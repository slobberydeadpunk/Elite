#include <iostream>
#include <queue>

#include "boost\thread.hpp"
#include "boost\timer.hpp"

std::queue<int> itemQ;

boost::mutex m;
boost::condition_variable qFull, qEmpty;

const int max_size_q = 5;


void producer()
{
	int i = 0;
	while (1)
	{
		boost::this_thread::sleep(boost::posix_time::millisec(1000));
		boost::mutex::scoped_lock lock(m);      

		while (itemQ.size() > max_size_q)
		{
			std::cout << "Q Full.notify_one Producer Waiting" << std::endl;
			qFull.wait(lock);
			std::cout << "Producer Notified to Continue" << std::endl;
		}

		itemQ.push(++i);
		qEmpty.notify_one();
	}

}

void consumer()
{
	while (1)
	{
		boost::this_thread::sleep(boost::posix_time::millisec(4000));
		boost::mutex::scoped_lock lock(m);

		while (itemQ.size() == 0)
		{
			std::cout << "Q Empty. Consumer " << boost::this_thread::get_id() <<" Waiting" << std::endl;
			qEmpty.wait(lock);
			std::cout << "Consumer Notified to Continue" << std::endl;
		}

		std::cout << itemQ.front() << std::endl;
		itemQ.pop();
		qFull.notify_one();

	}
}

int main()
{
	boost::thread producerthread(producer);

	boost::thread consumerthread1(consumer);
	boost::thread consumerthread2(consumer);
	boost::thread consumerthread3(consumer);
	boost::thread consumerthread4(consumer);
	boost::thread consumerthread5(consumer);

	consumerthread1.join();
	consumerthread2.join();
	consumerthread3.join();
	consumerthread4.join();
	consumerthread5.join();
}