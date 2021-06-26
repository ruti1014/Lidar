/*                Gimbal.h
 * Autor:         ruti1014
 * Beschreibung:  Header File der Gimbal Bibliothek
 * 
*/

#ifndef GIMBAL_H
#define GIMBAL_H

#include "Arduino.h"
#include "StepperMaster.h"


class Gimbal
{

  public:
    Gimbal(StepperMaster* stepperOne, StepperMaster* stepperTwo, int inter); //stepperOne = horizontal axis, stepeprTwo = vertical axis
    void rotateTo(double phi, double theta, int angleSpeed);
    void returnToHome();


  private:
    int anglTouSec(double anglSpeed);
    StepperMaster* _stepperOne;
    StepperMaster* _stepperTwo;
    bool _direction;
};

#endif
