//使用更相减损术和欧几里得算法
//实现求两个整数的最大公约数
#include <iostream>

int gcd_1(int a,int b)//更相减损术
{
    int r=0;//r来存储2^r次方形式的公因子
    while(!((a&1)||(b&1))){//a和b均为偶数
        a>>=1;
        b>>=1;
        ++r;
    }
    while(1){
        while(!(a&1))a>>=1;
        while(!(b&1))b>>=1;
        (a>b)?a=a-b:b=b-a;
        if(0==a)return b<<r;
        if(0==b)return a<<r;
    }
}

int main(void){
    int a=36,b=48;
    std::cout<<"The greatest common divisor: "
    <<gcd_1(a,b)<<std::endl;
    return 0;
}
