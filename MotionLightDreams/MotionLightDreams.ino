const int ledPin = 13;
const int speakerPin = 9;
const int motionPin = 2;

void setup(){
        pinMode(ledPin, OUTPUT); 
        pinMode(speakerPin, OUTPUT); 
        pinMode(motionPin, INPUT);
        Serial.begin(9600);
        Serial.print("test");
        delay(1000);
}
void loop(){
        int motionval = digitalRead(motionPin);
        Serial.println(motionval, DEC);
        if(motionval == 1){
                Serial.println("morethan0");
                delay(600);
                digitalWrite(speakerPin, HIGH);
        }else{
                delay(100);
                digitalWrite(speakerPin, LOW);
        }
}

