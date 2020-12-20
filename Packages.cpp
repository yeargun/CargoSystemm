#include <iostream>

class Packages{
private:
    std::string name;
public:
    Packages(){}
    Packages(std::string name){
        this->name=name;
    }
    ~Packages(){}
    std::string getName() const{
        return this->name;
    }
    void setName(std::string name){
        this->name=name;
    }
};
