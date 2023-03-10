//vgl.: https://creativecommons.tankerkoenig.de/?page=info

#ifndef __GasStationInfo_h__
#define __GasStationInfo_h__

#include <string>
using std::string;

class GasStationInfo
{
private:
    string id;
    string name;
    string brand;
    string street;
    string place;
    double lat;//geographische Breite
    double lng;//geographische Laenge
    double dist;//Umkreis
    string houseNumber;
    int postCode;//PLZ
    
public:
    string status;    
    double diesel;//Preis in EUR
    double e5;//Preis in EUR
    double e10;//Preis in EUR
    bool isOpen;
    
public:
    double GetLat(){return lat;}
    double GetLng(){return lng;}
    string GetId(){return id;}
    const char* PrintName();
    const char* PrintBrand();
    
    GasStationInfo(
        string id = "",
        string name = "",
        string brand = "",
        string street = "",
        string place = "",
        double lat = 0.0,
        double lng = 0.0,
        string houseNumber = "",
        int postCode = 0
        );
    //CopyCtor:
    GasStationInfo(const GasStationInfo& src);
    //Destructor
    ~GasStationInfo();
};   

#endif