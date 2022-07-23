#ifndef STACK
#define STACK
#include<iostream>
#include<stdlib.h>
#include <cstdlib>
using namespace std;
class Stack
{
private:
    static const int MaxInt = 256;
    int stack[MaxInt];
    int top;
public:
    Stack() { top = -1; }
    bool StackisEmpty();
    bool StackisFull();
    int PopItem();
    void PushItem(int x);
    void displaystack();
    int SizeOfStack();
};
#endif