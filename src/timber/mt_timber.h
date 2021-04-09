

#include "mt_type.h"
#include "mt_tree.h"

#ifndef TAG_
#define TAG_ ""
#endif  // TAG_

#ifndef MT_TIMBER_H_
#define MT_TIMBER_H_

namespace timber
{
#define TIMBER_LOG_FUNC_DEF(func)                                                       \
    void func(const LeafPtr &leaf, const char *message, ...) const                      \
    {                                                                                   \
        va_list args;                                                                   \
        va_start(args, message);                                                        \
        for (auto it : Timber::shared().trees_)                                         \
        {                                                                               \
            if (message)                                                                \
                it->func(leaf, tag_, message, args);                                    \
        }                                                                               \
        va_end(args);                                                                   \
    }                                                                                   \
    void func(const char *message, ...) const                                           \
    {                                                                                   \
        va_list args;                                                                   \
        va_start(args, message);                                                        \
        for (auto it : Timber::shared().trees_)                                         \
        {                                                                               \
            if (message)                                                                \
                it->func(CreateLeaf(LogPriorityFromShort(#func)), tag_, message, args); \
        }                                                                               \
        va_end(args);                                                                   \
    }

class Timber
{
private:
    std::string          tag_;
    std::vector<TreePtr> trees_;

public:
    explicit Timber(const std::string &tag) { tag_ = tag; };
    ~Timber() = default;

    static Timber &shared()
    {
        static Timber instance("");
        return instance;
    }

    static Timber Tagged(const std::string &tag)
    {
        // std::cout << "inside Timber, TAG_ = " << tag << std::endl;
        return Timber(tag);
    }

    static void Plant(const TreePtr &tree)
    {
        static std::mutex lock;
        lock.lock();

        Timber::shared().trees_.emplace_back(tree);

        lock.unlock();
    };

    // @warning do not implicitly decay an array into a pointer; consider using gsl::array_view or an explicit cast
    // instead
    // @document https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md#Pro-bounds-decay
    // @check -hicpp-no-array-decay,
    TIMBER_LOG_FUNC_DEF(d)
    TIMBER_LOG_FUNC_DEF(i)
    TIMBER_LOG_FUNC_DEF(w)
    TIMBER_LOG_FUNC_DEF(e)
};

static const Timber logger = Timber::Tagged(TAG_);  // 每个引用的源文件，都会有它

#define logd(message, ...)                                                  \
    timber::logger.d(timber::CreateLeaf(timber::LogPriorityDebug,           \
                                        TAG_,                               \
                                        timber::FileNameFromPath(__FILE__), \
                                        __FUNCTION__,                       \
                                        std::to_string(__LINE__)),          \
                     message,                                               \
                     ##__VA_ARGS__);
#define logi(message, ...)                                                  \
    timber::logger.i(timber::CreateLeaf(timber::LogPriorityInfo,            \
                                        TAG_,                               \
                                        timber::FileNameFromPath(__FILE__), \
                                        __FUNCTION__,                       \
                                        std::to_string(__LINE__)),          \
                     message,                                               \
                     ##__VA_ARGS__);
#define logw(message, ...)                                                  \
    timber::logger.w(timber::CreateLeaf(timber::LogPriorityWarn,            \
                                        TAG_,                               \
                                        timber::FileNameFromPath(__FILE__), \
                                        __FUNCTION__,                       \
                                        std::to_string(__LINE__)),          \
                     message,                                               \
                     ##__VA_ARGS__);
#define loge(message, ...)                                                  \
    timber::logger.e(timber::CreateLeaf(timber::LogPriorityError,           \
                                        TAG_,                               \
                                        timber::FileNameFromPath(__FILE__), \
                                        __FUNCTION__,                       \
                                        std::to_string(__LINE__)),          \
                     message,                                               \
                     ##__VA_ARGS__);

}  // namespace timber

#endif  // MT_TIMBER_H_