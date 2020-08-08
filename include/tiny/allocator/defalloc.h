#ifndef TINY_DEFAULT_ALLOCATOR_H_
#define TINY_DEFAULT_ALLOCATOR_H_

#include <new>      // placement new
#include <cstddef>  // ptrdiff_t, size_t
#include <cstdlib>  // exit()
#include <climits>  // UINT_MAX
#include <iostream> // cerr

namespace tiny {

/*空间的分配，可以存储 size 个 T 对象*/
template <class T>
inline T* _allocate(ptrdiff_t size, T*) {
    /*为了卸载目前的内存分配异常处理函数，强制C++在内存不够的时候抛出std:bad_alloc*/
    std::set_new_handler(0);        

    /*空间的分配实现，调用 ::operator new() 全局函数*/
    T *temp = (T*)(::operator new((size_t)(size * sizeof(T))));
    if (0 == temp) {
        std::cerr << "out of memory" << std::endl;
        exit(1);
    }
    return temp;
}

/*空间的释放，调用 ::operator delete() 全局函数*/
template <class T>
inline void _deallocate(T *buffer) {
    ::operator delete(buffer);
}

/*对象的构造*/
template <class T, class V>
inline void _construct(T *p, const V& value) {
    new(p) T(value);    /*placement new*/
}

/*对象的析构*/
template <class T>
inline void _destroy(T *ptr) {
    ptr->~T();
}

/*提供外部使用的allocator*/
template <class T>
class allocator {
public:
    /*对象的类型*/
    typedef T value_type;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef T& reference;
    typedef const T& const_reference;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;

    /*嵌套allocator*/
    template <class U>
    struct rebind {
        typedef allocator<U> other;
    };

    /*以下四个函数提供外部使用，空间的分配和释放，对象的构造和析构*/
    pointer allocate(size_type n, const void *hint = 0) {
        return _allocate((difference_type)n, (pointer)0);
    }

    void deallocate(pointer p, size_type n) {
        _deallocate(p);
    }

    void construct(pointer p, const T& value) {
        _construct(p, value);
    }

    void destroy(pointer p) {
        _destroy(p);
    }

    /*返回某个对象的地址*/
    pointer address(reference x) {
        return (pointer)&x;
    }

    /*返回某个const对象的地址*/
    const_pointer const_address(const_reference x) {
        return (const_pointer)&x;
    }

    /*返回可成功分配的最大量*/
    size_type max_size() const {
        /*UINT_MAX 是 unsigned long 及 unsigned long long 的最大值*/
        return size_type(UINT_MAX/sizeof(T));
    }

    /*page size*/
    size_type init_page_size() {
        return size_type(4096/sizeof(T));
    }
};

}

#endif /*TINY_DEFAULT_ALLOCATOR_H_*/