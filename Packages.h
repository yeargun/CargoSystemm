#ifndef PACKAGES_H
#define PACKAGES_H
#include <string>
using namespace std;



class Packages{
public:
    Packages();
    Packages(string name);
    ~Packages();
    string getName() const;
    void setName(string name);

private:
    string name;
};

string Packages::getName() const{
    return this->name;
}


Packages::Packages() {

}
Packages::Packages(string name){
    this->name = name;

}
Packages::~Packages(){

}

#endif