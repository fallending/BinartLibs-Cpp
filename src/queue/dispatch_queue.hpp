/**
 C++ 实现的 Dispatch Queue

 iOS/Mac 平台下 apple 提供了非常好用的 dispatch_queue 能够很方便的进行线程的管理以及各个线程之间的切换（当然还有很多其他特性）。虽说 C++ 的标准库中提供了很多线程管理的方法，但相比于 dispatch_queue 还是弱爆了。由于项目中会经常用到，GitHub 上找了一些类似的实现都不太理想，于是自己实现了一版简单的主要支持一下特性：

  - 支持并发调用，并支持并发的任务处理
  - 支持任务的同步执行和异步执行
  - 可创建指定数量的任务线程
  - 执行同步任务时，在任务线程中可继续执行同步任务而不卡死
  - 同一任务可重复执行
  - 支持 lambda 表达式
  - 支持任务线程的安全退出

  类设计

  - DispatchQueue
    +sync()
    +async()
    +sync_imp()
    +async_imp()

  - DispatchTask
    +run()
    +signal()
    +wait()
    +reset()
*/

#include <iostream>

#include "dispatch_queue_task.hpp"

#if !defined(__DISPATCH_QUEUE_H__)
#define __DISPATCH_QUEUE_H__

namespace mt
{
  class DispatchQueue
  {
  public:
    DispatchQueue(int thread_count) {}

    virtual ~DispatchQueue() {}

    template <class T, typename std::enable_if<std::is_copy_constructible<T>::value>::type * = nullptr>
    void sync(const T &task)
    {
      sync(std::shared_ptr<QueueTask>(new ClosureTask<T>(task)));
    }

    void sync(std::shared_ptr<QueueTask> task)
    {
      if (nullptr != task)
      {
        sync_imp(task);
      }
    }

    template <class T, typename std::enable_if<std::is_copy_constructible<T>::value>::type * = nullptr>
    int64_t async(const T &task)
    {
      return async(std::shared_ptr<QueueTask>(new ClosureTask<T>(task)));
    }

    int64_t async(std::shared_ptr<QueueTask> task)
    {
      if (nullptr != task)
      {
        return async_imp(task);
      }
      return -1;
    }

  protected:
    virtual void sync_imp(std::shared_ptr<QueueTask> task) = 0;

    virtual int64_t async_imp(std::shared_ptr<QueueTask> task) = 0;
  };
} // namespace mt

#endif // __DISPATCH_QUEUE_H__
