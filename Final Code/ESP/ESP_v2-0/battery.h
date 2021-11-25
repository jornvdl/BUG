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
  if (battPercent > 100) battPercent = 100;
  int battRound     = round(battPercent);
  int batt5         = battRound/5;
  int battFin       = batt5*5;

  bleKeyboard.setBatteryLevel(battFin);

  if (debug) Serial.println("Battery percentage calculated and sent");
}

#endif // _BATTERY_H