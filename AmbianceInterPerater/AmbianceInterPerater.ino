//pinSetups
const int ledBluePin = 10;
const int ledYellowPin = 11;
const int ledRedPin = 9;
const int sensorPin  = A1;
const int micPin  = A4;

const int numReadings = 10;

int photoReadings[numReadings];
int micReadings[numReadings];
int micReadingPos = 0;
int photoReadingPos, micReading, volume;

int photoValue,micValue = 0;
void setup(){
        pinMode(ledBluePin, OUTPUT);
        pinMode(ledYellowPin, OUTPUT);
        pinMode(ledRedPin, OUTPUT);
        Serial.begin(9600);
}
void loop(){
        photoValue = map(analogRead(sensorPin),0,1024, 0, 255);


        micReading = abs(analogRead(micPin)-800);
        micReadingPos = insert(micReadings, micReading, micReadingPos);
        micValue = average(micReadings);

        //writing to Leds
        analogWrite(ledYellowPin, photoValue);
        analogWrite(ledBluePin,255-photoValue);
        analogWrite(ledRedPin, micValue);

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
                Serial.print(arr[i]);
                Serial.print(" ");
        }
        return total/numReadings;
}
