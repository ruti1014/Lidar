/*                LidarMaster.h
 * Autor:         ruti1014
 * Beschreibung:  Header File der LidarMaster Bibliothek
 * 
*/

#ifndef LidarMaster_h
#define LidarMaster_h

#include "Arduino.h"



class LidarMaster
{
  public:
    LidarMaster(int ic2Adress);
    uint16_t getDistance();
    uint16_t getAmp();
    uint16_t getTemperatur();
    int getAdress();


  private:
    uint16_t readIC216B(int reg);
    void selectRegister(int reg);
    void writeData(int reg, byte value);

    int _adress;

};

#endif
