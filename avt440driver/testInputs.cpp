#include<cstdio>
#include "avt440driver.h"
#include <unistd.h>
#include<string>
#include<bitset>

using namespace std;

int main()
{
    avt440driver* testAVT440driver=new avt440driver();
    int status=testAVT440driver->getStatus();
    if(status!=0)
    {
        printf("status: %d\n", status);
        return 0;
    }
    bool runLoop=true;
    unsigned char counter=0;
    int loopCounter=0;
    while(runLoop)
    {
        testAVT440driver->openInputA();
        for(int i=0;i<100;i++)
        {
            printf("IA: %s\n",bitset<8>(testAVT440driver->getInput()).to_string().c_str());
            usleep(1000000);
        }
        testAVT440driver->closeInput();

        testAVT440driver->openInputB();
        for(int i=0;i<100;i++)
        {
            printf("IB: %s\n",bitset<8>(testAVT440driver->getInput()).to_string().c_str());
            usleep(1000000);
        }
        testAVT440driver->closeInput();

        loopCounter++;
        printf("LC: %d\n",loopCounter);
    }
}
