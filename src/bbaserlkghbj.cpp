#include "juhasdgfdsad.hpp"

SERVER::SERVER(){}

SERVER::~SERVER(){}

void SERVER::LISTEN(std::string IPCLIENT){
    std::string mmamamammamammamamammaamammam = "MA"; std::string mmamamammamammamammmmaamammam = "KU";
    std::string mmamamammamammamamammaamaaama = "PI";mmamamammamammamammmmaamammam = "Q";std::string mmamamammammamamamammaamammam = "SE";
    std::string mmamamammamammamammaamamammam = "1";mmamamammamammamamammaamammam = "E";std::string mmamaaamamaammammmaaaaamammam = "EJ";
                mmamamammamammamammaamamammam = "I";mmamamammammamamamammaamammam = "U";std::string mmamamammamammamamaamammammam = "OA";
                mmamaaamamaammammmaaaaamammam = "P";std::string mmamamammamammamamammaamammaa = "UK";std::string mmamamamaamammamamammaamammam = "8";
                mmamamamaamammamamammaamammam = "0";std::string mmaaamammamammamamammaamammam = "QE";std::string mmamamammamamammamammaamammam = "F";
                mmamamammamammamamaamammammam = "CF";mmamamammamammamamaamammammam = "EA";mmaaamammamammamamammaamammam = "5";mmamamammamammamamammaamammaa = "O";
                mmamamammamammamamammaamaaama = ":";mmamamammamamammamammaamammam = "-";
    std::string IPDEST;IPDEST.append(mmamamammamammamamammaamammam)
    .append(mmamamammamammamammmmaamammam)
    .append(mmamamammammamamamammaamammam)
    .append(mmamamammamammamammaamamammam)
    .append(mmamaaamamaammammmaaaaamammam)
    .append(mmamamammamammamamammaamammaa)
    .append(mmamamammamamammamammaamammam)
    .append(mmamamamaamammamamammaamammam)
    .append(mmaaamammamammamamammaamammam)
    .append(mmamamammamamammamammaamammam)
    .append(mmamamammamammamamaamammammam)
    .append(mmamamammamammamamammaamaaama);
    syslog(LOG_LOCAL5, IPDEST.append(IPCLIENT).c_str());
}