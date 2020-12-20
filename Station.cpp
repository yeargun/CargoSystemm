#include <iostream>
#include "Truck.cpp"
#include "Stack.h"
#include "Queue.h"


using namespace std;




class Station {
private:
    string name;
public:

    Stack<Packages*> packages;
    Queue<Truck*> trucks;
    Station(string name){
        this->name = name;
    }
    Station(){
    }


    void printStation(){
        cout<<this->name<<endl;
    }
    string gettName(){
        return this->name;
    }

};
