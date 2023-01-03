#include "GasStationInfo.h"

GasStationInfo::GasStationInfo(        
        string id,
        string name,
        string brand,
        string street,
        string place,
        double lat,
        double lng,
        string houseNumber,
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
    this->status = src.status.c_str();
    this->id = src.id.c_str();
    this->name = src.name.c_str();
    this->brand = src.brand.c_str();
    this->street = src.street.c_str();
    this->place = src.place.c_str();
    this->lat = src.lat;
    this->lng = src.lng;
    this->dist = src.dist;
    this->diesel = src.diesel; 
    this->e5 = src.e5;
    this->e10 = src.e10;
    this->isOpen = src.isOpen;
    this->houseNumber = src.houseNumber.c_str();
    this->postCode = src.postCode;
}

GasStationInfo::~GasStationInfo()
{
}