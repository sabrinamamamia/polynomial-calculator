/*

#include <iostream>
#include <fstream>
#include <stdexcept>
#include "LL.h"

using std::ostream;
using std::endl;
using std::cout;
using std::string;
using std::out_of_range;


//Class LL Implementation
//Defaut constructor
//Note: What is the logic behind this? Sentinel node?

template <typename T>
LL<T>::LL()
{
    head = NULL;
    //cout << "LL Constructor called\n";
    //Node <T> * head;
    //head = new Node <T> ();
    
    //head->next = head->prev->next;
    //head->prev = head->next->prev;
    
    //head->next = head;
    //head->prev = head;
}

//Destructor
template <typename T>
LL<T>::~LL()
{
    if (head == NULL)
    {
        cout << "  List is already empty, nothing to do here.\n";
    }
    else
    {
        clear();
        delete head;                //Head and tail deleted separately from the other nodes
    }
}

//Clear() removes all objects from list and deallocated memory
template <typename T>
void LL<T>::clear()
{
    if (head == NULL)
    {
        cout << "  List is already empty, nothing to do here.\n";
    }
    
    else
    {
        Node<T> *current = head;
        while (current != NULL)
        {
            current = current->next;
            delete head;
            head = current;
        }
    }
}

//Push back function
template <typename T>
void LL<T>::push_back(T c, T e)
{
    if (head == NULL)
    {
        head = new Node<T>(c, e, NULL);
        //head = new Node<T>(c, e, NULL, NULL);
    }
    else
    {
        Node<T> * ptr = head;
        
        while (ptr->next != NULL)
        {
            ptr = ptr->next;
        }
        
        ptr->next = new Node<T>(c, e, NULL);
        //ptr->next = new Node<T>(c, e, NULL, NULL);
    }
    
}

//Insert function results in Node object being inserted by ascending order
//Note: Do you need to account for when the list is empty?
//WORK ON THIS
template <typename T>
void LL<T>::insert(T c, T e)
{
    //Single Linked List
    Node<T> * previousPtr, *ptr;
    
    if ((head == NULL) || (head->exp <= e && head->coeff < c))
    {
        head = new Node<T>(c,e,head);
    }
    
    else
    {
        previousPtr = head;
        ptr = head->next;
        
        while (ptr != NULL && ptr->exp >= e && ptr->coeff >= c)
        {
            previousPtr = ptr;
            ptr = ptr->next;
        }
        previousPtr->next = new Node<T>(c, e, ptr);
    }
    
    
     Doublely linked list
     Node<T> * ptr = head;
     
     if (ptr->exp >= e)
     {
     cout << "insert front" << endl;
     head = new Node<T>(c, e, ptr->next->prev, ptr->next);
     }
     
     else
     {
     while (ptr->exp < e)
     {
     cout << "insert back" << endl;
     ptr = ptr->next;
     }
     ptr->next->prev = ptr->next = new Node<T>(c, e, ptr->next->prev, ptr->next);
     }
    
}

//stream insertion operator
template <typename F>
ostream & operator<<(ostream & os, const LL<F> & rhsObj)
{
    if (rhsObj.head == NULL)
    {
        cout << "Linked list is empty" << endl;
    }
    
    for (Node<F> * ptr = rhsObj.head; ptr != NULL; ptr = ptr->next)
    {
        os << "coeff: " << ptr->coeff << endl;
        os << "exp: " << ptr->exp;
        os << endl;
    }
    return os;
}

*/