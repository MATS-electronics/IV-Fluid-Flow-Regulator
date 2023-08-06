#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <ClickEncoder.h>
#include <TimerOne.h>
//#include "pump2.h"

int start_b = 12; // start/Pause button
int stop_b = 13 ; // stop button

int menuitem = 1;
int frame = 1;
int page = 1;
int lastMenuItem = 1;


String menuItem1 = "Volume rate";
String menuItem2 = "Time duration";
String menuItem3 = "Calibration";
String menuItem4 = "Reset";

String Calibration[2] = { "Low speed", "High speed" };
int selectedCalibration = 0;

String Volume_rate[8] = {"25 ml/h","50 ml/h","75 ml/h","100 ml/h","125 ml/h",
"150 ml/h","175 ml/h","200 ml/h"};
int selectedVolumeRate = 0;

String Time_duration[4] = {"30 min","60 min","90 min","120 min"};
int selectedTimeDuration = 0;

boolean up = false;
boolean down = false;
boolean middle = false;

ClickEncoder *encoder;
int16_t last, value;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  encoder = new ClickEncoder(A2, A1, A3);
  encoder->setAccelerationEnabled(false);
  lcd.init();
  lcd.backlight();  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("MATS.");
  delay(1000);
  lcd.clear();
  lcd.print("MATS..");
  delay(1000);
  lcd.clear();
  lcd.print("MATS...");
  delay(1000);
  lcd.setCursor(0,1);
  lcd.print("   Main Menu   ");
  delay(3000);

  Timer1.initialize(1000);
  Timer1.attachInterrupt(timerIsr); 
  
  last = encoder->getValue();

  pinMode(start_b,INPUT);
  pinMode(stop_b,INPUT);

}

void loop() {
  drawMenu();
  //level_sensor();
  readRotaryEncoder();

  ClickEncoder::Button b = encoder->getButton();
  if (b != ClickEncoder::Open) {
   switch (b) {
      case ClickEncoder::Clicked:
         middle=true;
        break;
    }
  }

  if (up && page == 1 ) {
     
    up = false;
    if(menuitem==2 && frame ==2)
    {
      frame--;
    }
    if(menuitem==3 && frame ==3)
    {
      frame--;
    }
    lastMenuItem = menuitem;
    menuitem--;
    if (menuitem==0)
    {
      menuitem=1;
    }
  }else if (up && page == 2 && menuitem==1 ) {
    up = false;
    selectedVolumeRate++;
    if(selectedVolumeRate == 8)
    {
      selectedVolumeRate = 0;
    }
  }
  else if (up && page == 2 && menuitem==2 ) {
    up = false;
    selectedTimeDuration++;
    if(selectedTimeDuration == 4)
    {
      selectedTimeDuration = 0;
    }
    
  }
  else if (up && page == 2 && menuitem==3 ) {
    up = false;
    selectedCalibration++;
    if(selectedCalibration == -1)
    {
      selectedCalibration = 1;
    }
    
  }
  if (down && page == 1) //We have turned the Rotary Encoder Clockwise
  {

    down = false;
    if(menuitem==2 && lastMenuItem == 1)
    {
      frame ++;
    }else  if(menuitem==3 && lastMenuItem == 2)
    {
      frame ++;
    }
    lastMenuItem = menuitem;
    menuitem++;  
    if (menuitem==5) 
    {
      menuitem--;
    }
  }
  else if (down && page == 2 && menuitem==1 ) {
    down = false;
    selectedVolumeRate++;
    if(selectedVolumeRate == 8)
    {
      selectedVolumeRate = 0;
    }
  }
  else if (down && page == 2 && menuitem==2 ) {
    down = false;
    selectedTimeDuration++;
    if(selectedTimeDuration == 4)
    {
      selectedTimeDuration = 0;
    }
  }
  else if (down && page == 2 && menuitem==3 ) {
    down = false;
    selectedCalibration++;
    if(selectedCalibration == -1)
    {
      selectedCalibration = 1;
    }
  }
  if (middle) //Middle Button is Pressed
  {
    middle = false;

    if(page == 1 && menuitem ==6)// Reset
    {
      resetDefaults();
    }

    else if (page == 1 && menuitem<=3)
     {
      page=2;
     }
    else if (page == 2) 
     {
      page=1; 
     }
   }
  if (digitalRead(start_b) == 0){
     //motor_run(n, rate);
   }
}


