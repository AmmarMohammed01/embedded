#ifndef __HELPER_H__
#define __HELPER_H__
#include "usart.h"
#include "led.h"
void printPhrase(char* message, unsigned int msgLength);
void interpret();
void printMemory(char * charByte);
#endif
