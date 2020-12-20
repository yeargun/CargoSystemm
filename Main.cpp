#include <iostream>
#include <string>
#include <vector>
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
    for (command; getline(*packages, command);) {
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

//_packages class is for moving truck and its' packages
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
};
_packages* movingTruck = new _packages;
_packages* _packages::head = new _packages;

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

            //getting packages from first station
            for(int i=0;i<x;i++){
                station->packages.getTop(tempPackage);
                if(tempPackage==NULL){
                    cout<<"There's no enough package in first statin\n";
                    return;
                }
                station->packages.pop();
                movingTruck->addPackage(tempPackage);
            }
        }
    }

}
void addAndReleasePacksToMiddle(vector<Station*>* stations, int y, string middleStation,string zValues){
    Truck* tempTruck;
    Packages* tempPackage;
    for(Station* station: *stations){
        if(station->gettName()== middleStation){
            for(int i=0;i<y;i++){//getting packages from middle station
                tempPackage = new Packages();
                if(tempPackage==NULL){
                    cout<<"You cant get that much package from that station\n";
                    return;
                }
                station->packages.getTop(tempPackage);
                station->packages.pop();
                movingTruck->addPackage(tempPackage);
            }

            //releasing the given indeces of packages to middle station
            int iThZvalue;
            vector<int> zvalues;
            vector<string> removedPackageNames;
            _packages* tempNode= movingTruck->head->next;
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
                        break;
                    }
                }
                removedPackageNames.push_back(tempNode->data->getName());
            }
            for(string packageName : removedPackageNames){
                for(tempNode = movingTruck->head->next; tempNode!=NULL ; tempNode=tempNode->next){
                    if(tempNode->data->getName() == packageName){
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
}
void releasingToFinalStation(vector<Station*>* stations,string endStation){
    for(Station* station: *stations) {
        if (station->gettName() == endStation) {
            while(!movingTruck->isEmpty()){
                station->packages.push(
                        movingTruck->popPackage(0) );
            }
            Truck* truck = static_cast<Truck *>(movingTruck->head->data);
            station->trucks.enqueue(truck);
            delete movingTruck;
            break;
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

    //gets the first truck from given station
    //gets the packages from first station
    firstStationToMiddle(stations,x,startingStation);

    //gets y packages from middle station
    //and releases the indexes inside zValues
    addAndReleasePacksToMiddle(stations,y,middleStation,zValues);

    //moving truck reachs the final destination
    //we put truck to garage & we put packages to stack
    releasingToFinalStation(stations,endStation);
}
void printStations(vector<Station*>* stations){
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
    //argument order desk,package,truck,mission,result
    string command;
    ifstream dests, packages, trucks, missions;
    dests.open(argv[1]);
    packages.open(argv[2]);
    trucks.open(argv[3]);
    missions.open(argv[4]);
    output.open(argv[5]);
    vector<Station*> stations;

    setDests(&dests,&stations);
    setTrucks(&trucks,&stations);
    setPackages(&packages,&stations);

    //getting missions
    for (command; getline(missions, command); ) {
        moveTruck(&command,&stations);
    }
    printStations(&stations);
    output.close();
    return 0;
}