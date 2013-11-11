int micReadings[] = {0,0,0,0,0,0,0,0,0,0};
int micReadingPos = 0;
int status, micReading, micAverage;
int top = -1;
int micTotal = 0;
const int micPin = 0;
/*PUSH FUNCTION*/

void setup(){
        Serial.begin(9600);
        }

void loop() 
{
        micReading = abs(analogRead(micPin)-800);
        Serial.println(micReading);
        micReadingPos = insert(micReadings, micReading, micReadingPos);
        
        delay(1000);
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
        for(int i = 0; i < 10; i = i + 1) {
                total += arr[i];
//              Serial.print(arr[i]);
//              Serial.print(" ");
        }
        return total/10;
}
