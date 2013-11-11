//...........................................................
// this code Based on : http://playground.arduino.cc/Main/MaxSonar
int pw_pin=3;
long inch;
void setup() {
        // put your setup code here, to run once:
        pinMode(pw_pin, INPUT);
        Serial.begin(9600);
}

void loop() {
        // put your main code here, to run repeatedly:
        inch = pulseIn(pw_pin, HIGH);
        Serial.println(inch/58);
        delay(10);
   //   sensorRead();
   //   array_arrangment(array,arraysize);
   //   exact_cm_value= filter(array,arraysize);
   //   Serial.println(exact_cm_value);

}
