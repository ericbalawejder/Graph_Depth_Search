// stack in template type form
// http://www.cplusplus.com/reference/stack/stack/

#include <iostream>
#include <new>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>

using namespace std;

// template for structure NodeType of type Type
template <class Type>
struct StackNodeType
{
    Type value;
    StackNodeType<Type>* next;
};

// template for Stack class
template <class Type>
class Stack
{
    public:
        Stack();
        void push(Type);
        bool pop();
        Type& peek();
        bool isEmpty();
        // inStack function checks if node is in Stack
        bool inStack(Type);
        // findTail function finds the bottom of the stack
        Type& findTail();
        // popTail function pops bottom of the stack
        bool popTail();
        // peekTail function checks what is in bottom of stack
        Type& peekTail();

        void printall()
        {
            // printall prints out linked list values
            // if linked list is empty print "NULL"
            if (!pointer)
            {
                cout << "NULL" << endl << endl;
            }
            else
            {
                // print elements in linked list
                StackNodeType<Type>* temp = pointer;
                while (temp)
                {
                    cout << "     " << temp->value->node_value << endl;
                temp = temp->next;
                }
                cout << endl;
            }
        }

    private:
        StackNodeType<Type>*pointer;
};

// template for stack constructor
template <typename Type>
Stack<Type>::Stack()
{
    pointer = NULL;
}

// template for push function
template <typename Type>
void Stack<Type>::push(Type item)
{
    StackNodeType<Type>* current = new StackNodeType<Type>;
    current->value = item;
    // if linked list is empty add the first link
    if (!pointer)
    {
        current->next = NULL;
    }
    // if linked list is not empty, add new link at the head
    else
    {
        current->next = pointer;
    }
    pointer = current;
    //cout << pointer->value->node_value << " has been pushed.\n";
}

// template for pop function
template <typename Type>
bool Stack<Type>::pop()
{
    StackNodeType<Type>* temp = this->pointer;

    // if linked list empty return false
    if (!temp)
    {
        return false;
    }
    // if linked list is not empty delete the head link
    this->pointer = temp->next;
    delete temp;
    return true;
}

// template for popTail function
template <typename Type>
bool Stack<Type>::popTail()
{
    StackNodeType<Type>* temp = pointer;
    StackNodeType<Type>* previous;

    // if linked list is empty return false
    if (!temp)
    {
        return false; 
	}
    else if (!temp->next)
    {
        // if list only has one node
        //cout << temp->value->node_value << " has been popped.\n";
        pointer = NULL;
        return true;
    }
    else 
    {
        // if list has more than one node
        while(temp->next)
        {
            previous = temp;
            temp = temp->next;
        }
        //cout << temp->value->node_value << " has been popped.\n";
        delete temp;
        previous->next = NULL;

        return true;
    }
}

// template for peek function
template <typename Type>
Type& Stack<Type>::peek()
{
    StackNodeType<Type>* temp = pointer;
    // return the value of the head link
    return temp->value;
}

// template for peekTail function
template <typename Type>
Type& Stack<Type>::peekTail()
{
    StackNodeType<Type>* temp = findTail();
    // return the value of the head link
    return temp->value;
}

// template for isEmpty function
template <typename Type>
bool Stack<Type>::isEmpty()
{
    // return true if linked list is empty
    if (!pointer)
    {
        return true;
    }
    // else return false
    else
    {
        return false;
    }
}

// template for inStack function
template <typename Type>
bool Stack<Type>::inStack(Type node)
{
    if (!pointer)
    {
        //cout << "There are no nodes.  Node " << node->node_value << " is not in stack.\n";
        return false;
    }
    else
    {
        StackNodeType<Type>* temp = pointer;
        while(temp) 
        {
            if(temp->value->node_value == node->node_value)
            {
                //cout << "Node " << node->node_value << " is in stack.\n";
                return true;
            }
            temp = temp->next;
        }
        //cout << "Node " << node->node_value << " is not in stack.\n";
        return false;
    }
}

// template for findTail function
template <typename Type>
Type& Stack<Type>::findTail()
{
    StackNodeType<Type>* temp = pointer;
    while(temp->next)
    {
        temp = temp->next;
    }
    // returns node on bottom of stack
    return temp->value;
}
