/*
 * @Author: your name
 * @Date: 2021-03-26 14:19:06
 * @LastEditTime: 2021-03-26 14:22:15
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /mt-ccs/src/fancy/mt_shared_ptr.h
 */

#ifndef __MT_SHARED_PTR_H__
#define __MT_SHARED_PTR_H__

namespace fancy
{
    template<typename> class shared_ptr;

    template< class T >
    void swap( shared_ptr<T>& lhs, shared_ptr<T>& rhs ) noexcept 
    {
        std::cout << "swap out object  " << std::endl ;
        lhs.swap(rhs);
    }
        template<typename T>
    class shared_ptr {
        using DelFuncPtr = void (*)(T*) ;

    public:
        shared_ptr():m_ptr(nullptr),
        count_ptr( new size_t(0)),del(nullptr)
        {
        }
        explicit shared_ptr(T *ptr ,DelFuncPtr temp = nullptr ):
        m_ptr(ptr),count_ptr(new size_t(1)), del(temp )
        { 
        }
        //拷贝构造函数
        shared_ptr(const shared_ptr &hp):
        m_ptr(hp.m_ptr),count_ptr(hp.count_ptr),del(hp.del)
        { 
            ++(*count_ptr) ; //引用计数加1 
        }
        //拷贝赋值运算符 
        shared_ptr& operator=( shared_ptr &rhs){
            swap(*this,rhs);
            return *this;
        }
        //析构函数
        ~shared_ptr(){
            --(*count_ptr);
            if((*count_ptr) == 0 ){
                del ? del(m_ptr):
                    delete m_ptr;
                    delete count_ptr  ;
            }
            m_ptr = nullptr ;
            count_ptr =nullptr ;
        }
        size_t use_count(){ return (*count_ptr);}
        T& operator*() { return *m_ptr ;}
        T* operator->() { return m_ptr ; }

        void swap(shared_ptr &hp){
            std::cout << "swap in object " << std::endl ;
            using std::swap ;
            swap(m_ptr,hp.m_ptr);
            swap(count_ptr,hp.count_ptr);
            swap(del,hp.del);
        }
        void reset( ){
            if((*count_ptr) == 1) {
                delete m_ptr;
                delete count_ptr ;
                m_ptr = nullptr ;
                count_ptr =nullptr ;
            }
        }
        void reset( T *hp ,DelFuncPtr del = nullptr ){
            shared_ptr temp(hp,del);
            swap(temp);
        }
    private:
        T* m_ptr = nullptr ;
        size_t* count_ptr = nullptr ;
        //思考一下为什么是size_t*,而不是 size_t ? ?
        DelFuncPtr del = nullptr ; //自定义的删除器
    };
} // namespace fancy

#ifdef __MT_TEST__

#include <iostream>
using namespace std;

struct Foo {
    Foo() { std::cout << "Foo()\n"; }
    ~Foo() { std::cout << "~Foo()\n"; }
    Foo(const Foo&) { std::cout << "Foo copy ctor\n"; }
    Foo(Foo&&) { std::cout << "Foo move ctor\n"; }
};

struct Fooo {
    Fooo(int n = 0) noexcept : bar(n) { std::cout << "Fooo: constructor, bar = " << bar << '\n'; }
    ~Fooo() { std::cout << "Fooo: destructor, bar = " << bar << '\n'; }
    int GetBar() const noexcept { return bar; }

private:
    int bar;
};

struct D {
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
        std::cout << sh2.use_count() << '\n';//1
        shared_ptr<Foo> sh3(sh2);
        std::cout << sh3.use_count() << '\n';// 2

        shared_ptr<int> sh4(new int(4444)) ;
        shared_ptr<int> sh5(new int(5555)) ; // test swap()  
        sh4.swap(sh5);
        cout << "sh4 == "  << *sh4 << "\nsh5 == " << *sh5 << endl ; // 5555 4444 
        swap(sh4,sh5);
        cout << "sh4 == "  << *sh4 << "\nsh5 == " << *sh5 << endl ;  //4444  5555
    }

    std::cout << "shared_ptr constructor with deleter\n";
    {
        shared_ptr<Foo> sh5(new Foo, [](Foo* p) {
            std::cout << "Call delete from lambda...\n";
            delete p;
        });
    }

    {
        shared_ptr<Fooo> sptr(new Fooo(111)) ;
        std::cout << "The first Fooo's bar is " << sptr->GetBar() << "\n"; // 111  
        sptr.reset(new Fooo); //先搞一个新的出来,然后干掉原来的,避免自赋值
        std::cout << "The second Fooo's bar is " << sptr->GetBar() << "\n"; // 0 
    }
}

#endif


#endif // __MT_SHARED_PTR_H__