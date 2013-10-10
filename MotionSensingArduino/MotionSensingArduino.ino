void setup(){
  Serial.begin(9600);
}
void loop(){
  int motionval = digitalRead(13);
  Serial.println(motionval);
  if(motionval == 1){
    delay(1000);
  }else{
    delay(100);
  }
}
  
