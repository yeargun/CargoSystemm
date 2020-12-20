#include "Packages.cpp"

using namespace std;

class Truck : public Packages {
    string motorPower;
    string position;
    bool _isMoving;
public:
    Truck(string name1, string name, string position, string power) : Packages(name) {
        this->motorPower=power;
        this->position=position;
    }

    bool isMoving(){
        return this->_isMoving;
    }
    string getMotorPower(){
        return  this->motorPower;
    }
    string getName(){
        return Packages::getName();
    }
    struct node{
        Packages* package;
        node* nextNode;
        node* prevNode;
    };
    node* head;
    node* tail;


};