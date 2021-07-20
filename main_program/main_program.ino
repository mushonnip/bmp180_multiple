#include "TCA9548A.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SFE_BMP180.h>

TCA9548A<TwoWire> TCA;
LiquidCrystal_I2C lcd(0x27, 16, 2);
SFE_BMP180 pressure1;
SFE_BMP180 pressure2;

#define WIRE Wire

void setup()
{
  TCA.begin(WIRE);
  TCA.openChannel(TCA_CHANNEL_0);
  pressure1.begin();
  TCA.closeChannel(TCA_CHANNEL_0);
  TCA.openChannel(TCA_CHANNEL_1);
  pressure2.begin();
  TCA.closeChannel(TCA_CHANNEL_1);
}

void loop()
{
  lcd.setCursor(0,0);
  lcd.setCursor(0, 1);
}
