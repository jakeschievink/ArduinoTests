#define BLINKLED 3
#define WORKINGLED 2
#define BUTTON 11
#define DEBUG 0
#define MINUTE 1000

const int defaulttime = 25;
int buttonStat = 0;
long time;
long fourth;
long endtime;
boolean butready = true;
boolean starttimer = false; 
boolean pressed = false;
void setup(){
        Serial.begin(9600);
        pinMode(BUTTON, INPUT);
        pinMode(BLINKLED, OUTPUT);
        pinMode(WORKINGLED, OUTPUT);
        Serial.print("start" );
        attachInterrupt(BUTTON, stateChange, HIGH);
}
void loop(){
        time = millis();

        if(!starttimer){
                if(pressed){
                        endtime = time+((long)(defaulttime*MINUTE) );
                        starttimer = true;
                        fourth = time+((long)(defaulttime*MINUTE)/4);
                        digitalWrite(BLINKLED, LOW);
                        digitalWrite(WORKINGLED, HIGH);
                        pressed = false;

                        #ifdef DEBUG
                                Serial.print("endtime:");
                                Serial.println(endtime);
                        #endif
                }else{
                        pulsate();
                }
        }


        if(starttimer){
                if(time <= endtime){
                        #ifdef DEBUG
                                Serial.print("timeleft");
                                Serial.println(endtime-time);
                        #endif
                        if(fourth-time < 0){
                                Serial.print("ONEFORRRRRRTH");
                                blink();
                                fourth = time+((long)(defaulttime*MINUTE)/4);
                                
                        
                        }

                }
                else{
                        digitalWrite(WORKINGLED, LOW);
                        starttimer = false; 
                }
        }

                        
                
                
        
}
void blink(int amount;){
        for(int i=1; i<amount; i++){
                digitalWrite(BLINKLED, HIGH);
                delay(1000);
                digitalWrite(BLINKLED, LOW);
                delay(500);
        }
 }

void pulsate(){
        int anval = 0; 
                for(anval = 0; anval <=255; anval++){
                        if(!pressed){

                                analogWrite(BLINKLED, anval);
                                delay(10);
                        }else{
                                analogWrite(BLINKLED, 0);
                                break;
                        }
                
                }
                for(anval = 255; anval >=0; anval--){
                        if(!pressed){
                                analogWrite(BLINKLED, anval);
                                delay(10);
                        }else{

                                analogWrite(BLINKLED, 0);
                                break;
                        }
                }
}
void stateChange(){
        pressed = true;
        Serial.println(pressed);
}
