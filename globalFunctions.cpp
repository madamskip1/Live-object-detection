#include "globalFunctions.hpp"

#include <unistd.h>
#include <iostream>


void CreateProc(int (*func)(int arg, char *tab[]),
                int arg,
                char *tab[])
{
    int res = fork();
    if (res == 0)
    {
        func(arg, tab);
        exit(0);
    }
}
void CreateProcInt(int (*func)())
{
    int res = fork();
    if (res == 0)
    {
        func();
        exit(0);
    }
}

void printError(std::string str)
{
    std::cout << str;
    exit(1);
}

void delay(double seconds)
{
    int ticks_per_sec = 1000000 * seconds;
    clock_t start_time = clock();
    while (clock() < start_time + ticks_per_sec)
        ;
}
