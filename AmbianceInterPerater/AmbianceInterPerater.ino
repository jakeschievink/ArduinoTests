const int ledBluePin = 10;
const int ledYellowPin = 11;
const int ledRedPin = 9;
const int sensorPin  = A1;
const int numReadings = 10;
int photoreadings[numReadings];

int sensorValue = 0;
void setup(){
        pinMode(ledBluePin, OUTPUT);
        pinMode(ledYellowPin, OUTPUT);
        pinMode(ledRedPin, OUTPUT);
        Serial.begin(9600);
}
void loop(){
        sensorValue = map(analogRead(sensorPin),0,1024, 0, 255);
        analogWrite(ledYellowPin, sensorValue);
        analogWrite(ledBluePin, 255-sensorValue);
        analogWrite(ledRedPin, sensorValue);

        Serial.println(sensorValue);
}
