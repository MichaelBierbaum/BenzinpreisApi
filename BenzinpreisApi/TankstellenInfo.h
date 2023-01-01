//vgl.: https://creativecommons.tankerkoenig.de/?page=info

#ifndef __TankstellenInfo_h__
#define __TankstellenInfo_h__

#include <string>
using std::string;

class TankstellenInfo
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
    double diesel;//Preis in EUR
    double e5;//Preis in EUR
    double e10;//Preis in EUR
    bool isOpen;
    int houseNumber;
    int postCode;//PLZ
    
public:
    double GetLat(){return lat;}
    double GetLng(){return lng;}
    string GetId(){return id;}
    
    TankstellenInfo(
        string id = "",
        string name = "",
        string brand = "",
        string street = "",
        string place = "",
        double lat = 0.0,
        double lng = 0.0,
        int houseNumber = 0,
        int postCode = 0
        );
    //CopyCtor:
    TankstellenInfo(const TankstellenInfo& src);
    //Destructor
    ~TankstellenInfo();
};

TankstellenInfo RaiBa(
    /*id*/"2599dfbd-54c1-473d-a0df-a1538ba120b6",
	/*name*/"Raiffeisen Lagerhaus GmbH Gaukönigshofen",
	/*brand*/"ZG Raiffeisen Energie",
	/*street*/"Raiffeisenplatz",
	/*place*/"Gaukönigshofen",
	/*lat*/49.634,
	/*lng*/10.0065,
	/*houseNumber*/3,
	/*postCode*/97253
    );
    

#endif