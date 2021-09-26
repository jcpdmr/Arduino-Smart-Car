const int sensorPin = 11;
const int alarmPin = 12;
const int num_samples = 20;
int last_sum = 0;

void setup() {
  pinMode(sensorPin, INPUT);
  pinMode(alarmPin, OUTPUT);
  //Serial.begin(9600);
  delay(5000); // this delay is to set up the central MCU and do not let it interpretes some starting signal from this board
}

void loop() {
  int sample_sum = sum_read();
  //Serial.println("The result of the first sample: " + String(first_sum));
 
  if(sample_sum == 0 || sample_sum == num_samples){
      digitalWrite(alarmPin, HIGH);
      //Serial.println("The car is stucked!");
      delay(100);
      while(loop_sum == first_sum){
        loop_sum = sum_read();   
        } 
      digitalWrite(alarmPin, LOW);
      delay(500);
      }
    }

 delay(50);
}

int sum_read(){
  int sum = 0;
  for(int i = 0; i < num_samples; i++){
    sum = sum + digitalRead(sensorPin);
    //Serial.println("Attempt: " + String(i) + " | Value: " + String(digitalRead(sensorPin)));
    delay(30);
    }
  return sum; 
  }
