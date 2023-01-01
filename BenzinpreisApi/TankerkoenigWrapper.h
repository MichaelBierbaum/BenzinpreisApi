#ifndef __TankerkoenigWrapper_h__
#define __TankerkoenigWrapper_h__

#include <string>
using std::string;

#include "TankstellenInfo.h"
#include "credentials.h"

class TankerkoenigWrapper
{
private:
    TankstellenInfo tankstelle;
    string key = tankerkoenig_api_key;

public:
    enum Spritsorte{e5, e10, diesel, all};
    string Sorten[4] = {"e5", "e10", "diesel", "all"};
    TankerkoenigWrapper(TankstellenInfo &tankstelle);
    ~TankerkoenigWrapper();
    string CreateUmkreissuche(Spritsorte type = all);
    string CreateDetailabfrage();
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