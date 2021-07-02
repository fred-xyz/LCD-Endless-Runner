#include <Wire.h> 
#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>

#define DUDE 0
#define ROOF 1
#define BOTTOM 3
#define STALAMIT 4
#define STALACTITE 5
//stalactite
//stalagmit
int inPin = 10;    // pushbutton connected to digital pin 10
int val = 0;      // variable to store the read value


bool mit[20];
bool mit_template[20] = {false, false, false, false, true, false, false, false, false, false, false , false, false , false, true , false, true , false, false, false};
bool tite[20]; 
bool tite_template[20] = {false, false, false, false, false, false, false,false, true, true , false, true , false, false , false, false , false, false, false, false };

byte dude[8] = { //the 8 is becus you can only make opto 8 tcustom careters
  B01110,
  B10001,
  B01110,
  B00100,
  B11111,
  B10101,
  B01010,
  B10001,    
};

byte roof[8] = {
  B11111,
  B01110,
  B10001,
  B10101,
  B11011,
  B10101,
  B01110,
  B00100,    
};

byte bottom[4] = {
  B10000,
  B11111,
  B10101,
  B11111,    
};

byte stalagmit[6] = {
  B00100,
  B00100,
  B01100,
  B01101,
  B10101,
  B01010,    
};

byte stalactite[6] = {
  B11111,
  B10101,
  B10011,
  B11100,
  B10110,
  B00100,    
};

LiquidCrystal_I2C lcd(0x27, 20, 4); //the Paramatros is set to the dedital pins

unsigned long myTime;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(inPin, INPUT);    // sets the digital pin 10 as input
  
  lcd.begin(); //inesialic and set the demansen of the LCD
  lcd.createChar(DUDE, dude);
  lcd.createChar(ROOF, roof);
  lcd.createChar(BOTTOM, bottom);
  lcd.createChar(STALAMIT, stalagmit);
  lcd.createChar(STALACTITE, stalactite);
  
  resetGame();

}

void loop() {
      
      val = digitalRead(inPin);   // read the input pin
      if(val == HIGH){
        lcd.setCursor(1,1);
        lcd.write(byte(DUDE));
        delay(500);
        clear_rows();
        Serial.println("true");
      }
      else{
        lcd.setCursor(1,2);
        lcd.write(byte(DUDE));
        delay(500);  
        clear_rows();
        Serial.println("false");
      }
      
    for(int i=0; i<20; i++){
      if(mit[i]){
        lcd.setCursor(i,2);
        lcd.write(byte(STALAMIT)); 
      }
      if(i>0){
        mit[i-1]=mit[i];
      }
  
      if(tite[i]){
        lcd.setCursor(i,1);
        lcd.write(byte(STALACTITE)); 
      }
      if(i>0){
        tite[i-1]=tite[i];
      }
    }
  
    
    if(random(1, 10)==1){
      mit[19]=true;
      tite[19]=false;
    }else{
      mit[19]=false;
    }
  
    if(random(1, 10)==1){
      tite[19]=true;
      mit[19]=false;
    }else{
      tite[19]=false;
    }
    
    if(mit[0] && val == LOW){
      gameOver();
    }
    
    if (tite[0] && val == HIGH){
      gameOver();
    }
}


void clear_rows (){
  for(int i=0; i<20; i++){
    lcd.setCursor(i,2);
    lcd.print(" ");
    lcd.setCursor(i,1);
    lcd.print(" ");
  }
}

void gameOver(){
  unsigned long endTime = millis();
  String go = "Game Gver";
  String youTime = "you time: ";
  unsigned long duration = (endTime - myTime) / 1000;
  lcd.clear();
  lcd.print(go);
  lcd.setCursor(0,2);
  lcd.print(youTime);
  lcd.print(duration);
  while(digitalRead(inPin)==0){
  }
  resetGame();
}
void resetGame(){
    myTime = millis();

    for(int j=0; j<20; j++){
      lcd.setCursor(j,0);
      lcd.write(byte(ROOF));
      lcd.setCursor(j,3);
      lcd.write(byte(BOTTOM));

      mit[j] = mit_template[j];
      tite[j] = tite_template[j]; 
    }
  }
