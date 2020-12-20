#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Station.cpp"

using namespace std;
string charArrayToString(char* a, int size) { //
    int i;
    string s;
    for (i = 0; i < size; i++) {
        s += a[i];
    }
    return s;
}
bool strCompare(string s1, string s2, int compareLength) { // returns true if strings are identical
    if (compareLength > s1.length() || compareLength > s2.length()) { return false; }
    for (int i = 0; i < compareLength; i++) {
        if (s1[i] != s2[i]) {
            return false;
        }
    }
    return true;
}
string stringSplitter(const string* string1, const char parameter, int index) { // splits the string by the given parameter
//and returns the preffered indexed string from splitted strings
    char* buffer = new char[string1->length()];
    int splitTime = -1;
    int bufferIndex = 0;
    for (char c : *string1) {
        if (c != parameter) {
            *(buffer + bufferIndex) = c;
            bufferIndex++;
        }
        else {
            splitTime++;
            if (splitTime == index) {
                return charArrayToString(buffer, bufferIndex);
            }
            bufferIndex = 0;
        }
    }
    if(index>splitTime+1)
        return "NULL";
    return charArrayToString(buffer, bufferIndex);
}
void setPackages(ifstream* packages, vector<Station*>* stations) {
    string command;
    string initialPosition;
    string packageName;
    for (command; getline(*packages, command); ) {
        packageName = stringSplitter(&command,' ',0);
        initialPosition = stringSplitter(&command,' ',1);
        Packages* newPackage;
        for(auto station: *stations){
            if(station->gettName()== initialPosition){

                newPackage = new Packages(packageName);
                station->packages.push(newPackage);
            }
        }
    }
}
bool contains(vector<int> v,int x){
    if(find(v.begin(), v.end(), x) != v.end())
        return true;
    return false;
    }
void setDests(ifstream* dests, vector<Station*>* stations) {
    string command;
    Station* newStation;
    for (command; getline(*dests, command); ) {
        newStation = new Station(command);
        stations->push_back(newStation);
    }
}


void setTrucks(ifstream* trucks, vector<Station*>* stations){
    string command;
    string initialPosition;string truckName;string power;
    Truck* tempTruck;
    for (command; getline(*trucks, command); ) {
        truckName = stringSplitter(&command,' ',0);
        initialPosition = stringSplitter(&command,' ',1);
        power = stringSplitter(&command,' ',2);
        for(Station* station: *stations){
            if(station->gettName()== initialPosition){
               tempTruck = new Truck(truckName, truckName, initialPosition, power);
               station->trucks.enqueue(tempTruck);
            }
        }
    }
}




//_packages is for moving truck and its' packages
class _packages{
public:
    static _packages* head;
    Packages* data;
    _packages* next;
    _packages* prev;

    _packages(){}
    _packages(Truck* truck){//we use _packages to implement moving truck
        //when we initialize the object with a truck object. This constructor puts the truck* to head
        this->head = new _packages;
        this->head->data = truck;
        this->head->next= NULL;
        this->head->prev = NULL;
    }

    void addPackage(Packages* newPackage){
        _packages* tempPackage = this->head;
        for(; tempPackage->next!=NULL;tempPackage=tempPackage->next){}
        tempPackage->next = new _packages();
        tempPackage->next->data = newPackage;
        tempPackage->next->prev = tempPackage;
        tempPackage->next->next = NULL;
    }

    Packages* popPackage(int index){
        _packages* tempPackage = this->head;
        for(int i=-1; tempPackage!=NULL;tempPackage=tempPackage->next, i++){
            if(i==index){
                tempPackage->prev->next = tempPackage->next;
                //if the element that we wanna pop isnt at the end of the list
                //we change next nodes prev
                if(tempPackage->next!=NULL){
                    tempPackage->next->prev = tempPackage->prev;
                }
                return tempPackage->data;
            }
        }
        return NULL;
    }
    void printWhole(){
        _packages* temp=head;
        if(head==NULL){
            return;
        }
        for(;temp!=NULL;temp=temp->next){
            cout<<temp->data->getName() <<" ";
        }
        cout<<endl;
    }
    bool isEmpty(){
        if(head->next==NULL)
            return true;
        return false;
    }
    int size(){
        int i = 0;
        for(_packages* temp=head;temp!=NULL;temp=temp->next){
            i++;
        }
        return i-1;
    }
};
_packages* movingTruck = new _packages;
_packages* _packages::head = new _packages;


//gets the first truck from given station
//gets the packages from first station
void firstStationToMiddle(vector<Station*>* stations,int x,string startingStation){
    Truck* tempTruck;
    Packages* tempPackage;
    for(Station* station: *stations){
        if(station->gettName()== startingStation){
            station->trucks.getFront(tempTruck);
            if(tempTruck==NULL){
                cout<<"There's no truck to be used in this station("<<station->gettName()<<")\n";
                return;
            }
            station->trucks.dequeue();
            movingTruck = new _packages(tempTruck);
//          getting packages from first station
            for(int i=0;i<x;i++){
//               station->packages.printWhole();
                station->packages.getTop(tempPackage);
                if(tempPackage==NULL){
                    cout<<"There's no enough package in first statin\n";
                    return;
                }
                station->packages.pop();
                movingTruck->addPackage(tempPackage);
            }
//           break;
        }
    }

}




