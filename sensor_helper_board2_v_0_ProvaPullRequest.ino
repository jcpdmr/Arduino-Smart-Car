const int sensorPin = 11;
const int alarmPin = 12;
const int num_samples = 20;
int last_sum = 0;

void loop() {
  int sample_sum = sum_read();
  //Serial.println("The result of the first sample: " + String(first_sum));
 
  if(sample_sum == 0 || sample_sum == num_samples){
      digitalWrite(alarmPin, HIGH);
      }
  else{
      digitalWrite(alarmPin, LOW);
      }  

 delay(2000); //the meaning of this big delay is to prevent the activation of the alarm by accidental stop of the wheel during the change of direction
}


// PROVA PROVA 123 PROVA PROVA 123 PER APRIRE UNA PULL REQUEST
