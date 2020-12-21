#ifndef GLOBALFUNCTIONS_HPP_
#define GLOBALFUNCTIONS_HPP_

#include "globalVariables.h"
#include <string>

void CreateProc(int (*func)(int arg, char *tab[]),
                int arg,
                char *tab[]);

void CreateProcInt(int (*func)());

void printError(std::string str);

void delay(double seconds);


#endif /* GLOBALFUNCTIONS_HPP_ */
