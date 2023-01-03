#ifndef __TankerkoenigWrapper_h__
#define __TankerkoenigWrapper_h__

#include <string>
using std::string;

#include "GasStationInfo.h"

// Key für den Zugriff auf die freie Tankerkoenig-Spritpreis-API
// Fuer eigenen Key bitte hier https://creativecommons.tankerkoenig.de
// registrieren.
class TankerkoenigWrapper
{
private:
    GasStationInfo gasStations[3];//tankstelle
    string key;
    bool ParseJsonForDetailrequest(string &jsonData);
    bool ParseJsonForPrices(string &jsonData);

public:
    enum Spritsorte{e5, e10, diesel, all};
    string Sorten[4] = {"e5", "e10", "diesel", "all"};

public:
    string GetJson();
    bool UpdatePrices(string &jsonData);
    TankerkoenigWrapper(const char *tankerkoenig_api_key);
    ~TankerkoenigWrapper();
    string CreateUrlForRadiusSearch(Spritsorte type = all, double radius = 1.0);
    string CreateUrlForDetailrequest(const char *gasStationID = "");
    string CreateUrlForPrices();
};


/*Umkreissuche
    Parameter	Bedeutung	                            Format
    ------------------------------------------------------------------------------------
    lat     	geographische Breite des Standortes	    Floatingpoint-Zahl
    lng	        geographische Länge	                    Floatingpoint-Zahl
    rad	        Suchradius in km                    	Floatingpoint-Zahl, max: 25
    type	    Spritsorte	                            'e5', 'e10', 'diesel' oder 'all'
    sort	    Sortierung	                            price, dist (1)
    apikey	    Der persönliche API-Key 	            UUID

    wobei:
    (1) Bei type=all wird immer nach Entfernung sortiert - die Angabe der Sortierung ist dann optional
*/

#endif