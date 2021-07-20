#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <BMP180.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
BMP180 pressure1(BMP180_STANDARD);
BMP180 pressure2(BMP180_STANDARD);

#define TCAADDR 0x70
void tcaselect(uint8_t i)
{
  if (i > 7)
    return;

  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << i);
  Wire.endTransmission();
}

long int bmp1;
long int bmp2;

void setup()
{
  Serial.begin(115200);
  Wire.begin();

  tcaselect(0);
  while (pressure1.begin() != true)
  {
    lcd.setCursor(0, 0);
    lcd.print(F("Sensor BMP180 Ke-1 error"));

    Serial.println(F("Sensor BMP180 Ke-1 error"));
    delay(5000);
  }

  tcaselect(1);
  while (pressure2.begin() != true)
  {
    lcd.setCursor(0, 0);
    lcd.print(F("Sensor BMP180 Ke-2 error"));

    Serial.println(F("Sensor BMP180 Ke-2 error"));
    delay(5000);
  }
  tcaselect(2);
  lcd.begin();
}

void loop()
{

  tcaselect(0);
  bmp1 = pressure1.getPressure();
  tcaselect(1);
  bmp2 = pressure2.getPressure();
  Serial.print("P1 = ");
  Serial.print(bmp1);
  Serial.println(" Pa");

  
  Serial.print("P2 = ");
  Serial.print(bmp2);
  Serial.println(" Pa");

  Serial.print("P1-P2 = ");
  Serial.print(bmp1 - bmp2);
  Serial.println(" Pa");
  Serial.println("");

  tcaselect(2);
  lcd.setCursor(0, 0);
  lcd.print("NEGATIVE PRESS  ");
  lcd.print(bmp1);
  lcd.print("Pa");

  lcd.setCursor(0, 1);
  lcd.print("P1-P2 = ");
  lcd.print(bmp1 - bmp2);
  lcd.print("Pa   ");

  delay(1000);
}
