#include "Vector.h"
#include <random>//置乱函数使用置乱器
#include <utility> //使用swap()函数
#include <iostream>


/////////////内部接口
template <typename T>
void Vector<T>::copyform(const T *A, Rank lo, Rank hi) //A[lo,hi)
{
    _elem = new T[_CAPACITY = (hi - lo) << 1];
    _size = 0;
    while (lo < hi)
        _elem[_size++] = A[lo++];
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
    //std::cout << "容量已缩减！！！" << std::endl;  //测试使用，已验证容量已经可以缩减
}

template <typename T>
void Vector<T>::permute()
{
    std::default_random_engine e;
    for (int i = _size; i != 0; --i)
        std::swap(_elem[i - 1], _elem[e() % i]);
}


///////////只读接口
template <typename T>
Rank Vector<T>::find(const T &e, Rank lo, Rank hi) const //[lo,hi)
{
    while ((lo < hi--) && (e != _elem[hi]))
        ;
    return hi;
}

template <typename T>
void Vector<T>::show() const
{
    for (int i = 0; i != _size; ++i)
        std::cout << _elem[i] << '\t';
}


///////////可写接口
template <typename T>
Vector<T> &Vector<T>::operator=(const Vector<T> &V)
{
    if (_elem)
        delete[] _elem;
    copyform(V.elem(), 0, V.size());
    return *this;
}

template <typename T>
T & Vector<T>::operator[](Rank r)const
{
    return _elem[r];
}

template <typename T>
void Vector<T>::unsort(Rank lo,Rank hi)     //[lo,hi)
{
    std::default_random_engine e;
    T *V = _elem + lo;
    for (int i = hi - lo; i != 0; --i)
        std::swap(V[i - 1], V[e() % i]);
}

template <typename T>
void Vector<T>::unsort()
{
    //unsort(0, _size);
    permute();
}

template <typename T>
Rank Vector<T>::insert(Rank r, const T &e)    //0 <= r <_size
{
    expand();
    for(int i=_size;i!=r;--i)
        _elem[i] = _elem[i - 1];
    _elem[r] = e;
    ++_size;
    return r;
}

template <typename T>
int Vector<T>::remove(Rank lo,Rank hi)
{
    if(lo==hi)
        return 0;
    while(hi<_size)
        _elem[lo++] = _elem[hi++];
    _size = lo;
    shrink();
    return hi - lo;
}

template <typename T>
T Vector<T>::remove(Rank r)
{
    T e = _elem[r];
    remove(r, r + 1);
    return e;
}

int main()
{
    int a[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    Vector<int> Vec1(10, 5, 5);
    Vector<int> Vec2(a, 8);
    Vector<int> Vec3(a, 2, 5);
    Vector<int> Vec4(Vec2);
    Vector<int> Vec5(Vec2, 2, Vec2.size());

    Vec1.show();
    std::cout << std::endl;
    Vec2.show();
    std::cout << std::endl;
    Vec3.show();
    std::cout << std::endl;
    Vec4.show();
    std::cout << std::endl;
    Vec5.show();
    std::cout << std::endl;
    //测试各个构造函数   copyfrom()

    Vec3.show();
    std::cout << std::endl;
    Vec3 = Vec2;
    Vec3.show();
    std::cout << std::endl;
    Vec3.unsort(Vec3.size() >> 1, Vec3.size());
    Vec3.show();
    std::cout << std::endl;
    Vec3.unsort();
    Vec3.show();
    std::cout << std::endl;
    //测试=   两个unsort() permute()

    Vec3[0] = -1;
    Vec3.show();
    std::cout << std::endl;
    //测试[]

    std::cout << Vec3.empty() << '\t' << Vec3.size() << '\t' << *Vec3.elem() << std::endl;
    //测试 上述三个函数

    std::cout << Vec3.find(-2) << '\t' << Vec3.find(-1, 4, 8) << std::endl;
    //测试两个find()

    Vector<int> Vec6(3, 3, 1);
    Vec6.show();
    std::cout << Vec6.size() << std::endl;
    Vec6.insert(1, -1);
    Vec6.show();
    std::cout << Vec6.size() << std::endl;
    //测试expand()和insert();

    Vector<int> Vec7(10, 10, 7);
    Vec7.show();
    std::cout << std::endl;
    std::cout << Vec7.size() << std::endl;
    std::cout << Vec7.remove(2, 10) << std::endl;
    Vec7.show();
    std::cout << std::endl;
    std::cout << Vec7.size() << std::endl;
    std::cout << Vec7.remove(0) << std::endl;
    Vec7.show();
    std::cout << std::endl;
    std::cout << Vec7.size() << std::endl;
    //测试两个 remove() 和 shrink()


    return 0;
}