#include "GasStationInfo.h"

GasStationInfo::GasStationInfo(        
        string id,
        string name,
        string brand,
        string street,
        string place,
        double lat,
        double lng,
        int houseNumber,
        int postCode
        )
{
    this->id = id;
    this->name = name;
    this->brand = brand;
    this->street = street;
    this->place = place;
    this->lat = lat;
    this->lng = lng;
    this->houseNumber = houseNumber;
    this->postCode = postCode;
}

GasStationInfo::GasStationInfo(const GasStationInfo &src)
{
    this->id = src.id;
    this->name = src.name;
    this->brand = src.brand;
    this->street = src.street;
    this->place = src.place;
    this->lat = src.lat;
    this->lng = src.lng;
    this->dist = src.dist;
    this->diesel = src.diesel; 
    this->e5 = src.e5;
    this->e10 = src.e10;
    this->isOpen = src.isOpen;
    this->houseNumber = src.houseNumber;
    this->postCode = src.postCode;
}

GasStationInfo::~GasStationInfo()
{
}