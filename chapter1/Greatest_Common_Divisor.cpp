//使用更相减损术和欧几里得算法
//实现求两个整数的最大公约数
#include <iostream>

int gcd_1(int a, int b) {//更相减损术
    int r = 0;//r来存储2^r次方形式的公因子
    while (!((a & 1) || (b & 1)))//a和b均为偶数
    {
        a >>= 1;
        b >>= 1;
        ++r;
    }
    while (1) {
        while (!(a & 1))a >>= 1;//剔除偶因子
        while (!(b & 1))b >>= 1;
        (a > b) ? a = a - b : b = b - a;
        if (0 == a)return b << r;
        if (0 == b)return a << r;
    }
}//邓俊辉：数据结构习题解析（第三版）1-25

int gcd_2(int a, int b) {
    if (a < b)
        std::swap(a, b);
    return b == 0 ? a : gcd_2(b, a % b);
}

int main(void) {
    int a = 36, b = 48;
    std::cout << "The greatest common divisor: "
              << gcd_1(a, b) << std::endl;
    std::cout << "The greatest common divisor: "
              << gcd_2(a, b) << std::endl;
    return 0;
}
