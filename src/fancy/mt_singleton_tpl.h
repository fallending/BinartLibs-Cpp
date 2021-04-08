
#include <mutex>
#include <memory>

#ifndef MT_SINGTON_TPL_H_
#define MT_SINGTON_TPL_H_

namespace mt
{
namespace tpl
{
template <typename T>
class Singleton
{
public:
    // 创建单例实例
    template <typename... Args>
    static std::shared_ptr<T> Initial(Args &&...args)
    {
        std::call_once(flag_, [&] {
            inst_ = std::make_shared<T>(std::forward<Args>(args)...);
        });
        return inst_;
    }

    // 获取单例
    static std::shared_ptr<T> Shared() { return inst_; }

    Singleton(const Singleton &) = delete;
    Singleton(Singleton &&)      = delete;
    Singleton &operator=(const Singleton &) = delete;
    Singleton &operator=(Singleton &&) = delete;

private:
    Singleton()  = default;
    ~Singleton() = default;

    static std::shared_ptr<T> inst_;
    static std::once_flag     flag_;
};

template <typename T>
std::once_flag Singleton<T>::flag_;
template <typename T>
std::shared_ptr<T> Singleton<T>::inst_;
}  // namespace tpl
}  // namespace mt

#endif  // __MT_SINGTON_TPL_H__