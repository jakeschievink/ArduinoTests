const int readPin = A0;
const int minute = 60000;
int pinVal = 0;
int maxv = 0;
int minv = 1000;
long starttime = millis();
Thermistor temp(0);

void setup(){
                Serial.begin(9600);
}
void loop(){
        pinVal = analogRead(readPin);
        if(pinVal > maxv){
                maxv = pinVal;
        }
        if(pinVal < minv){
                minv = pinVal;
        }
        //Serial.println(millis()-starttime);
        if((millis() - starttime) > 3600000){
                Serial.print("min: ");
                Serial.println(minv);
                Serial.print("max: ");
                Serial.println(maxv);
                minv = 10000;
                maxv = 0;
                starttime = millis();
        }
        delay(1000);
}
