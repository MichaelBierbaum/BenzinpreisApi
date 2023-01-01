#include "TankerkoenigWrapper.h"

#include <stdexcept>
using std::exception;

char buff[200];

TankerkoenigWrapper::TankerkoenigWrapper(TankstellenInfo &tankstelle)
{
    this->tankstelle = tankstelle;
};

TankerkoenigWrapper::~TankerkoenigWrapper()
{
}

string TankerkoenigWrapper::CreateUmkreissuche(Spritsorte type)
{
    //example:
    //return "https://creativecommons.tankerkoenig.de/json/list.php?lat=49.6339&lng=10.00658&rad=2.0&sort=dist&type=all&apikey=00000000-0000-0000-0000-000000000002";
    snprintf(buff, sizeof(buff), 
        "https://creativecommons.tankerkoenig.de/json/list.php?lat=%f&lng=%f&rad=0.0&sort=%s&type=%s&apikey=%s",
        this->tankstelle.GetLat(),
        this->tankstelle.GetLng(),
        "dist", //price, dist
        this->Sorten[type],
        this->key);
    return buff;
}

string TankerkoenigWrapper::CreateDetailabfrage()
{
    string id = this->tankstelle.GetId();
    if(id.empty())
        throw new exception("TankstellenId = \"\"");

    //example:
    //return "https://creativecommons.tankerkoenig.de/json/detail.php?id=24a381e3-0d72-416d-bfd8-b2f65f6e5802&apikey=00000000-0000-0000-0000-000000000002";
    snprintf(buff, sizeof(buff),
        "https://creativecommons.tankerkoenig.de/json/detail.php?id=%s&apikey=%s",
        id,
        this->key);
    return buff;
}
