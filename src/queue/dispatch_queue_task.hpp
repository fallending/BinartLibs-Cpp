
#include <iostream>

#if !defined(__DISPATCH_QUEUE_TASK_H__)
#define __DISPATCH_QUEUE_TASK_H__

namespace mt
{
  // MARK: - QueueTask
  class QueueTask
  {
  public:
    QueueTask() : _signal(false) {}
    virtual ~QueueTask() {}

    virtual void run() = 0;
    virtual void signal()
    {
      _signal = true;
      _condition.notify_all();
    }
    virtual void wait()
    {
      std::unique_lock<std::mutex> lock(_mutex);
      _condition.wait(lock, [this]() { return _signal; });
      _signal = false;
    }

    virtual void reset()
    {
      _signal = false;
    }

  private:
    bool _signal;
    std::mutex _mutex;
    std::condition_variable _condition;
  };
  template <class T>
  class ClosureTask : public QueueTask
  {
  public:
    explicit ClosureTask(const T &closure) : _closure(closure) {}

  private:
    void run() override
    {
      _closure();
    }
    T _closure;
  };

} // namespace mt

#endif // __DISPATCH_QUEUE_TASK_H__
