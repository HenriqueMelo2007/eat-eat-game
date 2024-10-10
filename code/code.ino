#include <LiquidCrystal.h>

#define upButton 6
#define downButton 7
#define leftButton 9
#define rightButton 8

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

byte eatEatRightOpenedMouth[8] = {
  B01110,
  B11001,
  B11111,
  B11100,
  B11100,
  B11111,
  B01110,
  B00000
};

byte eatEatRightClosedMouth[8] = {
  B01110,
  B11001,
  B11111,
  B11111,
  B11111,
  B11110,
  B01100,
  B00000
};

byte eatEatLeftOpenedMouth[9] = {
  B01110,
  B10011,
  B11111,
  B00111,
  B00111,
  B11111,
  B01110,
  B00000
};

byte eatEatLeftClosedMouth[8] = {
  B01110,
  B10011,
  B11111,
  B11111,
  B11111,
  B01111,
  B00110,
  B00000
};

byte fruit[8] = {
  B00011,
  B00110,
  B00100,
  B01110,
  B11111,
  B11111,
  B11111,
  B01110
};

byte ghost[8] = {
  B01110,
  B11111,
  B10101,
  B10101,
  B11111,
  B11111,
  B11011,
  B01010
};

bool start;
 

void setup()
{
  pinMode(upButton, INPUT);
  pinMode(downButton, INPUT);
  pinMode(leftButton, INPUT);
  pinMode(rightButton, INPUT);

  start = false;

  lcd.begin(16, 2);
  lcd.createChar(1, eatEatRightOpenedMouth);
  lcd.createChar(2, eatEatRightClosedMouth);
  lcd.createChar(3, eatEatLeftOpenedMouth);
  lcd.createChar(4, eatEatLeftClosedMouth);
  lcd.createChar(5, fruit);
  lcd.createChar(6, ghost);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.write(1);
  lcd.write(5);
  lcd.print("Eat-Eat Game");
  lcd.write(6);
  lcd.write(3);
  lcd.setCursor(0, 1);
  lcd.print("Press any button");
}
 
void loop()
{
  
}