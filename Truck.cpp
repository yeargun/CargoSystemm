#include "Packages.cpp"

using namespace std;


class Truck : public Packages {
    string motorPower;
    string position;
public:
    Truck(string name1, string name, string position, string power) : Packages(name) {
        this->motorPower=power;
        this->position=position;
    }
    string getName(){
        return Packages::getName();
    }
};