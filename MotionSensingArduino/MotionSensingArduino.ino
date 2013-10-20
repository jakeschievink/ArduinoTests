void setup(){
  Serial.begin(9600);
  delay(1000);
}
void loop(){
  int motionval = digitalRead(13);
  Serial.println(motionval, DEC);
  if(motionval == 1){
    delay(600000);
  }else{
    delay(100);
  }
}
  
