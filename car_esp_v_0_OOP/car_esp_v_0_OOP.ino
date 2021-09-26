class Motor {
  int pinfront; int pinback; int pinPWM; int freq; int pwmChannel; int resolution; int motspeed; int movdir; int motstate;
  public:
    Motor(int pinfront, int pinback, int pinPWM, int pwmChannel){
      this->pinfront = pinfront;
      this->pinback = pinback;
      this->pinPWM = pinPWM;
      this->pwmChannel = pwmChannel;
     
      init();
           
      int freq = 30000;
      int resolution = 8;
      int motspeed = 200;
      int movdir = 0;
      int motstate = 0;
    }
    
    void init() {
      pinMode(pinfront, OUTPUT);
      pinMode(pinback, OUTPUT);    
      pinMode(pinPWM, OUTPUT);

      digitalWrite(pinback, LOW);
      digitalWrite(pinfront, LOW);

      ledcSetup(pwmChannel, freq, resolution);
      ledcAttachPin(pinPWM, pwmChannel);    
    }
    
    
    int getmotspeed() {
      return motspeed; 
    }
    void setmotspeed(int new_motspeed) {
      motspeed = new_motspeed; 
    }

    int getpwmChannel() {
      return pwmChannel; 
    }

    int getmovdir() {
      return movdir; 
    }
    int setmovdir(int new_movdir){
      if (new_movdir == 0){                     // setmovdir(0) => Stop direction
        digitalWrite(pinfront, LOW);
        digitalWrite(pinback, LOW);
        }
      else if (new_movdir == 1){                // setmovdir(1) => Front direction
        
        digitalWrite(pinfront, HIGH);
        digitalWrite(pinback, LOW);
        }
      
      else if(new_movdir == 2){                 // setmovdir(2) => Back direction
        digitalWrite(pinfront, LOW);
        digitalWrite(pinback, HIGH);
        }
      else{
        Serial.println("The new_movdir is outiside the correct range [0,1,2] !");
        }
      
      movdir = new_movdir;
      return movdir;
    }
       

    int setmotstate(int new_motstate){
      if(new_motstate == 1){
        ledcWrite(pwmChannel, motspeed);
        motstate = 1;
        return motstate;
        }
      else if(new_motstate == 0){
        ledcWrite(pwmChannel, 0);
        motstate = 0;
        return motstate;
        }
       else{
        Serial.println("The new_movstate is outiside the correct range [0,1]!");
        }
      }
  
    int getmotstate(){
      return motstate;
      }
    
}; // don't forget the semicolon at the end of the class


/////////////////////////////////////////////////////////////////////

//declaring the istances of the class at a global level
Motor motor1A(25, 33, 32, 0); 
Motor motor1B(27, 14, 26, 1);
Motor motor2A(5, 18, 19, 2);
Motor motor2B(16, 4, 17, 3);

//declaring other const
const int sensorOnePin = 22;  //At this pin there's the answer of the question "Is the distance below 50 cm?"
const int sensorTwoPin = 23;  //At this pin there's the answer of the question "Is the car stucked?"
const int alarmPin = 21;

const int alt = 0;
const int front = 1;
const int back = 2;
const int enabled = 1;
const int disabled = 0;
const int zero = 0;


//declaring variables used in the loop
volatile int status_alarm_one = 0;
volatile int status_alarm_two = 0;
int full = 230;  //the most common motor speed used in the sketch [0-255]


///////////////////////////////////////////////////
////////////////FUNCTION //////////////////////////
///////////////////////////////////////////////////
void gostraight(){
    
    motor1A.setmotspeed(full);
    motor1B.setmotspeed(full);
    motor2A.setmotspeed(full);
    motor2B.setmotspeed(full);
    
    motor1A.setmovdir(front);
    motor1B.setmovdir(front);
    motor2A.setmovdir(front);
    motor2B.setmovdir(front);
        
    motor1A.setmotstate(enabled);
    motor1B.setmotstate(enabled);
    motor2A.setmotstate(enabled);
    motor2B.setmotstate(enabled);

//    Serial.println(motor1A.getmotspeed());
//    Serial.println(motor1B.getmotspeed());
//    Serial.println(motor2A.getmotspeed());
//    Serial.println(motor2B.getmotspeed());
//
//    delay(2000);
  }

void stopcar(){
  
    motor1A.setmotspeed(zero);
    motor1B.setmotspeed(zero);
    motor2A.setmotspeed(zero);
    motor2B.setmotspeed(zero);
  
    motor1A.setmovdir(alt);
    motor1B.setmovdir(alt);
    motor2A.setmovdir(alt);
    motor2B.setmovdir(alt);
    
    motor1A.setmotstate(disabled);
    motor1B.setmotstate(disabled);
    motor2A.setmotstate(disabled);
    motor2B.setmotstate(disabled);
    
//  delay(2000);
    
    }
