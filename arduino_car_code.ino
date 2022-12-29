#include<SoftwareSerial.h>

int ledPin = A15;   //the number of the LED pin
int ldrPin = A14;  //the number of the LDR pin
//rgb pins
int rgb1 = 48;
int rgb2 = 50;
int rgb3 = 52;
//Front Motor Pins  
int Enable1 = 7;
int Motor1_Pin1 = 6;  
int Motor1_Pin2 = 5;  
//Back Motor Pins      
int Motor2_Pin1 = 4; 
int Motor2_Pin2 = 3;
int Enable2 = 2;
//ultrasonic
int trigPin = 44;
int echoPin = 46;
//bluetooth
int bluetoothTx = 0; 
int bluetoothRx = 1; 

void setup() {

  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);  
  pinMode(ldrPin, INPUT);

  pinMode(rgb1, OUTPUT);
  pinMode(rgb2, OUTPUT);
  pinMode(rgb3, OUTPUT);

  pinMode(Enable1, OUTPUT);
  pinMode(Motor1_Pin1, OUTPUT);  
  pinMode(Motor1_Pin2, OUTPUT);  
  pinMode(Motor2_Pin1, OUTPUT);  
  pinMode(Motor2_Pin2, OUTPUT);
  pinMode(Enable2, OUTPUT);
  digitalWrite(Enable1, HIGH);
  digitalWrite(Enable2, HIGH);

  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
}//void setup


void loop() {
  char c;
   if(Serial.available()>0){
      c = Serial.read();
      Serial.println(c);
switch(c){
     case 'F':  //Moving the Car Forward
      digitalWrite(Motor2_Pin2, LOW);
      digitalWrite(Motor2_Pin1, HIGH);
      digitalWrite(Motor1_Pin1, LOW);
      digitalWrite(Motor1_Pin2, LOW);
      UltraSonic();
      break;
    case 'B':  //Moving the Car Backward
      digitalWrite(Motor2_Pin1, LOW);
      digitalWrite(Motor2_Pin2, HIGH);
      digitalWrite(Motor1_Pin1, LOW);
      digitalWrite(Motor1_Pin2, LOW);
       UltraSonic();  
      break;
    case 'L':  //Moving the Car Left
      digitalWrite(Motor1_Pin1, LOW);
      digitalWrite(Motor1_Pin2, HIGH);
      digitalWrite(Motor2_Pin1, LOW);
      digitalWrite(Motor2_Pin2, LOW);
       UltraSonic();
      break;
    case 'R':   //Moving the Car Right
      digitalWrite(Motor1_Pin2, LOW);
      digitalWrite(Motor1_Pin1, HIGH);  
      digitalWrite(Motor2_Pin1, LOW);
      digitalWrite(Motor2_Pin2, LOW);
       UltraSonic();
      break;
    case 'S':   //Stop
      digitalWrite(Motor2_Pin2, LOW);
      digitalWrite(Motor2_Pin1, LOW);
      digitalWrite(Motor1_Pin2, LOW);
      digitalWrite(Motor1_Pin1, LOW);
      break; 
    case 'I':  //Moving the Car Forward right
      digitalWrite(Motor2_Pin2, LOW);
      digitalWrite(Motor2_Pin1, HIGH);
      digitalWrite(Motor1_Pin2, LOW);
      digitalWrite(Motor1_Pin1, HIGH);
       UltraSonic();
      break; 
    case 'J':  //Moving the Car backward right
      digitalWrite(Motor1_Pin2, LOW);
      digitalWrite(Motor1_Pin1, HIGH);
      digitalWrite(Motor2_Pin1, LOW);
      digitalWrite(Motor2_Pin2, HIGH);
       UltraSonic();
    
      break;        
    case 'G':  //Moving the Car Forward left
      digitalWrite(Motor2_Pin2, LOW);
      digitalWrite(Motor2_Pin1, HIGH);
      digitalWrite(Motor1_Pin1, LOW);
      digitalWrite(Motor1_Pin2, HIGH);
       UltraSonic();
      break; 
    case 'H':  //Moving the Car backward left
      digitalWrite(Motor2_Pin1, LOW);
      digitalWrite(Motor2_Pin2, HIGH);
      digitalWrite(Motor1_Pin1, LOW);
      digitalWrite(Motor1_Pin2, HIGH);
       UltraSonic();
      break;
    case 'W':  //Front light ON 
      digitalWrite(ledPin, HIGH);
      break;
    case 'w':  //Front light OFF
      digitalWrite(ledPin, LOW);
      break;
    case 'U':  //Back light ON 
     
      break;
    case 'u':  //Back light OFF 
      
      break; 
    case 'V':  //Horn On
      
      break; 
    case 'v':  //Horn OFF 
    
      break;   
    case 'x': //Turn ON Everything

    break;
    case 'X': //Turn OFF Everything
      
    break;

    //Controlling the Speed of Car  
    default:  //Get velocity
    int v;
      if(c == 'q'){
        v = 255;  //Full velocity
        analogWrite(Enable2, v);
      }
      else{ 
        if((c >= 48) && (c <= 57)){ 
          v = (c - 48)*25;       
          analogWrite(Enable2, v);
        }
      }
   }//end switch
      
   }//end if
   LDR();
   }//end loop  
void LDR(){  
int ldrStatus = analogRead(ldrPin);   
   if (ldrStatus >=300) {
    digitalWrite(ledPin, HIGH);  
    digitalWrite(rgb1, HIGH);
    digitalWrite(rgb2, HIGH);
    digitalWrite(rgb3, HIGH);//turn LED on
    ///Serial.println(ldrStatus ); 
   }//end if
  else {
    digitalWrite(ledPin, LOW);  
    digitalWrite(rgb1, LOW);
    digitalWrite(rgb2, LOW);
    digitalWrite(rgb3, LOW);//turn LED off
    //Serial.println(ldrStatus);
  }//end else
}//end LDR

void UltraSonic(){
  long duration;
  int distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm"); 
  if(distance > 3){
      digitalWrite(Motor2_Pin2, LOW);
      digitalWrite(Motor2_Pin1, LOW);
      digitalWrite(Motor1_Pin1, LOW);
      digitalWrite(Motor1_Pin2, LOW);delay(10);
  }//end if
  }//end UltraSonic