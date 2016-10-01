//
//  LL.h
//  slm243_assignment1
//
//  Created by Sabrina Ma on 9/24/16.
//  Copyright © 2016 Sabrina Ma. All rights reserved.
//

#ifndef COSC160Fall2016P01_LL_h
#define COSC160Fall2016P01_LL_h

#include <iostream>
#include <fstream>
#include <stdexcept>
#include "Stack.h"

using std::ostream;
using std::endl;
using std::cout;
using std::string;
using std::out_of_range;

//Class Node Declaration
template <typename T>
class Node
{
public:
    T coeff, exp;
    Node <T> * prev = NULL;
    Node <T> * next = NULL;
    Node();
    Node(T, T, Node *, Node *);
    //Node(T, T, Node *);
};

// Sentinel
template <typename T>
Node<T>::Node()
{
    //cout << "Sentinel created\n";
    coeff = -1;
    exp = -1;
};

template <typename T>
Node<T>::Node(T c, T e, Node<T> * p, Node<T> * n)
{
coeff = c;
exp = e;
prev = p;
next = n;
}

//Class LL Declaration
template <typename T>
class LL
{
private:
    Node <T> sentinel;
    Node <T> * ptr;
    void copyList(const LL<T> & rhs);
    
public:
    LL();
    ~LL();
    
    LL operator+(const LL<T> & rhsObj);
    LL operator-(const LL<T> & rhsObj);
    LL operator*(const LL<T> & rhsObj);
    
    T getMax(T, T);
    
    void clear();
    void push_back(T, T);
    void insert(T,T);
    
    template <typename F>
    friend ostream & operator<<(ostream & os, LL<F> & rhsObj);
    
    bool empty();
};

//Class LL Implementation
//Defaut constructor
//Note: What is the logic behind this? Sentinel node?

template <typename T>
LL<T>::LL()
{
    //head = NULL;
    //cout << "LL Constructor called\n";

    sentinel.next = &sentinel;
    sentinel.prev = &sentinel;
}

//Destructor
template <typename T>
LL<T>::~LL()
{
    //cout << "Destructor called\n";
    clear();
    //delete sentinel;                //Head and tail deleted separately from the other nodes
}

//Insert function results in Node object being inserted by ascending order
//Note: Do you need to account for when the list is empty?
//WORK ON THIS
template <typename T>
void LL<T>::insert(T c, T e)
{
    ptr = &sentinel;
    
    //If ptr->next is also sentinel, list is empty.
    if (ptr->next == &sentinel || ptr->next->exp < e)
    {
        ptr->next = ptr->next->prev = new Node<T>(c, e, ptr->next->prev, ptr->next);
    }
    
    
    else if (ptr->next->exp > e)
    {
        ptr = ptr->next;
        
        while (ptr->exp > e)
        {
            ptr = ptr->next;
        }
        
            if (ptr->exp == e)
            {
                ptr->coeff += c;
            }
            
            else
            {
                ptr = ptr->prev;
                ptr->next = ptr->next->prev = new Node<T>(c, e, ptr->next->prev, ptr->next);
            }
    }
}

template <typename T>
T LL<T>::getMax(T num1, T num2)
{
    if (num1 > num2)
        { return num1;}
    return num2;
}

//Overloaded addition operator
template <typename T>
LL<T> LL<T>::operator+(const LL<T> & rhsObj)
{
    Node <T> * lhsPtr = this->sentinel.next;
    Node <T> * rhsPtr = rhsObj.sentinel.next;
    LL<int> newLL;
    
    //cout << "Lhs exp: " << lhsPtr->exp << endl;
    //cout << "Rhs exp: " << rhsPtr->exp << endl;

    int max = getMax(lhsPtr->exp, rhsPtr->exp);
    
    //cout << "Max" << max << endl;
    
    for (int i = max; i >= 0; i--)
    {
        int matchCount = 0;
        int newCoeff = 0;
        //cout << "Index: " << i << endl;
        
        while (lhsPtr!= NULL && lhsPtr->exp == i)
        {
            //cout << "Lhs match found." << endl;
            //cout << "lhsPtr->coeff: " << lhsPtr->coeff << endl;
            
            newCoeff += lhsPtr->coeff;
            lhsPtr = lhsPtr->next;
            matchCount++;
            
            //cout << "new Coeff: " << newCoeff << endl;
            //cout << "matchCount: " << matchCount << endl;
        }
        
        
        while (rhsPtr!= NULL && rhsPtr->exp == i)
        {
            //cout << "rhs match found." << endl;
            //cout << "rhsPtr->coeff: " << rhsPtr->coeff << endl;
            
            newCoeff += rhsPtr->coeff;
            rhsPtr = rhsPtr->next;
            matchCount++;
            
            //cout << "new Coeff: " << newCoeff << endl;
            //cout << "matchCount: " << matchCount << endl;
        }
        
        if (matchCount > 0)
        {
            //cout << "new coeff " << newCoeff << " inserted into LL \n";
            newLL.insert(newCoeff, i);
        }
        else
        {
            continue;
        }
    }
    return newLL;
}

