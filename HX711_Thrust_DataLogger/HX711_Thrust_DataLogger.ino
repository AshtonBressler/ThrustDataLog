#include <EEPROM.h>
#include <HX711.h>

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 3;

HX711 scale;

void setup() {
  Serial.begin(57600);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  
  float calibrationFactor;
  EEPROM.get(0, calibrationFactor); // Retrieve the calibration factor from EEPROM
  Serial.println(calibrationFactor);
  scale.tare();
  scale.set_scale(calibrationFactor);  // Apply calibration factor
  
  Serial.println("Scale ready");
}

void loop() {
  float weight = scale.get_units(5);
  Serial.print("Weight: ");
  Serial.print(weight);
  Serial.println("lbs");
  delay(500);
}
