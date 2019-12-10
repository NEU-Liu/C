#include <sys/types.h> 
#include <sys/time.h> 
#include <stdio.h> 
#include <fcntl.h> 
#include <sys/ioctl.h> 
#include <unistd.h>
#include <stdlib.h>

int main() 
{ 
    char buffer[128]; 
    int result, nread; 
    fd_set inputs, testfds; 
    struct timeval timeout; 
    FD_ZERO(&inputs);//用select函数之前先把集合清零  
    FD_SET(0,&inputs);//把要检测的句柄——标准输入（0），加入到集合里。
     while(1) 
    { 
       testfds = inputs; 
       timeout.tv_sec = 2; //秒
       timeout.tv_usec = 500; //毫秒 
       result = select(FD_SETSIZE, &testfds, (fd_set *)0, (fd_set *)0, &timeout); //时间到就会返回结果，或者某个fd准备好了读写！
       //result = select(FD_SETSIZE, &testfds, (fd_set *)0, (fd_set *)0, 0); 
       
       // a file descriptor becomes ready;
       // the timeout expires.
        /**
         * int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);
         * fd_set *exceptfds: 暂时忽略，设为NULL.
         * timeout:为NULL或者0，就是阻塞模式
         * timeout,timeout.tv_sec = 0 && timeout.tv_usec =0 才是立即返回。 
         * timeout 为其他值就是但时间返回或者有描述符可以读的时候返回，此时不会等到时间到。
        */


       
       printf("%d\n",result);
       switch(result) 
       { 
       case 0: 
           printf("timeout!\n"); 
	       break;
	   case -1: 
           perror("select"); 
           exit(1); 
       default: 
           if(FD_ISSET(0,&testfds)) 
           { 
               ioctl(0,FIONREAD,&nread);//取得从键盘输入字符的个数，包括回车。 
               if(nread == 0) 
               { 
                  printf("keyboard done/n"); 
                  exit(0); 
               } 
               nread = read(0,buffer,nread); 
               buffer[nread] = 0; 
               printf("read %d from keyboard: %s", nread, buffer); 
         } 
         break; 
      } 
   } 
   return 0;
} 

