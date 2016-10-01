//
//  Stack.h
//  slm243_assignment1
//
//  Created by Sabrina Ma on 9/24/16.
//  Copyright © 2016 Sabrina Ma. All rights reserved.
//

#ifndef Stack_h
#define Stack_h

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include "LL.h"

using std::ostream;
using std::endl;
using std::cout;
using std::string;
using std::out_of_range;

template <typename T>
class Stack
{
private:
    T * stackArray;
    int capacity;
    int top;

public:
    Stack(int capacity);
    ~Stack () { delete[] stackArray; }
    
    void push(T);
    void pop();
    T & getTop() const;
    bool empty();
    
    //Note: do I need stack exceptions?
};

template <typename T>
Stack<T>::Stack(int capacity)
{
    this->capacity = capacity;
    stackArray = new T[capacity];
    top = -1;
}

//Note: review this
template <typename T>
void Stack <T>::push(T value)
{
    top++;
    stackArray[top] = value;
}

template <typename T>
void Stack<T>::pop()
{
    if (empty())
    {
        //cout << "Stack is empty\n";
    }
    else
    {
        T temp = stackArray[top-1];
        top--;
        temp = stackArray[top];
    }

}

template <typename T>
T & Stack<T>::getTop() const
{
    return stackArray[top];
}

template <typename T>
bool Stack<T>::empty()
{
    if (top == 0)
    {
        return true;
    }
    
    else
    {
        return false;
    }
}

#endif