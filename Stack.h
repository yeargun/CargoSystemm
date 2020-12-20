/*Function templates are special functions that can operate
with generic types. This allows us to create a function
template whose functionality can be adapted to more than
one type or class without repeating the entire code for each type.*/

/*To use this function template we use the following format for the function call:

function_name <type> (parameters);

*/
#ifndef STACK_H
#define STACK_H
#include "Output.h"



template <typename T>
class Stack {
public:
	Stack();
	~Stack();
	bool isEmpty() const;
	int size() const;

	//Push: Place item on top of the stack
	void push(const T& newItem);
	//Top: Take a look at the topmost item without removing it
	void getTop(T& stackTop) const;
	//Pop: Remove item from the top of the stack
	void pop();
	void printWhole();
private:
	struct ListNode {
		T item;
		ListNode* next;
	};
	ListNode* top;
	ListNode* _last;
	int _size;
};

template <typename T>
Stack<T>::~Stack(){}


template <typename T>
Stack<T>::Stack(){
    this->_size = 0;
}



template <typename T>
int Stack<T>::size() const {
    return this->_size;
}

template <typename T>
bool Stack<T>::isEmpty() const {
    if(this->_size == 0)
        return true;
    return false;
}

template <typename T>
void Stack<T>::printWhole(){
    for(ListNode* temp = top;temp!= NULL;temp=temp->next)
        output<<temp->item->getName()<<endl;
}


template <typename T>
void Stack<T>::push(const T& newItem){
    if(this->isEmpty()){
        _last = new ListNode;
        _last->next = NULL;
        _last->item = newItem;
        top = _last;
    }
    else{
        ListNode* newNode = new ListNode;
        newNode->item = newItem;
        newNode->next = top;
        top = newNode;
    }
    this->_size++;
}


template <typename T>
void Stack<T>::getTop(T& stackTop) const{
    if(top==NULL){
        cout<<"theres nothing to pop, stack is empty\n";
        return;
    }
    stackTop = top->item;
}

template <typename T>
void Stack<T>::pop(){
    if(top==NULL){
        cout<<"theres nothing to pop, stack is empty\n";
        return;
    }
    else if(top->next==NULL){
        top=NULL;
        _last = NULL;
    }
    else{
        ListNode* tempNode = top->next;
        delete top;
        top = tempNode;
        this->_size--;
    }
}


#endif


