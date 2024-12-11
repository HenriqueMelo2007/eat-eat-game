#include <LiquidCrystal.h>
#include "sprites.h"
#include <stdint.h>

#define upButton 6
#define downButton 7
#define leftButton 9
#define rightButton 8

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

bool start;

int lastValues[4] = {0, 0, 0, 0};

int eatEatPosition[2] = {7, 0};
int eatEatSprite = 1;

int fruitPosition[2] = {0, 0};
int ghostPosition[2] = {15, 1};

int score = 0;

void buttonPressed(int BTN);
void drawChar(int col, int row, int character);
void eatEat(int BTN);
void verifyCollision();
void showScore();
void respawn(int* positions);
int randomBinary();
int randomZeroOrFifteen();

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

  int seed = analogRead(0) + millis();
  randomSeed(seed);                    
}

void loop()
{
  buttonPressed(upButton);
  buttonPressed(downButton);
  buttonPressed(leftButton);
  buttonPressed(rightButton);

  if (start)
  {
    drawChar(eatEatPosition[0], eatEatPosition[1], eatEatSprite);
    drawChar(fruitPosition[0], fruitPosition[1], 5);
    drawChar(ghostPosition[0], ghostPosition[1], 6);
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
    lcd.clear();
    start = true;
    eatEat(BTN);
  }

  lastValues[BTN - 6] = input;
}

void drawChar(int col, int row, int character)
{
  lcd.setCursor(col, row);
  lcd.write(character);
}

void eatEat(int BTN)
{
  int specificBTN = BTN - 6;

  lcd.setCursor(eatEatPosition[0], eatEatPosition[1]);
  lcd.print(' ');

  switch (specificBTN)
  {
  case 0:
    eatEatPosition[1] = specificBTN;
    break;

  case 1:
    eatEatPosition[1] = specificBTN;
    break;

  case 2:
    if (eatEatPosition[0] < 15)
    {
      eatEatPosition[0] = eatEatPosition[0] + 1;
      switch (eatEatSprite)
      {
      case 1:
        eatEatSprite = 2;
        break;
      case 2:
        eatEatSprite = 1;
        break;
      default:
        eatEatSprite = 1;
        break;
      }
    }

    break;

  case 3:
    if (eatEatPosition[0] > 0)
    {
      eatEatPosition[0] = eatEatPosition[0] - 1;
      switch (eatEatSprite)
      {
      case 3:
        eatEatSprite = 4;
        break;
      case 4:
        eatEatSprite = 3;
        break;
      default:
        eatEatSprite = 3;
        break;
      }
    }
    break;

  default:
    break;
  }

  verifyCollision();
}

void verifyCollision()
{
  if (eatEatPosition[0] == fruitPosition[0] && eatEatPosition[1] == fruitPosition[1])
  {
    respawn(fruitPosition);
    score++;
  }
  if (eatEatPosition[0] == ghostPosition[0] && eatEatPosition[1] == ghostPosition[1])
  {
    showScore();
    start = false;
  }
}

void showScore()
{
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("GAME OVER");
  lcd.write(6);
  lcd.setCursor(3, 1);
  lcd.print("SCORE: ");
  lcd.print(score);
  delay(4000);
}

void respawn(int* positions)
{
  positions[0] = randomZeroOrFifteen();
  positions[1] = randomBinary();
}

int randomBinary()
{
  return random(0, 2);
}

int randomZeroOrFifteen()
{
  return random(0, 2) * 15;
}