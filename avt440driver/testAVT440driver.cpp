#include<cstdio>
#include "avt440driver.h"

using namespace std;

int main()
{
    printf("testAVT440driver\n");
    avt440driver* testAVT440driver=new avt440driver();
    printf("status: %d\n", testAVT440driver->getStatus());
    printf("output high\n");
    testAVT440driver->setOutputA(255);
    testAVT440driver->setOutputB(255);
    printf("give number to set it\n");
    int d;
    scanf("%d",&d);
    testAVT440driver->setOutputA(d);
    testAVT440driver->setOutputB(d);
    printf("give number to continue with low output\n");
    printf("now it is time to give inputs\n");
    scanf("%d",&d);
    testAVT440driver->setOutputA(0);
    testAVT440driver->setOutputB(0);
    printf("outputs are:\n");
    printf("A: %d\n",testAVT440driver->getInputA());
    printf("B: %d\n",testAVT440driver->getInputB());
    printf("status register: %d\n",testAVT440driver->getStatusRegister());
    printf("give number to rewrite inputs to outputs for 10 times\n");
    scanf("%d",&d);
    for(int i=0;i<10;i++)
    {
        testAVT440driver->setInputAtoOutputA();
        testAVT440driver->setInputBtoOutputB();
    }
    printf("give number to exit\n");
    scanf("%d",&d);
    testAVT440driver->setOutputA(0);
    testAVT440driver->setOutputB(0);
    delete testAVT440driver;
    return 0;
}
