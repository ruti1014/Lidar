/*                StepperMaster.h
 * Autor:         ruti1014
 * Beschreibung:  Header File der StepperMaster Bibliothek
 * 
*/

#ifndef StepperMaster_h
#define StepperMaster_h

#include "Arduino.h"


class StepperMaster
{
  public:
    StepperMaster(int PIN_IN1, int PIN_IN2, int PIN_IN3, int PIN_IN4);
    void rotate(bool clockwise);
    void setStepPosition(int pos);
    int getStepPosition();
    void sequence(bool in1, bool in2, bool in3, bool int4);
    void setAbsoluteAngle(double pos);
    double getAbsoluteAngle();
    void setMinInterval(int minInterval);
    int getMinInterval();


  private:
    int _pin_in1;
    int _pin_in2;
    int _pin_in3;
    int _pin_in4;
    int _stepPosition;
    int _minInterval;
    double _absoluteAngle;
};

enum turnDirection
{
  CLOCKWISE = 1,
  COUNTERCLOCKWISE = 0
};


#endif
