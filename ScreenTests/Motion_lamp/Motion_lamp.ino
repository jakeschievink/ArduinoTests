#include "ST7565.h"
#include <glcd.h>
#include <fonts/allFonts.h>

#define BACKLIGHT_LED 10

const int MOTIONACT = 0;
const int OFFACT = 1;
const int ONACT = 2;
boolean ready = true;
int curActivity = MOTIONACT;
ST7565 glcd(9,8,7,6,5);
char* motionMsg = "MotionActivated";

void setup(){
        Serial.begin(9600);

        Serial.print("start" );
        int swidth = 128;
        int sheight = 64;
        // turn on backlight
        pinMode(BACKLIGHT_LED, OUTPUT);
        analogWrite(BACKLIGHT_LED, 50);
        pinMode(0, INPUT);
        digitalWrite(0, HIGH);

        // initialize and set the contrast to 0x18
        glcd.begin(0x18);
        glcd.clear();
        glcd.display();
        delay(2000);
        glcd.clear();
        displaymessage(MOTIONACT);
        delay(3000);

}
void loop(){
        int buttonStat = digitalRead(0);
        if(ready && buttonStat == LOW){
                Serial.println(curActivity);
                curActivity++;
                if(curActivity > 2){
                        curActivity=0;
                }
                ready = false;
                displaymessage(curActivity);
                ready = true;

        Serial.println(curActivity);
                
        }
        
}
void displaymessage(int num){
        char* selectmsg = "yuoip";
        switch(num){
                case MOTIONACT: 
                        selectmsg = "Motion Activates";
                        break;
                case OFFACT : 
                        selectmsg = "OFF";
                        break;
                case ONACT : 
                        selectmsg = "ON";
                        break;
                default: 
                        
                        break;
                break;
        }
        glcd.clear();
        glcd.drawstring(10,4, selectmsg);
        glcd.display();
}
