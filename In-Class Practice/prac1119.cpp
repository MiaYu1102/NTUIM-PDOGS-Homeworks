#include<bits/stdc++.h>
using namespace std;

class Entity
{
protected:
  string id;
  bool isOn; 
  bool isSer; // means nothing if isOn == false
  double lon;
  double lat;
public: 
  Entity(string id, bool isOn, bool isSer, double lon, double lat);
  void print();
};


Entity::Entity(string id, bool isOn, bool isSer, double lon, double lat)
  : id(id), isOn(isOn), isSer(isSer), lon(lon), lat(lat)
{
}

void Entity::print()
{
  cout << this->id << ": " << this->isOn << " " << this->isSer
       << " (" << this->lon << ", " << this->lat << ")" << endl;
}

class Car : public Entity
{
private:
public:
  Car(string id, bool isOn, bool isSer, double lon, double lat);
  void print();
};

Car::Car(string id, bool isOn, bool isSer, double lon, double lat)
: Entity(id, isOn, isSer, lon, lat)
{
}
void Car::print()
{
    cout << this->id << ": ";
    if(this->isOn){
        if(this->isSer){
            cout<<"in-service, (";
        }
        else{
            cout<<"empty, (";
        }
        cout << this->lon << "," << this->lat <<")";
    }
    else
        cout<<"offline";
    cout<<endl;
}

class CarArray
{
private:
    int capacity; // initialize it to 20000; may change later
    int cnt;
    Car** carPtr;
    public:
    CarArray();
    // CarArray(const CarArray& ca); // not needed
    // operator=(const CarArray& ea); // in this problem
    ~CarArray();
    bool add(string id, bool isOn, bool isSer, double lon, double lat);
    void print();
};

CarArray::CarArray()
{
    this->cnt = 0;
    this->capacity = 20000;
    this->carPtr = new Car*[this->capacity];
}
CarArray::~CarArray()
{
    for(int i = 0; i < this->cnt; i++)
        delete this->carPtr[i];
    delete [] this->carPtr;
}

bool CarArray::add(string id, bool isOn, bool isSer, double lon, double lat)
{
    if(this->cnt < this->capacity){
        this->carPtr[cnt] = new Car(id, isOn, isSer, lon, lat);
        this->cnt++;
        return true;
    }
    else
        return false;
}

void CarArray::print(){
    for(int i=0; i<this->cnt; i++)
        this->carPtr[i]->print();
}

class Passenger : public Entity
{
private:
public:
    Passenger(string id, bool isOn, bool isSer, double lon, double lat);
    void print();
};

Passenger::Passenger(string id, bool isOn, bool isSer, double lon, double lat)
: Entity(id, isOn, isSer, lon, lat)
{
}
void Passenger::print()
{
    cout << this->id << ": ";
    if(this->isOn){
        if(this->isSer){
            cout<<"in-service, (";
        }
        else{
            cout<<"waiting, (";
        }
        cout << this->lon << "," << this->lat <<")";
    }
    else
        cout<<"offline";
    cout<<endl;

}

int main()
{
    Car c("5HE-313", true, false, 0, 0);
    c.print();

    Passenger p("B90705023", true, false, 0, 0);
    p.print();
    return 0;
}
