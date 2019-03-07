#include "Vector.h"
#include <random>//置乱函数使用置乱器
#include <utility>//使用swap()函数

template <typename T>
void Vector<T>::copyform(T const *A, Rank lo, Rank hi) //A[lo,hi)
{
    _elem = new T[_CAPACITY = (lo + hi) << 1];
    _size = 0;
    while (lo < hi)
        _elem[_size++] = A[lo++];
}

template <typename T>
Vector<T> &Vector<T>::operator=(Vector<T> const &V)
{
    if (_elem)
        delete[] _elem;
    copyform(V.elem(), 0, V.size());
    return *this;
}

template <typename T>
void Vector<T>::expand()
{
    if(_size<_CAPACITY)
        return;
    if(_size<DEFAULT_CAPACITY)
        _CAPACITY = DEFAULT_CAPACITY;
    T *oldElem = _elem;
    _elem = new T[_CAPACITY <<= 1];
    for (int i = 0; i != _size;++i)
        _elem[i] = oldElem[i];
    delete[] oldElem;
}

template <typename T>
void Vector<T>::shrink()
{
    if(_CAPACITY<DEFAULT_CAPACITY<<1)
        return;
    if (_size << 2 > _CAPACITY)
        return;
    T *oldElem = _elem;
    _elem = new T[_CAPACITY >> 1];
    for (int i = 0; i != _size;++i)
        _elem[i] = oldElem[i];
    delete[] oldElem;
}

template<typename T>
T & Vector<T>::operator[](Rank r)const
{
    return *_elem[r];
}

template<typename T>
void Vector<T>::permute()
{
    std::default_random_engine e;
    for (int i = _size; i != 0; --i)
        std::swap(*this[i - 1], *this[e() % i]);
}









int main() { return 0; }