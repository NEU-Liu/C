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
    //write(fd, "\0", 1); /* 在文件最后添加一个空字符，以便下面printf正常工作 */
    lseek(fd, 0, SEEK_SET);
    mapped_mem = mmap(start_addr, flength, PROT_READ|PROT_WRITE, //允许写入
    MAP_SHARED, //允许其它进程访问此内存区域
    fd, 0);
    printf("%s\n", mapped_mem); /* 为了保证这里工作正常，参数传递的文件名最好是一个文本文 */
    while((p = strstr(mapped_mem, "Hello"))) /* 此处来修改文件 内容 */
    {
        memcpy(p, "LinuxABCD", 9);
        
        p += 5;
        //memcpy(p, "LinuxABCD", 9);
    }
    memcpy(mapped_mem, "LinuxABCD", 9);
    
    close(fd);
    munmap(mapped_mem, flength);
    return 0;

}



