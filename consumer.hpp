/*
 * consumer.hpp
 *
 *  Created on: 16 gru 2020
 *      Author: kszmmnn
 */

#ifndef CONSUMER_HPP_
#define CONSUMER_HPP_
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/containers/deque.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/sync/interprocess_condition.hpp>
#include <boost/thread/lock_guard.hpp>
#include <sstream>


using MySynchronisedQueue = SynchronizedQueue<int>;

#endif /* CONSUMER_HPP_ */
