#include <Thermistor.h>
#define DEBUG
#define READINGINTERVAL 10
#define NUMBEROFREADINGS 20
//pinSetups
const int ledBluePin = 10;
const int ledYellowPin = 11;
const int ledRedPin = 9;
const int ledWhitePin = 6;
const int sensorPin  = A1;
const int micPin  = A4;

long time,readingtime;

typedef struct Readvals{
        int reading;
        int readings[NUMBEROFREADINGS];
        int readingPos;
        int value;
        int displayed;
        int max;
        int min;
};
struct Readvals mic;
struct Readvals photo;
struct Readvals therm;
Thermistor temp(5);
void setup(){
        pinMode(ledBluePin, OUTPUT);
        pinMode(ledYellowPin, OUTPUT);
        pinMode(ledRedPin, OUTPUT);
        Serial.begin(9600);
        readingtime = 1000;
}
void loop(){
        time = millis();
         
        if(time > readingtime){
                takeReadings();
                readingtime = time+READINGINTERVAL;
                #if defined DEBUG
                        Serial.print("photo: ");
                        Serial.println(photo.reading);
                        Serial.print("mic: ");
                        Serial.println(mic.reading);
                        Serial.print("Temp:");
                        Serial.println(therm.reading);
                #endif
        }
        
        
        
        updateDisplayedValues();
        //writing to Leds
        writetoLeds();

        

        delay(90);
}

void takeReadings(){
                photo.reading = analogRead(sensorPin);
                photo.readingPos = insert(photo.readings, photo.reading, photo.readingPos);
                photo.value = map(average(photo.readings),0,1024, 0, 255);

                mic.reading = abs(analogRead(micPin)-840);
                mic.readingPos = insert(mic.readings, mic.reading, mic.readingPos);
                mic.value = average(mic.readings);
                //mic.value = map(average(mic.readings),50,255,0,255);

                therm.reading = int(temp.getTemp());
                therm.value = map(therm.reading, 155, 200, 0, 255);
}
void updateDisplayedValues(){
        photo.displayed = photo.displayed*.9+.1*photo.value;
        mic.displayed = mic.displayed*.9+.1*mic.value;
}
void writetoLeds(){
        analogWrite(ledWhitePin, photo.displayed);
        analogWrite(ledBluePin,255-photo.displayed);
        analogWrite(ledYellowPin, mic.displayed);
        analogWrite(ledRedPin, therm.value);
}
int insert(int arr[], int item, int pos){
        if(pos == 11){
                return 0;
        }else{
                arr[pos]=abs(item);
                pos++;
                return pos;
        }
}
int average(int arr[]){
        int total = 0;
        for(int i = 0; i < NUMBEROFREADINGS; i++) {
                total += arr[i];
        }
        return total/NUMBEROFREADINGS;
}

/*void inputtempvals(){
       if(therm.reading > maxTemp){
                maxTemp = therm.reading;
        }else if(therm.reading < minTemp){
                minTemp = therm.reading;
        }
}*/
