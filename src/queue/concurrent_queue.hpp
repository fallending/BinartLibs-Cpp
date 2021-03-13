
#ifndef __CONCURRENT_QUEUE_H__
#define __CONCURRENT_QUEUE_H__

// 注意：1、析构函数没有加锁，因为需要同时对head lock和tail lock加锁。不建议在析构不确定的情况下使用。

// 2、经测试，比加锁的std::list快50%，比加锁的std::queue慢20%。

namespace mt
{
  class concurrent_lock
  {
  public:
    concurrent_lock()
    {
      // InitializeCriticalSection(&cs_);
    }

    ~concurrent_lock()
    {
      // DeleteCriticalSection(&cs_);
    }

    void lock()
    {
      // EnterCriticalSection(&cs_);
    }

    void unlock()
    {
      // LeaveCriticalSection(&cs_);
    }

  private:
    // CRITICAL_SECTION cs_;
  };

  class scoped_lock
  {
  public:
    scoped_lock(const concurrent_lock &lock) : lock_(lock)
    {
      const_cast<concurrent_lock &>(lock_).lock();
    }

    ~scoped_lock()
    {
      const_cast<concurrent_lock &>(lock_).unlock();
    }

  private:
    const concurrent_lock &lock_;
  };

  template <typename T>
  class concurrent_queue
  {
  public:
    concurrent_queue()
    {
      NODE *node = new NODE();
      node->next = nullptr; // NOTE: c of NULL, c++ 11+ of nullptr

      head_ = node;
      tail_ = node;
    }

    ~concurrent_queue()
    {
      NODE *node = head_;

      do
      {
        node = erase_(node);
      } while (node != nullptr);
    }

    void push(const T &val)
    {
      NODE *node = new NODE();
      node->val = val;
      node->next = nullptr;

      scoped_lock lock(t_lock_);
      tail_->next = node;
      tail_ = node;
    }

    bool pop(T *val)
    {
      scoped_lock lock(h_lock_);
      if (empty_())
      {
        return false;
      }

      head_ = erase_(head_);
      *val = head_->val;
      return true;
    }

  private:
    struct NODE
    {
      T val;
      NODE *next;
    };

  private:
    bool empty_() const
    {
      return head_->next == nullptr;
    }

    NODE *erase_(NODE *node) const
    {
      NODE *tmp = node->next;
      delete node;
      return tmp;
    }

  private:
    NODE *head_;
    NODE *tail_;
    concurrent_lock h_lock_;
    concurrent_lock t_lock_;
  };
} // namespace mt

#endif