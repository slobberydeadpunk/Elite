#include <iostream>
#include <deque>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition.hpp>

using namespace std;

#define DEFAULT_PACKET_SIZE 1280

class Packet
{
	int size_;
	unsigned char databuf_[DEFAULT_PACKET_SIZE];
	unsigned int id_;

public:
	Packet() { std::memset(databuf_, 0, sizeof(databuf_)); }
	~Packet() { ; }

	int getSize() { return size_; }
	void setSize(int size) { size_ = size; }
	
	unsigned int getID() { return id_; }
	void setID(unsigned int id) { id_ = id; }
	
	void getData(char* pbuf) { memcpy(pbuf, databuf_, size_); }
	void setData(char* pbuf, int size) { memcpy(databuf_, pbuf, size); }

	virtual bool isValid() { return false; }
	virtual bool encode() { return false; }
	virtual bool decode() { return false; }
};

class ISynchronizedQueue
{
public:
	virtual bool add(Packet pkt) = 0;
	virtual bool get(Packet& pkt) = 0;
};

class SynchronizedQueue : public ISynchronizedQueue
{
	boost::mutex mutex_;
	deque<Packet> queue_;
	//boost::condition_variable cond_;

public:
	bool add(Packet pkt)
	{
		boost::lock_guard<boost::mutex> lock(mutex_);
		queue_.push_back(pkt);
		return true;
	}

	bool get(Packet& pkt)
	{
		boost::lock_guard<boost::mutex> lock(mutex_);
		if (!queue_.size())
		{
			return false;
		}

		pkt = queue_.front();
		queue_.pop_front();
		return true;
	}
};


class SynchronizedVector :public ISynchronizedQueue
{
	int size_;
	boost::mutex mutex_;
	std::vector<Packet> vec_;
	int start_, end_;

public:
	SynchronizedVector(int size = 100) 
		: size_(size)
		, start_(0)
		, end_(0)
	{ vec_.assign(size_, Packet()); }

	bool add(Packet pkt)
	{
		boost::lock_guard<boost::mutex> lock(mutex_);
		vec_[end_++] = pkt;
		if(end_ >= size_)
			end_ = 0;
		if(end_ == start_)
			start_= end_ + 1;
		if(start_ >= size_)
			start_ = 0;
		return true;
	}

	bool get(Packet& pkt)
	{
		boost::lock_guard<boost::mutex> lock(mutex_);
		if(start_ == end_)
			return false;
		pkt = vec_[start_++];
		if(start_ >= size_)
			start_ = 0;
		return true;
	}
};


class SynchronizedVectorNB :public ISynchronizedQueue
{
	int size_;
	boost::mutex mutex_;
	std::vector<Packet> vec_;
	int start_, end_;

public:
	SynchronizedVectorNB(int size = 100)
		: size_(size)
		, start_(0)
		, end_(0)
	{ vec_.assign(size_, Packet()); }
	
	bool add(Packet pkt)
	{
		boost::unique_lock<boost::mutex> lock(mutex_, boost::try_to_lock_t());
		if(!lock.owns_lock())
			return false;
		vec_[end_++] = pkt;
		if(end_ >= size_)
			end_ = 0;
		if(end_ == start_)
			start_ = end_ + 1;
		if(start_ >= size_)
			start_ = 0;
		return true;
	}

	bool get(Packet& pkt)
	{
		boost::unique_lock<boost::mutex> lock(mutex_,boost::try_to_lock_t());
		if(!lock.owns_lock())
			return false;

		if(start_ == end_)
			return false;
		pkt = vec_[start_++];
		if(start_ >= size_)
			start_ = 0;
		return true;
	}
};