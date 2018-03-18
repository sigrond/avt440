#include "avt440driver.h"
#include <sys/io.h>
//#include <asm/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BASE 0x378
#define WAIT_TIME 100000

//0x1       0x2     0x4     0x8     0x10            0x20
//STROBE ~ AUTO ~ INIT 0 SELECT ~   IRQviaACK 0    bi-directional-mode 0
#define STROBE 0x1 /**< neg *///neg
#define AUTO 0x2 /**< neg *///neg
#define INIT 0x4 /**< pos *///pos
#define SELECT 0x8 /**< neg *///neg
#define DIRECTION 0x20

//#define DEBUG

avt440driver::avt440driver() : status(0), InA(0), InB(0), OutA(0), OutB(0), ctl(0)
{
    //ctor
    {
        status=-1;
    }
    else
    {
        outb(0,BASE);
        outb(STROBE ,BASE+2);
        usleep(WAIT_TIME);
        outb(INIT ,BASE+2);
        usleep(WAIT_TIME);
        outb(STROBE ,BASE+2);
        usleep(WAIT_TIME);
        ctl=inb(BASE+2);
    }
}

avt440driver::~avt440driver()
{
    //dtor
    outb(0,BASE);
    usleep(WAIT_TIME);
    outb(INIT ,BASE+2);
    usleep(WAIT_TIME);
    outb(STROBE ,BASE+2);
    usleep(WAIT_TIME);
}

int avt440driver::getStatus()
{
    return status;
}

void avt440driver::setOutputA(unsigned char b)
{
    //adres
    //nazwa zanegowanie
    //0x1       0x2     0x4     0x8     0x10            0x20
    //STROBE ~ AUTO ~ INIT 0 SELECT ~   IRQviaACK 0    bi-directional-mode 0
    #ifdef DEBUG
    unsigned char a=0;
    a=inb(BASE);
    printf("a: %d\n",a);
    #endif // DEBUG
    outb(0,BASE);
    #ifdef DEBUG
    a=inb(BASE);
    printf("a: %d\n",a);
    #endif // DEBUG
    outb(0b00000001,BASE+2);//STROBE 0 AUTO 1 INIT 0 SELECT 1 - wysoki na OC buforow wejsciowych niski na wejscia zegarowe buforow wyjscioowych
    outb(b,BASE);
    usleep(WAIT_TIME);
    outb(0b00000000,BASE+2);//STROBE 1 INIT 0 - wysoki na clk IC3 (bufor A)
    usleep(WAIT_TIME);
    outb(0b00000001,BASE+2);//STROBE 0 INIT 0
    usleep(WAIT_TIME);
    #ifdef DEBUG
    a=inb(BASE);
    printf("a: %d\n",a);
    #endif // DEBUG
    outb(0,BASE);
    #ifdef DEBUG
    a=inb(BASE);
    printf("a: %d\n",a);
    #endif // DEBUG
    OutA=b;
}

void avt440driver::setOutputB(unsigned char b)
{
    outb(0,BASE);
    outb(1,BASE+2);//STROBE 0 INIT 0
    outb(b,BASE);
    usleep(WAIT_TIME);
    outb(0b00000101,BASE+2);//STROBE 0 INIT 1
    usleep(WAIT_TIME);
    outb(1,BASE+2);//STROBE 0 INIT 0
    usleep(WAIT_TIME);
    outb(0,BASE);
    OutB=b;
}

unsigned char avt440driver::getInputA()
{
    unsigned char a=0;
    outb(0,BASE);
    #ifdef DEBUG
    a=inb(BASE);
    printf("a: %d\n",a);
    #endif // DEBUG
    //STROBE ~ AUTO ~ INIT 0 SELECT ~   IRQviaACK 0    bi-directional-mode 0
    outb(STROBE | SELECT | DIRECTION,BASE+2);//STROBE 0 AUTO 0 INIT 0 SELECT 1
    #ifdef DEBUG
    a=inb(BASE);
    printf("a: %d\n",a);
    #endif // DEBUG
    usleep(WAIT_TIME);
    a=inb(BASE);
    outb(STROBE,BASE+2);//STROBE 0 AUTO 1 INIT 0 SELECT 1
    usleep(WAIT_TIME);
    #ifdef DEBUG
    a=inb(BASE);
    printf("a: %d\n",a);
    #endif // DEBUG
    outb(0,BASE);
    InA=a;
    return a;
}

