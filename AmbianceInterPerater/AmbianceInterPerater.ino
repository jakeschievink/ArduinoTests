#include <Thermistor.h>

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
        Serial.print("photo: ");
        Serial.println(photoValue);

        micReading = abs(analogRead(micPin)-800);
        Serial.print("mic: ");
        Serial.println(micReading);
        micReadingPos = insert(micReadings, micReading, micReadingPos);
        micValue = average(micReadings);

        tempReading = int(temp.getTemp());
        Serial.println(tempReading);
        tempValue = map(tempReading, 155, 200, 0, 255);

        //writing to Leds
        analogWrite(ledWhitePin, photoValue);
        analogWrite(ledBluePin,255-photoValue);
        analogWrite(ledYellowPin, micValue);
        analogWrite(ledRedPin, tempValue);

        delay(1000);
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
        for(int i = 0; i < numReadings; i = i + 1) {
                total += arr[i];
        }
        return total/numReadings;
}
