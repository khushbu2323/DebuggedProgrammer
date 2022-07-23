
#include<iostream>
#include<stdlib.h>
#include <cstdlib>
#include "stack.hpp"
// This Function Will check Underflow of stack
bool Stack::StackisEmpty()
{
    if(top == -1)
        return true;
    return false;
}

// This Function Will check Overflow of stack
bool Stack::StackisFull()
{
    if(top == MaxInt - 1)
        return true;
    return false;
}

//This will pop an element from stack
int Stack::PopItem()
{
    if(StackisEmpty())
    {
        cout<<"Stack Is Empty";
        abort();
    }
    int x = stack[top];
    top--;
    return x;
}

//This function will insert an element to stack
void Stack::PushItem(int x)
{
    if(StackisFull())
    {
        cout<<"Stack Is Full";
        abort();
    }
    top++;
    stack[top] = x;
}

int Stack ::SizeOfStack()
{
    cout<<"Size of Stack is"<<endl;
    return top+1;
}
//this function will display elements of stack
  void Stack::displaystack(){
        if(top==-1){
            cout<<"\n No Element Present In Stack..";
        }
        else{
            cout<<"\nElement of the Stack is..";
            int temtop=top;
            while(temtop!=-1){
                cout<<stack[temtop]<<" ";
                temtop--;
            }
        }
    }
int main()
{

 Stack s;
    int choice,val;
       
        cout<<"\n Choose Your Operation For stack  : \n1) Push an Item To Stack \n2) Pop an Item From Stack \n3) Display The Elements Of Stack \n4) Find size of stack \n5) Exit ";
        while(1){
            cout<<"\nEnter your Chocie: ";
            cin>>choice;
            if(choice==1){
                cout<<"\nEnter the element to be inserted in stack.";
                cin>>val;
                s.PushItem(val);
            }
            else if(choice==2){
               s.PopItem();
            }
            else if(choice==3){
                s.displaystack();
            }
            else if(choice==4){
                s.SizeOfStack();
            }
            else break;
        }

    return 0;
}