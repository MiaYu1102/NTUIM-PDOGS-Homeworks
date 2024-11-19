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
};

Car::Car(string id, bool isOn, bool isSer, double lon, double lat)
: Entity(id, isOn, isSer, lon, lat)
{
}


int main()
{
    Car a("5HE-313", true, true, 0, 0);
    a.print();
    return 0;
}
