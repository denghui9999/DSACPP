#ifndef MY_FIB_H
#define MY_FIB_H

class Fib{
    private:
        int f, g;//f=fib(n-1),g=fib(n)
    public:
        Fib(int n) //初始化为不小于n的最小Fibonacci项
        {
            f = 1;
            g = 0;
            while (g < n)
            {
                next();
            }
        }
        int get() { return g; }
        int next() {
            g = g + f;
            f = g - f;
            return g;
        }
        int prev(){
            f = g - f;
            g = g - f;
            return g;
        }
};



#endif