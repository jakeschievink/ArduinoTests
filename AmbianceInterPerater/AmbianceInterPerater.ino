#include <Thermistor.h>
#define DEBUG

//pinSetups
const int ledBluePin = 10;
const int ledYellowPin = 11;
const int ledRedPin = 9;
const int ledWhitePin = 6;
const int sensorPin  = A1;
const int micPin  = A4;

const int numReadings = 10;
const int maxTemp = 200;
const int minTemp = 155;

int photoReadings[numReadings];
int micReadings[numReadings];
int micReadingPos = 0;
int photoReadingPos = 0;
int photoReading, micReading, tempReading, volume;

int photoValue,micValue, tempValue = 0;

Thermistor temp(5);
void setup(){
        pinMode(ledBluePin, OUTPUT);
        pinMode(ledYellowPin, OUTPUT);
        pinMode(ledRedPin, OUTPUT);
        Serial.begin(9600);
}
void loop(){
        photoReading = analogRead(sensorPin);
        photoReadingPos = insert(photoReadings, photoReading, photoReadingPos);
        photoValue = map(average(photoReadings),0,1024, 0, 255);

        micReading = abs(analogRead(micPin)-800);
        micReadingPos = insert(micReadings, micReading, micReadingPos);
        micValue = average(micReadings);

        tempReading = int(temp.getTemp());
        tempValue = map(tempReading, 155, 200, 0, 255);

        //writing to Leds
        writetoLeds();

        #if defined DEBUG
                Serial.print("photo: ");
                Serial.println(photoValue);
                Serial.print("mic: ");
                Serial.println(micReading);
                Serial.print("Temp:");
                Serial.println(tempReading);
        #endif

        delay(1000);
}
void writetoLeds(){
        analogWrite(ledWhitePin, photoValue);
        analogWrite(ledBluePin,255-photoValue);
        analogWrite(ledYellowPin, micValue);
        analogWrite(ledRedPin, tempValue);
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
        for(int i = 0; i < numReadings; i++) {
                total += arr[i];
        }
        return total/numReadings;
}
