const int echoPin = 8;
const int trigPin = 7;
const int answerPin = 12;

const int numReadings = 7;
long wave_timeduration;
int readIndex;
long total;
long average;

void setup() {
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode (answerPin, OUTPUT);
  Serial.begin(9600);
  Serial.println("Waiting for the set up...");
  delay(1000); // this delay is to set up the central MCU and do not let it interpretes some starting signal from this board

}

void loop() {

  measure_distance();

}


int measure_distance(){
  readIndex = 0;
  total = 0;
  average = 0;
  for (readIndex; readIndex < numReadings; readIndex++){
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    wave_timeduration = pulseIn(echoPin, HIGH);
    // Serial.print("Current readIndex: "); Serial.println(readIndex);
    if(wave_timeduration > 30000 ){ //after 38ms the obstacle is out of sensor range
        long distance_cm = 265;
        //Serial.print("Value: "); Serial.println(distance_cm);
        total = total + 265;
        delay(50); 
      }
    else{
      long distance_cm = wave_timeduration / 58.309; //this 58.309 comes from the physics of the problem [wave propagation speed, distance traveled, ... ]
      //Serial.print("Value: "); Serial.println(distance_cm);
      total = total + distance_cm;
      delay(50);
      }
    
   }
 
 average = total / numReadings;
 Serial.print("Average: "); Serial.println(average);

 if (average < 70){ 
    digitalWrite(answerPin, HIGH); // we're surely near an obstacle ! ACTIVATE ALARM
   
  }
  
 else{
    digitalWrite(answerPin, LOW); // we're far from an obstacle
  }
  
 
 
}
