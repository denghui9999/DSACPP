//汉诺塔问题
#include <iostream>
const int num = 4;          //num表示棋子的数量
using arr = int[3];         //arr是含3个整数的数组
using honoi_arr = arr[num]; //num行3列
honoi_arr my_arr;           //myarr表示honoi塔状态数组

void init(honoi_arr myarr) //初始化函数
{
    for (int i = 0; i != num; ++i) //状态数组第一列从上到下依次1~num
        myarr[i][0] = i + 1;
    for (int i = 0; i != num; ++i) //其余列置零
    {
        for (int j = 1; j != 3; ++j)
        {
            myarr[i][j] = 0;
        }
    }
}

void show() //输出函数
{
    std::cout << "X\tY\tZ\t\n";
    for (int i = 0; i != num; ++i)
    {
        for (int j = 0; j != 3; ++j)
            std::cout << my_arr[i][j] << '\t';
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void move(int a, int b) //移动棋子：将第a列最上方棋子移动到第b列最上方
{
    int temp = 0;
    for (int i = 0; i != num; ++i) //找到第a列最上方棋子标号并用temp记录后置0
    {

        if (my_arr[i][a - 1] != 0)
        {

            temp = my_arr[i][a - 1];
            my_arr[i][a - 1] = 0;
            break;
        }
        else
        {
            continue;
        }
    }
    for (int i = num - 1; i >= 0; --i) //找到第b列空闲位置并置为temp
        if (my_arr[i][b - 1] == 0)
        {
            my_arr[i][b - 1] = temp;
            break;
        }
        else
        {
            continue;
        }
    show(); //每次移动后将状态输出
}

void honoi(int n, int x, int y, int z) //n为要移动棋子个数，x为起始列，因为中间列，z为目标列
{
    if (1 == n)
    {
        move(x, z);
    }
    else
    {
        honoi(n - 1, x, z, y);
        move(x, z);
        honoi(n - 1, y, x, z);
    }
    std::cout << std::endl;
    return;
}

int main(void)
{
    init(my_arr);
    show();
    honoi(num, 1, 2, 3);
    return 0;
}