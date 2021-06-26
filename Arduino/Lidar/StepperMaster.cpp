/*                StepperMaster.cpp
 * Autor:         ruti1014
 * Beschreibung:  Ansteuerung des Stepper Motors
 * Hardware:      Stepper Motor vom Typ 28byj-48
*/


#include "Arduino.h"
#include "StepperMaster.h"

StepperMaster::StepperMaster(int PIN_IN1, int PIN_IN2, int PIN_IN3, int PIN_IN4) {
  pinMode(PIN_IN4, OUTPUT);
  pinMode(PIN_IN3, OUTPUT);
  pinMode(PIN_IN2, OUTPUT);
  pinMode(PIN_IN1, OUTPUT);
  _pin_in1 = PIN_IN1;
  _pin_in2 = PIN_IN2;
  _pin_in3 = PIN_IN3;
  _pin_in4 = PIN_IN4;

  setMinInterval(900);
  setAbsoluteAngle(0.0);
  _stepPosition = 1;
  
}

void StepperMaster::sequence(bool in1, bool in2, bool in3, bool in4) {
  digitalWrite(_pin_in4, in4);
  digitalWrite(_pin_in3, in3);
  digitalWrite(_pin_in2, in2);
  digitalWrite(_pin_in1, in1);
}

void StepperMaster::rotate(bool clockwise) {

  switch (_stepPosition) {

    case 1:
      sequence(LOW, LOW, LOW, HIGH);
      break;
    case 2:
      sequence(LOW, LOW, HIGH, HIGH);
      break;
    case 3:
      sequence(LOW, LOW, HIGH, LOW);
      break;
    case 4:
      sequence(LOW, HIGH, HIGH, LOW);
      break;
    case 5:
      sequence(LOW, HIGH, LOW, LOW);
      break;
    case 6:
      sequence(HIGH, HIGH, LOW, LOW);
      break;
    case 7:
      sequence(HIGH, LOW, LOW, LOW);
      break;
    case 8:
      sequence(HIGH, LOW, LOW, HIGH);
      break;
  }

  if (clockwise) {
    _absoluteAngle += 360.0 / 4096.0;
    if (_stepPosition < 8)_stepPosition++;
    else _stepPosition = 1;
  } else {
    _absoluteAngle -= 360.0 / 4096.0;
    if (_stepPosition > 1) _stepPosition--;
    else _stepPosition = 8;
  }
}

void StepperMaster::setAbsoluteAngle(double pos) {
  _absoluteAngle = pos;
}

double StepperMaster::getAbsoluteAngle() {
  return _absoluteAngle;
}

int StepperMaster::getStepPosition() {
  return _stepPosition;
}

void StepperMaster::setMinInterval(int minInterval) {
  _minInterval = minInterval;
}

int StepperMaster::getMinInterval() {
  return _minInterval;
}
