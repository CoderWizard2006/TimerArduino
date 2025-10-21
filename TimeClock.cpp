#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

int digits[6] = {0,0,0,0,0,0}; 
int cursorPos = 0;             
bool settingMode = true;       
bool running = false;         
bool timerUP = false;          
bool paused = false;            
unsigned long previousMillis = 0;

void displayTime();
void moveCursorRight();
void moveCursorLeft();
void handleSettingMode(char key);
void countdown();

void setup() {
  lcd.init();
  lcd.backlight();
  pinMode(13, OUTPUT);

  lcd.setCursor(0,0);
  lcd.print("Press A ");
  lcd.setCursor(0,1);
  lcd.print("for cursorFwd");
  delay(2000);
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Press B ");
  lcd.setCursor(0,1);
  lcd.print("for cursorBack");
  delay(2000);
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Press C for Start"); 
  delay(2000);
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Press D to Reset");
  delay(2000);
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Time");
  lcd.setCursor(0,1);
  lcd.print("HH:MM:SS");
  lcd.setCursor(0,1);
  displayTime();
}


void loop() {
  char key = keypad.getKey();
  if (key) {
    if (settingMode) handleSettingMode(key);
    else {
      if (key == '*') paused = !paused;  
      else if (key == 'D') {             
        running = false;
        settingMode = true;
        for (int i=0; i<6; i++) digits[i]=0;
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Set Time:");
        lcd.setCursor(0,1);
        lcd.print("HH:MM:SS");
        displayTime();
        cursorPos = 0;
      }
    }
  }

  if (running && !paused) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= 1000) {
      previousMillis = currentMillis;
      countdown();
    }
  }

  if (timerUP) {
    digitalWrite(13,HIGH);  
    delay(5000);
    digitalWrite(13,LOW);    
    timerUP = false;
    running = false;
    settingMode = true;
    for (int i=0; i<6; i++) digits[i]=0;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Set Time:");
    lcd.setCursor(0,1);
    lcd.print("HH:MM:SS");
    displayTime();
    cursorPos = 0;
  }
}

void displayTime() {
  lcd.setCursor(0,1);
  lcd.print(digits[0]);
  lcd.print(digits[1]);
  lcd.print(":");
  lcd.print(digits[2]);
  lcd.print(digits[3]);
  lcd.print(":");
  lcd.print(digits[4]);
  lcd.print(digits[5]);
  lcd.print(" "); 
}

void moveCursorRight() {
  cursorPos++;
  if (cursorPos > 5) cursorPos = 5;
}

void moveCursorLeft() {
  if (cursorPos > 0) cursorPos--;
}

void handleSettingMode(char key) {
  if (key >= '0' && key <= '9') {
    digits[cursorPos] = key - '0';
    moveCursorRight();
    displayTime();
  }
  else if (key == 'A') { moveCursorRight(); displayTime(); }
  else if (key == 'B') { moveCursorLeft(); displayTime(); }
  else if (key == 'C') { settingMode = false; running = true; previousMillis = millis(); }
  else if (key == 'D') {
    for (int i=0; i<6; i++) digits[i]=0;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Set Time: HH:MM:SS");
    lcd.setCursor(0,1);
    displayTime();
    cursorPos = 0;
  }
}

void countdown() {
  int hours = digits[0]*10 + digits[1];
  int minutes = digits[2]*10 + digits[3];
  int seconds = digits[4]*10 + digits[5];

  if (hours == 0 && minutes == 0 && seconds == 0) {
    lcd.clear();
    lcd.setCursor(4,0);
    lcd.print("TIME UP!");
    timerUP = true;
    running = false;
    return;
  }

  if (seconds > 0) seconds--;
  else {
    seconds = 59;
    if (minutes > 0) minutes--;
    else {
      minutes = 59;
      if (hours > 0) hours--;
    }
  }

  digits[0] = hours / 10;
  digits[1] = hours % 10;
  digits[2] = minutes / 10;
  digits[3] = minutes % 10;
  digits[4] = seconds / 10;
  digits[5] = seconds % 10;

  displayTime();
}
