#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv)
{
    int fd;
    char *mapped_mem, * p;
    int flength = 0;
    void * start_addr = 0;
    fd = open("demo.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    flength = lseek(fd, 1, SEEK_END);
    printf("flength:%d\n",flength);
    //write(fd, "\0", 1); /* 在文件最后添加一个空字符，以便下面printf正常工作 */
    lseek(fd, 0, SEEK_SET);
    mapped_mem = mmap(start_addr, flength, PROT_READ | PROT_WRITE, //允许读
    MAP_PRIVATE, //不允许其它进程访问此内存区域 MAP_SHARED 设置为这个值才鞥写内容！！
    fd, 0);
    printf("文件内容:%s\n", mapped_mem); /* 为了保证这里工作正常，参数传递的文件名最好是一个文本文件 */
    char * Data = "123456";
    memcpy(mapped_mem, "Data1234", 4);
    
    close(fd);
    munmap(mapped_mem, flength);
    return 0;
}


/*
用open系统调用打开文件, 并返回描述符fd.
用mmap建立内存映射, 并返回映射首地址指针start.
对映射(文件)进行各种操作, 显示(printf), 修改(sprintf).
用munmap(void *start, size_t lenght)关闭内存映射.
用close系统调用关闭文件fd.
**/