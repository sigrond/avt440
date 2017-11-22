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
        printf("IA: %s\t",bitset<8>(testAVT440driver->getInputA()).to_string().c_str());
        printf("IB: %s\t",bitset<8>(testAVT440driver->getInputB()).to_string().c_str());
        testAVT440driver->setOutputA(counter);
        printf("OA: %s\t",bitset<8>(counter).to_string().c_str());
        testAVT440driver->setOutputB(counter);
        printf("OB: %s\t",bitset<8>(counter).to_string().c_str());
        printf("SR: %3hhu ",testAVT440driver->getStatusRegister());
        printf("LC: %d\n",loopCounter);
        if(counter==0)
        {
            counter=1;
        }
        else
        {
            counter<<=1;
        }
        usleep(1000000);
        loopCounter++;
        //printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
    }
    return 0;
}
