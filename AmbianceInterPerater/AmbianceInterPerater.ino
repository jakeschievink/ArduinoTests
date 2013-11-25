#include <Thermistor.h>
#define DEBUG
#define READINGINTERVAL 1000
#define NUMBEROFREADINGS 10
//pinSetups
const int ledBluePin = 10;
const int ledGreenPin = 11;
const int ledRedPin = 9;
const int ledWhitePin = 6;
const int photoPin  = A1;
const int micPin  = A4;

long time,readingTime, longReadingTime;

struct readVals{
        int reading;
        int readings[NUMBEROFREADINGS];
        int readingPos;
        int value;
        int displayed;
        int max;
        int min;
};
const struct readVals DEFAULTVALS={0,125,0,0,0,0,1000};
struct readVals mic = DEFAULTVALS;
struct readVals photo = DEFAULTVALS;
struct readVals therm;

Thermistor temp(5);
void setup(){
        pinMode(ledBluePin, OUTPUT);
        pinMode(ledGreenPin, OUTPUT);
        pinMode(ledRedPin, OUTPUT);
        pinMode(ledWhitePin, OUTPUT);
        Serial.begin(9600);
        readingTime = 1000;
}
void loop(){
        time = millis();
         
        if(time > readingTime){
                takeReadings();
                readingTime = time+READINGINTERVAL;
                #if defined DEBUG
                        Serial.print("photodisplayed: ");
                        Serial.println(photo.displayed);
                        Serial.print("photovalue: ");
                        Serial.println(photo.value);
                        Serial.print("photomin: ");
                        Serial.println(photo.min);
                        Serial.print("photomax: ");
                        Serial.println(photo.max);
                        Serial.print("photoavg: ");
                        Serial.println(average(photo.readings));


                        Serial.print("mic: ");
                        Serial.println(mic.reading);
                        Serial.print("Temp:");
                        Serial.println(therm.reading);
                #endif
        }
        if(time > longReadingTime){
       }
        
        
        
        updateDisplayedValues();
        //writing to Leds
        writetoLeds();

        

        delay(90);
}
void writetoLeds(){
        analogWrite(ledWhitePin, photo.displayed);
        analogWrite(ledBluePin,255-photo.displayed);
        analogWrite(ledGreenPin, mic.displayed);
        analogWrite(ledRedPin, therm.value);
}
void takeMinMax(struct readVals *comp){
        if((*comp).min == 0){
                (*comp).min = 1000;
        }

        if(average((*comp).readings) < (*comp).min){
                (*comp).min = average((*comp).readings);
                
        }else if(average((*comp).readings) > (*comp).max){
                (*comp).max = average((*comp).readings);
        }

}
void takeReading(struct readVals *comp, int pin){
        (*comp).reading = analogRead(pin);
        (*comp).readingPos = insert((*comp).readings, (*comp).reading, (*comp).readingPos);
        takeMinMax(&*comp);
        (*comp).value = map(average((*comp).readings), (*comp).min, (*comp).max, 0, 255);
}
void takeReadings(){

               takeReading(&photo, photoPin); 

                mic.reading = abs(analogRead(micPin)-840);
                mic.readingPos = insert(mic.readings, mic.reading, mic.readingPos);
                mic.value = average(mic.readings);
                takeMinMax(&mic);
                //mic.value = map(average(mic.readings),50,255,0,255);

                therm.reading = int(temp.getTemp());
                therm.value = map(therm.reading, 155, 200, 0, 255);
}
void updateDisplayedValues(){
        photo.displayed = photo.displayed*.9+.1*photo.value;
        mic.displayed = mic.displayed*.9+.1*mic.value;
}

int insert(int arr[], int item, int pos){
        if(pos == 11){
                return 0;
        }else{
                arr[pos]=item;
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
