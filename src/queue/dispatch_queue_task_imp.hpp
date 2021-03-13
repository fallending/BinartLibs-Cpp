
#include <future>
#include <queue>
#include "dispatch_queue.hpp"

#if !defined(__DISPATCH_QUEUE_TASK_IMP_H__)
#define __DISPATCH_QUEUE_TASK_IMP_H__

namespace mt
{
  // MARK: - MutexQueueImp

  class MutexQueueImp : public DispatchQueue
  {
  public:
    MutexQueueImp(int thread_count)
        : DispatchQueue(thread_count),
          _cancel(false),
          _thread_count(thread_count)
    {
      for (int i = 0; i < thread_count; i++)
      {
        create_thread();
      }
    }
    ~MutexQueueImp()
    {
      _cancel = true;
      _condition.notify_all();
      for (auto &future : _futures)
      {
        future.wait();
      }
    }

    void sync_imp(std::shared_ptr<QueueTask> task) override
    {
      if (_thread_count == 1 && _thread_id == std::this_thread::get_id())
      {
        task->reset();
        task->run();
        task->signal();
      }
      else
      {
        async_imp(task);
        task->wait();
      }
    }

    int64_t async_imp(std::shared_ptr<QueueTask> task) override
    {
      _mutex.lock();
      task->reset();
      _dispatch_tasks.push(task);
      _mutex.unlock();
      _condition.notify_one();
      return 0;
    }

  private:
    MutexQueueImp(const MutexQueueImp &);

    void create_thread()
    {
      _futures.emplace_back(std::async(std::launch::async, [&]() {
        _thread_id = std::this_thread::get_id();
        while (!_cancel)
        {

          {
            std::unique_lock<std::mutex> work_signal(_signal_mutex);
            _condition.wait(work_signal, [this]() {
              return _cancel || !_dispatch_tasks.empty();
            });
          }

          while (!_dispatch_tasks.empty() && !_cancel)
          {
            _mutex.lock();
            if (_dispatch_tasks.empty())
            {
              _mutex.unlock();
              break;
            }
            std::shared_ptr<QueueTask> task(_dispatch_tasks.front());
            _dispatch_tasks.pop();
            _mutex.unlock();
            if (nullptr != task)
            {
              task->run();
              task->signal();
            }
          }
        }
      }));
    }

  private:
    std::vector<std::future<void>> _futures;
    std::queue<std::shared_ptr<QueueTask>> _dispatch_tasks;
    std::recursive_mutex _mutex;
    bool _cancel;
    std::mutex _signal_mutex;
    std::condition_variable _condition;
    int _thread_count;
    std::thread::id _thread_id;
  };
} // namespace mt

#endif // __DISPATCH_QUEUE_TASK_IMP_H__
