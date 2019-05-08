#include "Vector.h"
#include "fibonacci.h"//引入Fib类，在fibSearch中使用
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
    for (int i = _size; i != 0; --i){
        static std::default_random_engine e;
        static std::uniform_int_distribution<Rank> u(0, i - 1);
        std::swap(_elem[i - 1], _elem[u(e)]);//swap()-头文件ultility
    }
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
T & Vector<T>::operator[](Rank r)const//此处并没有对原有对象进行修改，但对返回的引用进行改变
//判断r是否越界(即 r >= _size)由上层判断
{
    return _elem[r];
}

template <typename T>
void Vector<T>::unsort(Rank lo,Rank hi)     //置乱[lo,hi)
{
    T *V = _elem + lo;
    for (int i = hi - lo; i != 0; --i)
    {
        static std::default_random_engine e;
        static std::uniform_int_distribution<Rank> u(0, i - 1);
        std::swap(V[i - 1], V[u(e)]);
    }
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
int Vector<T>::remove(Rank lo, Rank hi) //[lo,hi)
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

template <typename T>
int Vector<T>::deduplicate() //去除无序向量的重复元素，返回去除的元素个数
{
    int oldSize = _size;
    Rank i = 1;
    while(i<_size)
    {
        find(_elem[i], 0, i) < 0 ? ++i : remove(i);
    }
    return oldSize - _size;
}

//有序向量
template <typename T>
int Vector<T>::disordered()const//判别向量中逆序的元素数，返回0表示该向量有序
{
    int n = 0;//记录逆序数
    for (int i = 1; i != _size; ++i)
    {
        if(_elem[i-1]>_elem[i])
            ++n;
    }
    return n;
}

//template <typename T>
//int Vector<T>::uniquify()//该函数为低效版 复杂度 O(n2)
//{
//    int oldsize = _size;
//    int i = 1;
//    while (i < _size)
//        _elem[i - 1] == _elem[i] ? remove(i) : ++i;//remove() O(n)
//    return oldsize - _size;
//}

template <typename T>
int Vector<T>::uniquify()//有序向量唯一化高效版,
//避免了remove()操作, 复杂度O(n)
//由无序向量的o(n2)到有序向量的O(n),关键在与对向量进行排序
{
    Rank i = 0, j = 0;
    while(++j<_size)
    if(_elem[i]!=_elem[j])
        _elem[++i] = _elem[j];//覆盖操作就意味着删除了原有的元素
    _size = ++i;
    shrink();
    return j - i;
}

template <typename T>
Rank Vector<T>::binSearch_A(const T &e,Rank lo,Rank hi)const//在[lo,hi)中查找返回秩，失败返回-1
//O(1.5log2(n))   
{
    while(lo<hi)
    {
        int mi = (lo + hi) >> 1;
        if (e < _elem[mi])
            hi = mi;
        else if (_elem[mi] < e)//考虑到可能T只重载了操作符 <
            lo = mi + 1;
        else
            return mi;
    }
    return -1;
}

template <typename T>
Rank Vector<T>::fibSearch(const T &e, Rank lo, Rank hi)const//在[lo,hi)中查找返回秩，失败返回-1
//O(1.44log2(n))
{
    Fib fib(hi - lo);
    while (lo < hi)
    {
        while ((hi - lo) < fib.get())//最终，fib.get()最小为 1
            fib.prev();
        Rank mi = lo + fib.get() - 1;
        if(e<_elem[mi])
            hi = mi;
        else if(_elem[mi]<e)
            lo = mi + 1;
        else
            return mi;
    }
    return -1;
}

template <typename T>
Rank Vector<T>::binSearch_B(const T &e, Rank lo, Rank hi)const //在[lo,hi)中查找返回秩，失败返回-1
//三分支减少为二分支 但停止条件变为查找区间不足2 好的情况效率变低，坏的情况效率提升
{
    
    while (1 < hi - lo)
    {
        Rank mi = (lo + hi) >> 1;
        (e < _elem[mi]) ? hi = mi : lo = mi;
    }
    return (e == _elem[lo]) ? lo : -1;
}

template <typename T>
Rank Vector<T>::binSearch_C(const T &e,Rank lo,Rank hi)const//在[lo,hi)中查找e
//命中返回其中秩最大者，未命中返回小于e的最大秩
{
    while(lo<hi)
    {
        Rank mi = (lo + hi) >> 1;
        (e < _elem[mi]) ? hi = mi : lo = mi + 1;
    }
    return --lo;
}

template <typename T>
Rank Vector<T>::Search(const T &e)const
{
    static std::default_random_engine re;
    static std::uniform_int_distribution<unsigned> u(0, 1);
    return u(re) ? binSearch_C(e, 0, _size) : fibSearch(e, 0, _size);
}

//冒泡排序
template <typename T>
bool Vector<T>::bubble(Rank lo,Rank hi)//一趟扫描将[lo,hi)中最大数置于最后，返回false
{
    bool sorted = true;
    while (++lo < hi)
    {
        if (_elem[lo] < _elem[lo - 1])
        {
            sorted = false;
            std::swap(_elem[lo - 1], _elem[lo]);
        }
    }
    return sorted;
}
template <typename T>
void Vector<T>::bubbleSort(Rank lo,Rank hi)//多趟扫描，直至全序
{
    while(!bubble(lo,hi--))
        ;
}


//归并排序
template <typename T>
void Vector<T>::merge(Rank lo, Rank mi, Rank hi)
{
    T *A = _elem + lo;
    int lb = mi - lo;
    T *B = new T[lb]; //
    for (Rank i = 0; i != lb; ++i)
        B[i] = A[i];
    int lc = hi - mi;
    T *C = _elem + mi;
    for (Rank i = 0, j = 0, k = 0; (j < lb) || (k < lc);)
    {
        if ((j < lb) && ((k >= lc) || (B[j] <= C[k])))
            A[i++] = B[j++];
        if ((k < lc) && ((j >= lb) || (C[k] < B[j])))
            A[i++] = C[k++];
    }
    delete[] B;
}
template <typename T>
void Vector<T>::mergeSort(Rank lo,Rank hi)
{
    if (hi - lo < 2)
        return;
    int mi = (lo + hi) >> 1;
    mergeSort(lo, mi); //无序向量的递归分解
    mergeSort(mi, hi); //无序向量的递归分解
    merge(lo, mi, hi); //归并生成有序向量
}

template <typename T>
void Vector<T>::Sort(Rank lo, Rank hi) //[lo,hi)对外的排序接口，采用随机一排序算法
{
    static std::default_random_engine e;
    static std::uniform_int_distribution<int> u(0, 1);
    (u(e) == 0) ? bubbleSort(lo, hi) : mergeSort(lo, hi);
}

int main()
{
    const int arr_size = 25;
    int arr_test[arr_size];
    for (int i = 0; i !=arr_size;++i)
        arr_test[i] = i * 2;
    
    Vector<int> test1(arr_test, arr_size);
    test1.show();
    std::cout << std::endl;

    test1.unsort();
    test1.show();
    std::cout << std::endl;

    test1.Sort(0, 9);
    test1.show();
    std::cout << std::endl;
    test1.Sort(9, 18);
    test1.show();
    std::cout << std::endl;
    test1.Sort(18, 25);
    test1.show();
    std::cout << std::endl;
    return 0;   
}