unsigned char avt440driver::getInputB()
{
    unsigned char a=0;
    outb(0,BASE);
    outb(STROBE | AUTO | DIRECTION,BASE+2);//STROBE 0 AUTO 1  INIT 0 SELECT 0
    usleep(WAIT_TIME);//czas na przepisanie z wejsc na wyjscai bufora IC5
    a=inb(BASE);
    outb(STROBE,BASE+2);
    usleep(WAIT_TIME);
    outb(0,BASE);
    InB=a;
    return a;
}

unsigned char avt440driver::getStatusRegister()
{
    unsigned char a=0;
    a=inb(BASE+1);
    return a;
}

void avt440driver::setInputAtoOutputA()
{
    outb(0,BASE);
    outb(0b00001001,BASE+2);//STROBE 0 AUTO 1  INIT 0 SELECT 0
    usleep(WAIT_TIME);
    outb(0b00001000,BASE+2);//STROBE 1 AUTO 1  INIT 0 SELECT 0
    usleep(WAIT_TIME);
    outb(0b00001001,BASE+2);//STROBE 0 AUTO 1  INIT 0 SELECT 0
    usleep(WAIT_TIME);
    outb(STROBE,BASE+2);
    usleep(WAIT_TIME);
}

void avt440driver::setInputBtoOutputB()
{
    #ifdef DEBUG
    unsigned char a=0;
    a=inb(BASE);
    printf("a: %d\n",a);
    #endif // DEBUG
    outb(0,BASE);
    outb(0b00000011,BASE+2);//STROBE 0 AUTO 0  INIT 0 SELECT 1
    usleep(WAIT_TIME);
    #ifdef DEBUG
    a=inb(BASE);
    printf("a: %d\n",a);
    #endif // DEBUG
    outb(0b00000111,BASE+2);//STROBE 0 AUTO 0  INIT 1 SELECT 1
    usleep(WAIT_TIME);
    #ifdef DEBUG
    a=inb(BASE);
    printf("a: %d\n",a);
    #endif // DEBUG
    outb(0b00000011,BASE+2);//STROBE 0 AUTO 0  INIT 0 SELECT 1
    usleep(WAIT_TIME);
    outb(STROBE,BASE+2);
    usleep(WAIT_TIME);
}

//STROBE ~ AUTO ~ INIT 0 SELECT ~   IRQviaACK 0    bi-directional-mode 0
void avt440driver::openInputA()
{
    outb(0,BASE);
    outb(STROBE,BASE+2);
    usleep(WAIT_TIME);
    outb(STROBE | SELECT | DIRECTION,BASE+2);
    usleep(WAIT_TIME);
}

void avt440driver::openInputB()
{
    outb(0,BASE);
    outb(STROBE,BASE+2);
    usleep(WAIT_TIME);
    outb(STROBE | AUTO | DIRECTION,BASE+2);
    usleep(WAIT_TIME);
}

void avt440driver::closeInput()
{
    outb(0,BASE);
    outb(STROBE,BASE+2);
    usleep(WAIT_TIME);
}

unsigned char avt440driver::getInput()
{
    unsigned char a=0;
    a=inb(BASE);
    usleep(WAIT_TIME);
    return a;
}

void avt440driver::setControll(unsigned char c)
{
    outb(c,BASE+2);
    usleep(WAIT_TIME);
}

//STROBE ~ AUTO ~ INIT 0 SELECT ~   IRQviaACK 0    bi-directional-mode 0
unsigned char avt440driver::getControllFromDevice()
{
    unsigned char a=0;
    outb(INIT,BASE+2);//piny rejestru kontrolnego do stanu wysokiej impedancji
    usleep(WAIT_TIME);
    a=inb(BASE+2);//teraz powinno sie dać odczytać co jest po drugiej stronie
    usleep(WAIT_TIME);
    return a;
}

unsigned char avt440driver::getControll()
{
    unsigned char a=0;
    a=inb(BASE+2);//zwykły odczyt rejestru kontrolnego, można zobaczyć czy są jakieś interferencjie ze wcześniej ustawionymi wartościami
    usleep(WAIT_TIME);
    return a;
}




