void resetDefaults()
  {
    selectedCalibration = 0;
    selectedVolumeRate = 0;
    selectedTimeDuration = 0;
    
  }

void timerIsr() {
  encoder->service();
}

void drawMenu()
  {
    
  if (page==1) 
  {    

    if(menuitem==1 && frame ==1)
    { 
      lcd.setCursor(0,0);
    lcd.print("                ");
    lcd.setCursor(0,1);
    lcd.print("                ");
      displayMenuItem(menuItem1, 0,true);
      displayMenuItem(menuItem2, 1,false);
    }
    else if(menuitem == 2 && frame == 1)
    {
      lcd.setCursor(0,0);
    lcd.print("                ");
    lcd.setCursor(0,1);
    lcd.print("                ");
      displayMenuItem(menuItem1, 0,false);
      displayMenuItem(menuItem2, 1,true);
    }
     else if(menuitem == 2 && frame == 2)
    {
      lcd.setCursor(0,0);
    lcd.print("                ");
    lcd.setCursor(0,1);
    lcd.print("                ");
      displayMenuItem(menuItem2, 0,true);
      displayMenuItem(menuItem3, 1,false);
    }

      else if(menuitem == 3 && frame == 2)
    {
      lcd.setCursor(0,0);
    lcd.print("                ");
    lcd.setCursor(0,1);
    lcd.print("                ");
      displayMenuItem(menuItem2, 0,false);
      displayMenuItem(menuItem3, 1,true);
    }
    
    else if(menuitem == 3 && frame == 3)
    {
      lcd.setCursor(0,0);
    lcd.print("                ");
    lcd.setCursor(0,1);
    lcd.print("                ");
      displayMenuItem(menuItem3, 0,true);
      displayMenuItem(menuItem4, 1,false);
    }

    else if(menuitem == 4 && frame == 3)
    {
      lcd.setCursor(0,0);
    lcd.print("                ");
    lcd.setCursor(0,1);
    lcd.print("                ");
      displayMenuItem(menuItem3, 0,false);
      displayMenuItem(menuItem4, 1,true);
    }
    
     
    //display.display();
  }
  else if (page==2 && menuitem == 1) 
  {    
   displayStringMenuPage(menuItem1, Volume_rate[selectedVolumeRate]);
  }

  else if (page==2 && menuitem == 2) 
  {
   displayStringMenuPage(menuItem2, Time_duration[selectedTimeDuration]);
  }
   else if (page==2 && menuitem == 3) 
  {
   displayStringMenuPage(menuItem3, Calibration[selectedCalibration]);
  }
  }

void displayIntMenuPage(String menuItem, int value)
{
    lcd.setCursor(0,0);
    lcd.print("                ");
    lcd.setCursor(0,1);
    lcd.print("                ");
    lcd.setCursor(0, 0);
    lcd.print(menuItem);
    lcd.setCursor(0, 1);
    lcd.print("Value");
    lcd.setCursor(0, 8);
    lcd.print(value);
    //display.display();
}

void displayStringMenuPage(String menuItem,String value)
{
    lcd.setCursor(0,0);
    lcd.print("               ");
    lcd.setCursor(0,1);
    lcd.print("               ");
    lcd.setCursor(0, 0);
    lcd.print(menuItem);
    lcd.setCursor(0, 1);
    lcd.print("Value");
    lcd.setCursor(0, 8);
    lcd.print(value);
    //display.display();
}

void displayMenuItem(String item, int position, boolean selected)
{
    if(selected)
    {
      //display.setTextColor(WHITE, BLACK);
      lcd.setCursor(0, position);
      lcd.print("X"+item);
    }else
    {
      //display.setTextColor(BLACK, WHITE);
      lcd.setCursor(0, position);
      lcd.print(">"+item);
    }
    
}

void readRotaryEncoder()
{
  value += encoder->getValue();
  
  if (value/2 > last) {
    last = value/2;
    down = true;
    delay(150);
  }else   if (value/2 < last) {
    last = value/2;
    up = true;
    delay(150);
  }
}

void stepper_speed()
{
}

// void level_sensor(){
//   int x = analogRead(A0);
//   Serial.println(x);
//   if(x<=100){
//     digitalWrite(7,HIGH);
//     delay(100);
//     digitalWrite(7,LOW);
// }
