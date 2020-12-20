#include <iostream>

class Packages{
public:
    Packages(){

    }
    Packages(std::string name){
        this->name=name;
    }
    ~Packages(){

    }
    std::string getName() const{
        return this->name;
    }
    void setName(std::string name){
        this->name=name;
    }

private:
    std::string name;
};
