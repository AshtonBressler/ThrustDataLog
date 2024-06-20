#include <Arduino.h>
#include "HX711.h"
#include <EEPROM.h>

HX711 scale;

const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 3;
float knownWeight;
long rawReadingKnown;

void setup() {

  Serial.flush();
  Serial.begin(57600);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

  Serial.println("Enter known object weight : ");
  delay(5000);
  knownWeight = Serial.parseFloat();
  Serial.println(knownWeight);


  Serial.println("Remove all weight from scale.");
  delay(2000);
  scale.tare(20);
  Serial.println(scale.get_value(5));

  Serial.println("Place known weight on scale now");
  delay(5000);
  rawReadingKnown = scale.get_value(5);
  float calibrationFactor = rawReadingKnown/knownWeight;
  scale.set_scale(calibrationFactor);
  EEPROM.put(0, calibrationFactor);
  Serial.print("Calibration factor stored: ");
  Serial.print(calibrationFactor);




}

void loop() {
 Serial.println(scale.get_units());
 delay(1000);
}
