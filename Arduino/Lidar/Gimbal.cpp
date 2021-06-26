/*                Gimbal.cpp
 * Autor:         ruti1014
 * Beschreibung:  Regelung der benötigten Stepper Motoren
 * 
*/

#include "Arduino.h"
#include "Gimbal.h"
#include "StepperMaster.h"




Gimbal::Gimbal(StepperMaster* stepperOne, StepperMaster* stepperTwo, int inter) { //Motor One pin 1-4, motor Two pin 1-4
  _stepperOne = stepperOne;
  _stepperTwo = stepperTwo;
}

void Gimbal::rotateTo(double phi, double theta, int angleSpeed) { //horizontal axis in deg, vertical axis in deg, anglespeed in deg/sec | phi -> stepperOne, theta -> stepperTwo
  double Dphi = phi - _stepperOne->getAbsoluteAngle();
  double Dtheta = theta - _stepperTwo->getAbsoluteAngle();
  long double c;


  int phi_interval;
  int theta_interval;
  double phi_dot;
  double theta_dot;

  long int phi_stamp = micros();
  long int theta_stamp = micros();

  while (abs(Dphi) > 0.1 || abs(Dtheta) > 0.1) {
    if (Dphi != 0) {
      c = abs(Dtheta) / abs(Dphi);
      phi_dot = (angleSpeed) / (sqrt(pow(cos(_stepperOne->getAbsoluteAngle() * (PI / 180.0)), 2) * pow(c, 2) + 1));

      if (anglTouSec(phi_dot) < _stepperOne->getMinInterval()) phi_interval = _stepperOne->getMinInterval();
      else phi_interval = anglTouSec(phi_dot);

      if ((micros() - phi_stamp >= phi_interval) && (abs(Dphi) > 0.1 )) {
        if (Dphi > 0) {
          _stepperOne->rotate(CLOCKWISE);
        } else {
          _stepperOne->rotate(COUNTERCLOCKWISE);
        }
        Dphi = phi - _stepperOne->getAbsoluteAngle();
        phi_stamp = micros();
      }
    }

    
    if (Dtheta != 0) {
     
      if (Dphi != 0) {
        c = abs(Dtheta) / abs(Dphi);
        theta_dot = (c * angleSpeed) / (sqrt(pow(cos(_stepperOne->getAbsoluteAngle() * (PI / 180.0)), 2) * pow(c, 2) + 1));
        theta_interval = anglTouSec(theta_dot);
      } else {
        if (_stepperOne->getAbsoluteAngle() == 90) {
          theta_interval = _stepperTwo->getMinInterval();
        } else {
          theta_dot = (angleSpeed) / (sqrt(pow(cos(_stepperOne->getAbsoluteAngle() * (PI / 180.0)), 2))); //90° abfangen
          theta_interval = anglTouSec(theta_dot);
        }
      }
      if ((micros() - theta_stamp >= theta_interval) && (abs(Dtheta) > 0.1 )) {
        if (Dtheta > 0) {
          _stepperTwo->rotate(CLOCKWISE);
        } else {
          _stepperTwo->rotate(COUNTERCLOCKWISE);
        }
        Dtheta = theta - _stepperTwo->getAbsoluteAngle();
        theta_stamp = micros();
      }

    }

  }
}

void Gimbal::returnToHome() {

  
  rotateTo(340, 180, 50);
  vTaskDelay(150);
 
  _stepperOne->setAbsoluteAngle(215); //210
  _stepperTwo->setAbsoluteAngle(105); // 105
  rotateTo(0, 0, 70);
}

int Gimbal::anglTouSec(double anglSpeed) {// deg/sek
  double x = PI / 2048;
  return ((x * 360) / (2 * PI * anglSpeed)) * pow(10, 6);
}
