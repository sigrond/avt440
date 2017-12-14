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
        //0x1       0x2     0x4     0x8     0x10            0x20
        //STROBE ~ AUTO ~ INIT 0 SELECT ~   IRQviaACK 0    bi-directional-mode 0
        printf("podaj kontrol�\n 0x1       0x2     0x4     0x8     0x10            0x20 \n STROBE ~ AUTO ~ INIT 0 SELECT ~   IRQviaACK 0    bi-directional-mode 0\n");
        int d;
        scanf("%d",&d);
        testAVT440driver->setControll(d);
        printf("warto�� bin: %s\n",bitset<8>((unsigned char)d).to_string().c_str());
        printf("wej�cie zeby sprawdzi� rejsetr\n");
        scanf("%d",&d);
        printf("warto�� rejestru: %s\n",bitset<8>(testAVT440driver->getControll()).to_string().c_str());
        printf("wej�cie zeby sprawdzi� warto�ci na rejsetrze\n");
        scanf("%d",&d);
        printf("warto�� zewn�trzna rejestru: %s\n",bitset<8>(testAVT440driver->getControllFromDevice()).to_string().c_str());
    }
}