void moveTruck(string* command, vector<Station*>* stations){
    string startingStation = stringSplitter(command,'-',0);
    string middleStation = stringSplitter(command,'-',1);
    string endStation = stringSplitter(command,'-',2);
    int x = stoi(stringSplitter(command,'-',3));
    int y = stoi(stringSplitter(command,'-',4));
    const string zValues = stringSplitter(command,'-',5);
    Truck* tempTruck;
    Packages* tempPackage;


    firstStationToMiddle(stations,x,startingStation);






    cout<<"\n\nAfter getting packages from first station\n";
    movingTruck->printWhole();
//
//
//
    //adding packages from middle station to moving truck
    for(Station* station: *stations){
        if(station->gettName()== middleStation){
            for(int i=0;i<y;i++){
                cout<<i<<endl;
                tempPackage = new Packages();
                if(tempPackage==NULL){
                    cout<<"you cant get that much package from that station\n";
                    return;
                }
                station->packages.getTop(tempPackage);
                station->packages.pop();
                movingTruck->addPackage(tempPackage);
            }

            cout<<"After adding packages from middle station\n";
            movingTruck->printWhole();


            //releasing the given indeces of packages to middle station
            int iThZvalue;
            vector<int> zvalues;
            vector<string> removedPackageNames;
            _packages* tempNode= movingTruck->head->next;
            _packages* copyTruck = new _packages();
            for(int i=0;;i++){ //seperating the z indices at string
                if(stringSplitter(&zValues,',',i) == "NULL"){
                    break;
                }
                iThZvalue = stoi(stringSplitter(&zValues,',',i));
                zvalues.push_back(iThZvalue);
            }
            for(int i: zvalues){        //it stores the names of given indices, with given order
                tempNode= movingTruck->head->next;//That will ease to remove the given indeces from linked list
                for(int k= 0;k<i;k++){
                    tempNode=tempNode->next;
                    if(tempNode==NULL){
                        cout<<"given index to removve from middle station is too big .. \n";
                        break;
                    }
                }
                removedPackageNames.push_back(tempNode->data->getName());
            }
            for(string packageName : removedPackageNames){
                //cout<<"to be removed package name-> "<<packageName<<endl;
                for(tempNode = movingTruck->head->next; tempNode!=NULL ; tempNode=tempNode->next){

                //for(tempNode = movingTruck->head->next; tempNode->next!=NULL && tempNode!=NULL;tempNode = tempNode->next){
                    if(tempNode->data->getName() == packageName){
                        //cout<<"This get removed from truck to middle station -> "<<packageName<<endl;
                        if(tempNode->next==NULL & tempNode->prev==movingTruck->head){//if there s only 1 package in truck
                            movingTruck->head->next = NULL;
                        }
                        else if(tempNode->next ==NULL){ //if the given element is at the end of the linked list
                            tempNode->prev->next=NULL;
                        }
                        else{
                            tempNode->prev->next = tempNode->next;
                            tempNode->next->prev = tempNode->prev;
                        }
                        station->packages.push(tempNode->data);
                    }
                }
            }
           break;
        }
    }
    cout<<"after releasing packages to middle station\n";
    movingTruck->printWhole();

    //moving truck reachs the final destination
        //we put truck to garage & we put packages to stack
    for(Station* station: *stations) {
        if (station->gettName() == endStation) {
            while(!movingTruck->isEmpty()){
                station->packages.push(
                        movingTruck->popPackage(0) );
                       // movingTruck->popPackage(0);
                       // movingTruck->popPackage(0);
            }
            Truck* truck = static_cast<Truck *>(movingTruck->head->data);
            //cout<<"this truck enters last station garage "<<truck->getName()<<endl;
            station->trucks.enqueue(truck);
            delete movingTruck;
            break;
        }
    }
}
void finalStations(vector<Station*>* stations){
    for(Station* station: *stations){
        output<<station->gettName()<<endl;
        output<<"Packages:\n";
        station->packages.printWhole();
        output<<"Trucks:\n";
        station->trucks.printWhole();
        output<<"-------------\n";
    }
}




int main(int argc, char* argv[]) {
    //desk1,package2,truck3,mission4,result5
    string command;
    ifstream dests, packages, trucks, missions;
    dests.open("dests.txt");
    packages.open("packages.txt");
    trucks.open("trucks.txt");
    missions.open("missions.txt");
    output.open("myOut.txt");
    vector<Station*> stations;


    setDests(&dests,&stations);
    setTrucks(&trucks,&stations);
    setPackages(&packages,&stations);



    //getting missions
    for (command; getline(missions, command); ) {
        //cout << command << endl;
       // finalStations(&stations);
        moveTruck(&command,&stations);
        //finalStations(&stations);
    }
    finalStations(&stations);


    output.close();
    return 0;
}