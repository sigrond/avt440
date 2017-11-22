#include <sys/io.h>
//#include <asm/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main()
{
    char a=0;
    if(ioperm(0x378,3,1))
	exit(1);
    //printf("give value\n");
    //char v[4];
    //scanf("%d",(int*)v);
	for(int i=0;i<1000;i++)
	{
    		outb(1,0x37A);//STROBE 1 INIT 0
    		usleep(1000000);
    		outb(255,0x378);//wysoki na wyjscia
		outb(5,0x37A);//STROBE 1 INIT 1
	    	usleep(1000000);
    		outb(1,0x37A);//STROBE 1 INIT 0
    		usleep(1000000);
    		outb(0,0x378);//niski na wyjscia
    		outb(0,0x37A);//STROBE 0 INIT 0
    		usleep(1000000);
    		outb(1,0x37A);//STROBE 1 INIT 0
    		usleep(100000);
		a=inb(0x378+1);
    		printf("%u\n",a);

}
    a=inb(0x378+1);
    //outb(v[0],0x378);
    printf("Hello parallel port\n");
    printf("%u\n",a);
    return 0;
}
