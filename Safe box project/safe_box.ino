#include <Key.h>
#include <Keypad.h>
#include<LiquidCrystal_I2C.h>
#include <Servo.h>
Servo servomotor;

LiquidCrystal_I2C lcd(0x27,16,2);
const byte ROWS = 4; // number of rows
const byte COLS = 4; // number of columns
char keys[ROWS][COLS] = {
{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'}
};
char password[6]={'#','6','4','2','1','D'};
int i=0;
int d=0;
int deschis=1;
byte rowPins[ROWS] = {2, 3, 4, 5}; // row pinouts of the keypad R1 = D8, R2 = D7, R3 = D6, R4 = D5
byte colPins[COLS] = {6, 7, 8,9};    // column pinouts of the keypad C1 = D4, C2 = D3, C3 = D2
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
 
void setup()
{
  lcd.begin();
//  lcd.backlight();
  Serial.begin(9600);
  pinMode(10,OUTPUT);
  servomotor.attach(11);
 servomotor.write(100);
  
    }
 
void loop()
{
  
  
  char passcheck[5];
  char key = keypad.getKey(); 
  if (key != NO_KEY){
      if(i==0){
        lcd.clear();
        lcd.print("     ");
        }
        
      lcd.print(key);
      tone(10,880);
      delay(50);
      noTone(10);
    if(key==password[i]){
      d++;
      }
      i++;
    Serial.println(key);
    }
    if(i==6){
      if(d==6){
        lcd.clear();
        Serial.println("Parola corecta!");
        
        delay(50);
        tone(10,880);
        delay(50);
        noTone(10);
        i=0;
        d=0;
        if(deschis==0){
          servomotor.write(100);
          deschis=1;
          Serial.println("deschis");
          lcd.print("      OPEN");
          }
        else if(deschis==1){
          servomotor.write(10);
          deschis=0;
          Serial.println("inchis");
          lcd.print("     CLOSED");
          }
        
        }
        else{
          lcd.clear();
          Serial.println("Parola incorecta!");
          lcd.print("    TRY AGAIN");
          delay(50);
          tone(10,880);
          delay(150);
          noTone(10);
          tone(10,880);
          delay(150);
          noTone(10);
          i=0;
          d=0;
          }
          
      }
  
    
}
