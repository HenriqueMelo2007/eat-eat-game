#include <LiquidCrystal.h>
#include <sprites.h>
#include <stdint.h>

#define upButton 6
#define downButton 7
#define leftButton 9
#define rightButton 8

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

bool start;
int lastValues[4] = {0, 0, 0, 0};

void buttonPressed(int BTN);

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
}

void loop()
{
  buttonPressed(upButton);
  buttonPressed(downButton);
  buttonPressed(leftButton);
  buttonPressed(rightButton);

  if (start)
  {
    lcd.clear();
  }
  else
  {
    lcd.setCursor(0, 0);
    lcd.write(1);
    lcd.write(5);
    lcd.print("Eat-Eat Game");
    lcd.write(6);
    lcd.write(3);
    lcd.setCursor(0, 1);
    lcd.print("Press any button");
  }
}

void buttonPressed(int BTN)
{
  int input = digitalRead(BTN);

  if (input == 1 && lastValues[BTN - 6] == 0)
  {
    start = true;
  }

  lastValues[BTN - 6] = input;
}