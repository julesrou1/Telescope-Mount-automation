/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
*********/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32// OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
void display1(int n){
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  // Display static text
  if(n==1){display.println("Hello, wtf!");}
  if(n==2){display.println("Hello, Jules!");}
  display.display(); 
  }



void display2(double ra, double dec){
  display.clearDisplay();

  //titre 
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(40,10);
  display.println("ra:");
  

  //rectangle entourage
  display.drawRoundRect(0, 0, 128, 32, 3, WHITE);
  display.drawLine(0,7,128,7,WHITE);

  
  //affichage ra
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(40,10);
  display.println("ra:");
  display.setTextSize(1);
  display.setCursor(60,10);
  display.println(ra);

  //affichage dec
  display.setTextSize(1);
  display.setCursor(40,20);
  display.println("dec:");
  display.setTextSize(1);
  display.setCursor(65,20);
  display.println(dec);


  display.display();
}


void setup() {
  Serial.begin(115200);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
}

void loop() {
//  display1(1);
//  delay(1000);
//  display1(2);
  Serial.end();
   delay(1000);
   display.clearDisplay();
   display2(45.58976,-0.12453);
  
}
