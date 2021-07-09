#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int x = 0;
int y = 0;
int val;
const int button = A2;

int dist;

int isGameOver = 0;

int cactuses[5][2] = {};

int dinoPos[1][2] = {3, 1};

int orig_frameCount = 600;
int orig_jumpCount = 4;

int isJumping = 0;
int jumpCount = orig_jumpCount;

int frameCount = orig_frameCount;

int score = 0;

void setup()
{
  randomSeed(analogRead(A0));
  Serial.begin(9600);
  for (int i = 0; i < 5; i++) {
    dist = random(15, 25);
    //Serial.print(dist);
    cactuses[i][0] = cactuses[i - 1][0] + random(10, 20);
    cactuses[i][1] = 1;
  }
  pinMode(button, INPUT_PULLUP);
  lcd.begin(16, 2);
}

void loop()
{
  val = analogRead(button);

  if (isGameOver == 1) {

    if (val <= 100) {
      //if button is pressed
      isGameOver = 0;
      score = 0;
      isJumping = 0;
      frameCount = orig_frameCount;
    }
    lcd.setCursor(0, 0);
    lcd.print("Game over!");
    lcd.setCursor(0, 1);
    lcd.print("Score: ");
    lcd.setCursor(6, 1);
    lcd.print(score);
  } else {
    
    if (val <= 100) {
      //if button is pressed
      isJumping = 1;
    }
    if (frameCount == 0) {
      frameCount = orig_frameCount;
      lcd.clear();

      if (isJumping == 1) {
        jumpCount--;
        if (jumpCount == 0) {
          dinoPos[0][1] = 1;
          isJumping = 0;
          jumpCount = orig_jumpCount;
        } else {
          dinoPos[0][1] = 0;
        }
      }

      lcd.setCursor(dinoPos[0][0], dinoPos[0][1]);
      lcd.print("D");

      lcd.setCursor(13, 0);
      lcd.print(score);

      for (int i = 0; i < 5; i++) {
        if (cactuses[i][0] < 16 && cactuses[i][0] > -1) {
          lcd.setCursor(cactuses[i][0], cactuses[i][1]);
          lcd.print("#");
        }
        cactuses[i][0]--;
        if (cactuses[i][0] == dinoPos[0][0] && cactuses[i][1] == dinoPos[0][1]) {
          isGameOver = 1;
          lcd.clear();
        } else if (cactuses[i][0] == 0) {
          score++;
          dist = random(15, 25);
          //Serial.print(dist);
          if (i == 0) {
            cactuses[i][0] = cactuses[4][0] + random(10, 20);
          } else {
            cactuses[i][0] = cactuses[i - 1][0] + random(10, 20);
          }
        }
      }
    }
    frameCount--;
  }
}