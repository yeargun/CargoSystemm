/*Function templates are special functions that can operate
with generic types. This allows us to create a function
template whose functionality can be adapted to more than
one type or class without repeating the entire code for each type.*/

/*To use this function template we use the following format for the function call:

function_name <type> (parameters);
*/
#ifndef QUEUE_H
#define QUEUE_H
#include <iostream>
#include "Output.h"
using namespace std;


template<class T>
class Queue {
public:
	Queue();
	~Queue();
	bool isEmpty() const;
	int size() const;
    void printWhole();
	//Enqueue: Items are added to the back of the queue
	void enqueue(const T& newItem);
	//Dequeue: Items are removed from the front of the queue
	void dequeue();
	//Get Front: Take a look at the first item
	void getFront(T& queueTop) const;
private:
	struct QueueNode {
        T item;
        QueueNode* next;
        QueueNode(){
            this->next=NULL;
        }
    };
    int _size;
	/* to avoid the traversal to the last node,
	 an additional pointer to the last node is defined*/
	QueueNode* _lastNode;
	QueueNode* _headNode;
};


template <typename T>
Queue<T>::~Queue<T>(){
    _size = 0;
}

template <typename T>
void Queue<T>::printWhole(){
    QueueNode* temp = this->_headNode;
    if(temp == NULL){
        return;
    }
    while(temp!=NULL && temp->item !=NULL){
        output << temp->item->getName()<<endl;
        temp = temp->next;
    }
}

template <typename T>
Queue<T>::Queue() {
    this->_size = 0;
}

template <typename T>
bool Queue<T>::isEmpty() const {
    if(this->size() == 0)
        return true;
    return false;
}

template <typename T>
int Queue<T>::size() const {
    return _size;
}


template <typename T>
void Queue<T>::enqueue(const T& newItem) {
    if(this->isEmpty()){
        _lastNode = new QueueNode;
        _lastNode->item = newItem;
        _lastNode->next = NULL;
        _headNode=_lastNode;
    }
    else{
        QueueNode* newNode=new QueueNode;
        _lastNode->next=newNode;
        newNode->item = newItem;
        _lastNode=newNode;
    }
    if(_headNode->next!= NULL)
        cout<<"";
    this->_size++;
}

template <typename T>
void Queue<T>::dequeue() {
    if(this->_size <1){
        cout<<"There's no trucks in station\n";
        return;
    }
    else{
        if(_headNode==NULL){
            cout<<"???\n";
            return;
        }
        else if(_headNode->next==NULL){
            _headNode=NULL;
            _lastNode=NULL;
        }
        else{
            _headNode = _headNode->next;
        }
    }
    this->_size--;
}


template <typename T>
void Queue<T>::getFront(T& queueTop) const {
    if(!isEmpty())
        queueTop = this->_headNode->item;
}


#endif