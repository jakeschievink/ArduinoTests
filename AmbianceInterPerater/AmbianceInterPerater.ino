#include <Thermistor.h>
#define DEBUG
#define READINGINTERVAL 100
#define NUMBEROFREADINGS 20
//pinSetups
const int ledBluePin = 9;
const int ledGreenPin = 10;
const int ledRedPin = 11;
const int photoPin  = A0;
const int micPin  = A2;
const int motionPin  = 2;
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
const int defaultreadings[NUMBEROFREADINGS] = { 125 };
const struct readVals DEFAULTVALS={0,*defaultreadings,0,0,0,0,1000};
struct readVals mic = DEFAULTVALS;
struct readVals photo = DEFAULTVALS;
//struct readVals therm;
struct readVals motion;

//Thermistor temp(1);
void setup(){
        pinMode(ledBluePin, OUTPUT);
        pinMode(ledGreenPin, OUTPUT);
        pinMode(ledRedPin, OUTPUT);
        Serial.begin(9600);
        readingTime = 1000;
}
void loop(){
        time = millis();
 //Takes Sensor readings at a specified interval        
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
                        Serial.println(*photo.readings);


                        Serial.print("mic displayed: ");
                        Serial.println(mic.displayed);

                        Serial.print("Motion:");
                        for(int i = 0; i < NUMBEROFREADINGS; i++){
                                Serial.print(motion.readings[i]);
                        }
                        Serial.println(motion.value);
                #endif
        }
       //updated the values displayed to smooth the color transitions 
        updateDisplayedValues();
        //writing to Leds
        writetoLeds();

        

        delay(90);
}
void writetoLeds(){
        analogWrite(ledBluePin,255-photo.displayed);
        analogWrite(ledGreenPin, mic.displayed);
        analogWrite(ledRedPin, motion.displayed*.7);
}
void takeMinMax(struct readVals *comp){
        if((*comp).min == 0){
                (*comp).min = 1000;
        }

        if(average((*comp).readings) < (*comp).min){
                (*comp).min = abs(average((*comp).readings));
                
        }else if(average((*comp).readings) > (*comp).max){
                (*comp).max = abs(average((*comp).readings));
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
                takeMinMax(&mic);
                mic.value = map(average(mic.readings), mic.min, mic.max, 0, 255);
                //mic.value = map(average(mic.readings),50,255,0,255);*/
                motionReading();
                takeMinMax(&motion);
                motion.value = map(average(motion.readings), motion.min, motion.max, 0, 255);

                //therm.reading = int(temp.getTemp());
                //therm.value = map(therm.reading, 155, 200, 0, 255);
}
void motionReading(){
        if(digitalRead(motionPin) == 1){
                motion.reading = 1024;
        }else{
                motion.reading = 0;
        }
        motion.readingPos = insert(motion.readings, motion.reading, motion.readingPos);
}
void updateDisplayedValues(){
        //Smpooths the displayed values
        photo.displayed = photo.displayed*.9+.1*photo.value;
        mic.displayed = mic.displayed*.9+.1*mic.value;
        motion.displayed = motion.displayed*.9+.1*motion.value;
}
//Adds item to readings array
int insert(int arr[], int item, int pos){
        if(pos == 11){
                return 0;
        }else{
                arr[pos]=item;
                pos++;
                return pos;
        }
}
//returns average of an array
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