void turn_right_random(){
  
    int random_ms = random(1200, 2000);
    
    motor1A.setmotspeed(full);
    motor1B.setmotspeed(full/1.1);
    motor2A.setmotspeed(full/1.1);
    motor2B.setmotspeed(full);
    
    motor1A.setmovdir(front);
    motor1B.setmovdir(back);
    motor2A.setmovdir(front);
    motor2B.setmovdir(back);
    
    motor1A.setmotstate(enabled);
    motor1B.setmotstate(enabled);
    motor2A.setmotstate(enabled);
    motor2B.setmotstate(enabled);

    delay(random_ms);
  
    stopcar();
  
  }

void goback(){
    motor1A.setmotspeed(full);
    motor1B.setmotspeed(full);
    motor2A.setmotspeed(full);
    motor2B.setmotspeed(full);
    
    motor1A.setmovdir(back);
    motor1B.setmovdir(back);
    motor2A.setmovdir(back);
    motor2B.setmovdir(back);
        
    motor1A.setmotstate(enabled);
    motor1B.setmotstate(enabled);
    motor2A.setmotstate(enabled);
    motor2B.setmotstate(enabled);
  }
void test_class_attributes(){
  Serial.print("movdir 1A:");
  Serial.println(motor1A.getmovdir());
  Serial.print("pwmChannel 1A:");
  Serial.println(motor1A.getpwmChannel());
  delay(500);
  motor1A.setmovdir(1);
  Serial.print("new movdir 1A:");
  Serial.println(motor1A.getmovdir());
  delay(2000);
  }

void test_interruprt(){
      if(status_alarm_one == 0){
        Serial.println("No interrupt has happened ");
        digitalWrite(alarmPin, LOW);
        }
      else if (status_alarm_one == 1){
        Serial.println("INTERRUPT HAS HAPPENED! ");
        digitalWrite(alarmPin, HIGH);
        status_alarm_one = 0;
        }
  }



void IRAM_ATTR isrOne(){
  status_alarm_one = 1;
  detachInterrupt(digitalPinToInterrupt(sensorOnePin));
  detachInterrupt(digitalPinToInterrupt(sensorTwoPin));
  }
  
void IRAM_ATTR isrTwo(){
  status_alarm_two = 1;
  detachInterrupt(digitalPinToInterrupt(sensorOnePin));
  detachInterrupt(digitalPinToInterrupt(sensorTwoPin));
  }



///////////////////////////////////////////////////////////
/////////////////////// SKETCH ////////////////////////////
///////////////////////////////////////////////////////////
void setup(){   
  pinMode(sensorOnePin, INPUT);
  pinMode(sensorTwoPin, INPUT);
  pinMode(alarmPin, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(sensorOnePin), isrOne, RISING);
  attachInterrupt(digitalPinToInterrupt(sensorTwoPin), isrTwo, HIGH);
  Serial.begin(115200);
  delay(3500); // this delay is to set up the central MCU and wait for the sensor boards
  }
  
void loop() {
      
     // long start_micros = micros();
     if(status_alarm_one == 0 && status_alarm_two == 0){
        gostraight();
        digitalWrite(alarmPin, LOW);
        Serial.println("Current status one: " + String(status_alarm_one) + "    | Current status two: " + String(status_alarm_two));
        }
     else if(status_alarm_one == 1){
        stopcar();
        digitalWrite(alarmPin, HIGH);
        Serial.println("INTERRUPT CORRELATED TO SENSOR ONE HAS HAPPENED! ");
        delay(500);    
        while(status_alarm_one == 1){
          turn_right_random();
          delay(1000);
          status_alarm_one = digitalRead(sensorOnePin);
          Serial.println("----ALARM---- Current status one: " + String(status_alarm_one));
          delay(100);
          }
        attachInterrupt(digitalPinToInterrupt(sensorOnePin), isrOne, RISING);
        attachInterrupt(digitalPinToInterrupt(sensorTwoPin), isrTwo, HIGH);
        digitalWrite(alarmPin, LOW);
        delay(100);
        }
     else if(status_alarm_two == 1){
        stopcar();
        digitalWrite(alarmPin, HIGH);
        detachInterrupt(digitalPinToInterrupt(sensorOnePin));
        detachInterrupt(digitalPinToInterrupt(sensorTwoPin));
        Serial.println("INTERRUPT CORRELATED TO SENSOR TWO HAS HAPPENED! ");
        goback();
        delay(1500);
        stopcar();
        delay(500);
        //while(status_alarm_two == 1){         
          turn_right_random();
          delay(00);
        status_alarm_two = 0;
        attachInterrupt(digitalPinToInterrupt(sensorOnePin), isrOne, RISING);
        attachInterrupt(digitalPinToInterrupt(sensorTwoPin), isrTwo, HIGH);
        digitalWrite(alarmPin, LOW);
        delay(100);
        }
      
     delay (50);

      // long elapsed_micros = micros() - start_micros;

    
}
