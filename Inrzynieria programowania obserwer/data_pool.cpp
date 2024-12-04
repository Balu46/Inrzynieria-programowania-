#include"data_pool.h"

data_pool* data_pool::my_data = nullptr;;
mutex data_pool::sMutex;


/**
 * Static methods should be defined outside the class.
 */
data_pool* data_pool::GetInstance()
{
	/**
	 * This is a safer way to create an instance. instance = new Singleton is
	 * dangeruous in case two instance threads wants to access at the same time
	 */
	std::lock_guard<std::mutex> lock(sMutex);

	if (my_data == nullptr) {
		my_data = new data_pool;
	}
	return my_data;

}