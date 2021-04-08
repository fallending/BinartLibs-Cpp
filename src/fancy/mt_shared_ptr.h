#include <iostream>

#ifndef MT_SHARED_PTR_H_
#define MT_SHARED_PTR_H_

namespace fancy
{
template <typename>
class shared_ptr;

template <class T>
void Swap(shared_ptr<T>& lhs, shared_ptr<T>& rhs) noexcept
{
    std::cout << "swap out object  " << std::endl;
    lhs.swap(rhs);
}

template <typename T>
class shared_ptr
{
    using DelFuncPtr = void (*)(T*);

public:
    shared_ptr() : ptr_(nullptr), count_ptr_(new size_t(0)), del_(nullptr) {}
    explicit shared_ptr(T* ptr, DelFuncPtr temp = nullptr)
        : ptr_(ptr), count_ptr_(new size_t(1)), del_(temp)
    {
    }
    //拷贝构造函数
    shared_ptr(const shared_ptr& hp)
        : ptr_(hp.ptr_), count_ptr_(hp.count_ptr_), del_(hp.del_)
    {
        ++(*count_ptr_);  //引用计数加1
    }
    //拷贝赋值运算符
    shared_ptr& operator=(const shared_ptr& rhs)
    {
        Swap(*this, rhs);
        return *this;
    }
    //析构函数
    ~shared_ptr()
    {
        --(*count_ptr_);
        if ((*count_ptr_) == 0)
        {
            del_ ? del_(ptr_) : delete ptr_;
            delete count_ptr_;
        }
        ptr_       = nullptr;
        count_ptr_ = nullptr;
    }
    size_t UseCount() { return (*count_ptr_); }
    T&     operator*() { return *ptr_; }
    T*     operator->() { return ptr_; }

    void Swap(shared_ptr& hp)
    {
        std::cout << "swap in object " << std::endl;
        using std::swap;
        swap(ptr_, hp.ptr_);
        swap(count_ptr_, hp.count_ptr_);
        swap(del_, hp.del_);
    }
    void Reset()
    {
        if ((*count_ptr_) == 1)
        {
            delete ptr_;
            delete count_ptr_;
            ptr_       = nullptr;
            count_ptr_ = nullptr;
        }
    }
    void Reset(T* hp, DelFuncPtr del = nullptr)
    {
        shared_ptr temp(hp, del);
        Swap(temp);
    }

private:
    T*      ptr_       = nullptr;
    size_t* count_ptr_ = nullptr;
    //思考一下为什么是size_t*,而不是 size_t ? ?
    DelFuncPtr del_ = nullptr;  //自定义的删除器
};
}  // namespace fancy

#ifdef MT_TEST_

#include <iostream>
using namespace std;

struct Foo
{
    Foo() { std::cout << "Foo()\n"; }
    ~Foo() { std::cout << "~Foo()\n"; }
    Foo(const Foo&) { std::cout << "Foo copy ctor\n"; }
    Foo(Foo&&) { std::cout << "Foo move ctor\n"; }
};

struct Fooo
{
    Fooo(int n = 0) noexcept : bar(n)
    {
        std::cout << "Fooo: constructor, bar = " << bar << '\n';
    }
    ~Fooo() { std::cout << "Fooo: destructor, bar = " << bar << '\n'; }
    int GetBar() const noexcept { return bar; }

private:
    int bar;
};

struct D
{
    void bar() { std::cout << "Call deleter D::bar()...\n"; }
    void operator()(Foo* p) const
    {
        std::cout << "Call delete from function object...\n";
        delete p;
    }
};
int main()
{
    std::cout << "shared_ptr constructor with no managed object\n";
    {
        shared_ptr<Foo> sh1;
    }

    std::cout << "shared_ptr constructor with object and test swap \n";
    {
        shared_ptr<Foo> sh2(new Foo);
        std::cout << sh2.UseCount() << '\n';  // 1
        shared_ptr<Foo> sh3(sh2);
        std::cout << sh3.UseCount() << '\n';  // 2

        shared_ptr<int> sh4(new int(4444));
        shared_ptr<int> sh5(new int(5555));  // test swap()
        sh4.swap(sh5);
        cout << "sh4 == " << *sh4 << "\nsh5 == " << *sh5 << endl;  // 5555 4444
        swap(sh4, sh5);
        cout << "sh4 == " << *sh4 << "\nsh5 == " << *sh5 << endl;  // 4444  5555
    }

    std::cout << "shared_ptr constructor with deleter\n";
    {
        shared_ptr<Foo> sh5(new Foo, [](Foo* p) {
            std::cout << "Call delete from lambda...\n";
            delete p;
        });
    }

    {
        shared_ptr<Fooo> sptr(new Fooo(111));
        std::cout << "The first Fooo's bar is " << sptr->GetBar()
                  << "\n";  // 111
        sptr.reset(new Fooo);  //先搞一个新的出来,然后干掉原来的,避免自赋值
        std::cout << "The second Fooo's bar is " << sptr->GetBar()
                  << "\n";  // 0
    }
}

#endif

#endif  // MT_SHARED_PTR_H_