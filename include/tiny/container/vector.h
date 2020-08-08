#ifndef TINY_VECTOR_H_
#define TINY_VECTOR_H_

namespace tiny
{

template <typename T, typename allocator>
class _vector
{
public:

};

template <typename T, typename allocator>
class vector: public _vector
{
public:
    vector(int n)
    {
        start = allocator(n);
    }
public:
    typedef T Elem;

private:
    Elem *start;
    Elem *last;
    Elem *end;
};

} /*namespace tiny*/

#endif /*TINY_VECTOR_H_*/