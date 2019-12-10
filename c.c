#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct VarLen_Struct //结构体的内存不一定连续，考虑到对齐原则！
{
    uint32_t Len;
    int *    Data;   //Data是一个指针变量：下面的两种情况都是指向一块连续的内存区域！
};

int main(int argc, char const *argv[])
{
    int TempData[10] = {0,1,2,3,4,5,6,7,8,9};
    struct VarLen_Struct my_Struct;

    // 第一种方式：
    my_Struct.Len = 10;
    my_Struct.Data= (int *)malloc(sizeof(int)*10); //malloc 申请的内存在逻辑上连续上，在物理地址上不连续！
    for (size_t i = 0; i < 10; i++)
    {
        printf("%d\n", my_Struct.Data[i]);
    }
    // 第二种方式：
    my_Struct.Len = 10;
    my_Struct.Data= TempData;
    for (size_t i = 0; i < 10; i++)
    {
        printf("%d\n", my_Struct.Data[i]);
    }

   
    return 0;
}



