/*
 *  Function to extract battery percentage out of the ADC pin.
 */

#ifndef _BATTERY_H
#define _BATTERY_H

void batterySend() {
  int batmeasure[20];
  float total;
  for(int m = 0; m < 20; m++) {
    batmeasure[m] = analogRead(batPin);
    total = total + batmeasure[m];
  }
  float avg         = total/20;
  float bV          = 0.0021*avg - 0.4452;
  float battPercent = sqrt((bV/a) + (sq(b)/2*a) - (c/a)) - b/(2*a);

  // Round to integer (rounded down to 5%)
  int batt5         = battPercent/5;
  int battFin       = batt5*5;

  battFin = min( 100, max( 0, battFin));

  bleKeyboard.setBatteryLevel(battFin);

  if (debug) Serial.println("Battery percentage calculated and sent");
}

#endif // _BATTERY_H