//Overloaded subtraction operator
template <typename T>
LL<T> LL<T>::operator-(const LL<T> & rhsObj)
{
    Node <T> * lhsPtr = this->sentinel.next;
    Node <T> * rhsPtr = rhsObj.sentinel.next;
    LL<int> newLL;
    
    //cout << "Lhs exp: " << lhsPtr->exp << endl;
    //cout << "Rhs exp: " << rhsPtr->exp << endl;
    
    int max = getMax(lhsPtr->exp, rhsPtr->exp);
    
    //cout << "Max" << max << endl;
    
    for (int i = max; i >= 0; i--)
    {
        int matchCount = 0;
        int newCoeff = 0;
        //cout << "Index: " << i << endl;
        
        while (lhsPtr!= NULL && lhsPtr->exp == i)
        {
            //cout << "Lhs match found." << endl;
            //cout << "lhsPtr->coeff: " << lhsPtr->coeff << endl;
            
            //lhs added to newCoeff
            newCoeff += lhsPtr->coeff;
            lhsPtr = lhsPtr->next;
            matchCount++;
            
            //cout << "new Coeff: " << newCoeff << endl;
            //cout << "matchCount: " << matchCount << endl;
        }
        
        
        while (rhsPtr!= NULL && rhsPtr->exp == i)
        {
            //cout << "rhs match found." << endl;
            //cout << "rhsPtr->coeff: " << rhsPtr->coeff << endl;
            
            //lhs subtracted from newCoeff
            newCoeff -= rhsPtr->coeff;
            rhsPtr = rhsPtr->next;
            matchCount++;
            
            //cout << "new Coeff: " << newCoeff << endl;
            //cout << "matchCount: " << matchCount << endl;
        }
        
        if (matchCount > 0)
        {
            //cout << "new coeff " << newCoeff << " inserted into LL \n";
            newLL.insert(newCoeff, i);
        }
        else
        {
            continue;
        }
    }
    return newLL;
}

//Overloaded multiplication operator
template <typename T>
LL<T> LL<T>::operator*(const LL<T> & rhsObj)
{
    Node <T> * lhsPtr;
    Node <T> * rhsPtr;
    LL<int> newLL;
    
    for (lhsPtr = this->sentinel.next; lhsPtr != this->sentinel.prev->next; lhsPtr = lhsPtr->next)
    {
//        cout << "lhsPtr->coeff " << lhsPtr->coeff << endl;
//        cout << "lhsPtr->exp " << lhsPtr->exp << endl;
//        
    for (rhsPtr = rhsObj.sentinel.next; rhsPtr != rhsObj.sentinel.prev->next; rhsPtr = rhsPtr->next)
    {
//        cout << "rhsPtr->coeff " << rhsPtr->coeff << endl;
//        cout << "rhsPtr->exp " << rhsPtr->exp << endl;
//        
//        
//        cout << "new coeff " << rhsPtr->coeff * lhsPtr->coeff << endl;
//        cout << "new exp " << rhsPtr->exp + lhsPtr->exp << endl;
//        
        newLL.insert((rhsPtr->coeff * lhsPtr->coeff), (rhsPtr->exp + lhsPtr->exp));
    }
    }
    return newLL;
}

//stream insertion operator
template <typename F>
ostream & operator<<(ostream & os, LL<F> & rhsObj)
{

    Node<F>* ptr = rhsObj.sentinel.next;
    os << ptr->coeff << "x^" << ptr->exp;
    for (ptr = ptr->next; ptr != rhsObj.sentinel.prev->next; ptr = ptr->next)
    {
        if (ptr->coeff > 0)
        { os << " + " << ptr->coeff << "x^" << ptr->exp; }
        
        else if (ptr->coeff < 0)
        { os << " " << ptr->coeff << "x^" << ptr->exp; }
    }
    
    return os;
}

//Clear() removes all objects from list and deallocated memory
template <typename T>
void LL<T>::clear()
{
    /*
    Node<T> * ptr = new Node<T>;
    
    Node<T> * temp = new Node<T>;
    
    ptr = sentinel.next;
    //temp = &sentinel.next;
    
    while (ptr != &sentinel)
    {   temp = ptr;
        ptr = ptr->next;
        delete temp;
    }
    
    delete ptr;

    */
}

template <typename T>
bool LL<T>::empty() 
{
    
    if (ptr->next == &sentinel)
    {
        return true;
    }
    else
    {
        return false;
    }
}

#endif