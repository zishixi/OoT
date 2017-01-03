
#pragma once

#include <mutex>
#include <condition_variable>
#include <thread>
#include <memory>

#define Mutex std::mutex;
#define Condition std::condition_variable;
#define StdThread std::thread;
#define SharedPtr std::shared_ptr;
#define UniqueLock std::unique_lock;

