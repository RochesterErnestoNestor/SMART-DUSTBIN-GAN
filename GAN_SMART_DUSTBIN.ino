#include <Servo.h>


#define TRIG_PIN A0    // Ultrasonic sensor trigger pin
#define ECHO_PIN A1   // Ultrasonic sensor echo pin
#define IR_PIN A2      // IR sensor pin
#define SERVO_PIN A3   // Servo motor pin
#define BUZZER_PIN A4  // Buzzer pin


Servo servo;
int isOpen = 0;  // Track bin state
int buzzer = 0;  // Track buzzer state


void setup() {
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    pinMode(IR_PIN, INPUT);
    pinMode(BUZZER_PIN, OUTPUT);
   
    servo.attach(SERVO_PIN);
    servo.write(0);  // Start with bin closed
   
    Serial.begin(9600);  // Debugging
}


void loop() {





    long duration, distance; 
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    duration = pulseIn(ECHO_PIN, HIGH);
    distance = (duration/2) / 29.1;
int irStatus = digitalRead(IR_PIN);
Serial.print("Distance: "); 
    Serial.print(distance);
    Serial.print(" cm, IR Sensor: ");
    Serial.println(irStatus);





  if (distance < 20) { 
    Serial.println("Opening Bin");  
    servo.write(90); 
    delay(200); 
while(distance < 20){ 
Serial.println("No Move Bin1"); 
          servo.write(0); 
          digitalWrite(TRIG_PIN, LOW); 
          delayMicroseconds(2);
          digitalWrite(TRIG_PIN, HIGH);
          delayMicroseconds(10);
          digitalWrite(TRIG_PIN, LOW);
          duration = pulseIn(ECHO_PIN, HIGH);
          distance = (duration/2) / 29.1;
          int irStatus = digitalRead(IR_PIN);
          Serial.print(distance); 
          		if(irStatus == LOW) { 
									

					
           			if (buzzer == 0){ 
       				Serial.println("Obstacle detected! Buzzer ON"); 
         				digitalWrite(BUZZER_PIN, HIGH);
         				delay(500); 
   
        				Serial.println("Obstacle detected! Buzzer OFF");
         				digitalWrite(BUZZER_PIN, LOW);
					
       				buzzer = 1; 
            			}
        			



			while (buzzer == 1){ 
				int irStatus = digitalRead(IR_PIN); 
          			Serial.print(irStatus); 
				if(irStatus == LOW) { 
					buzzer = 0;
					delay(5000); 
          				}
			}
     
          		}
      }
 
  }





  else if (distance >= 20) {
	Serial.println("Closing Bin"); 
      servo.write(90); 
      delay(200);
Serial.println("No Move Bin2");
      servo.write(0); 
digitalWrite(TRIG_PIN, LOW); 
      delayMicroseconds(2);
      digitalWrite(TRIG_PIN, HIGH);
      delayMicroseconds(10);
      digitalWrite(TRIG_PIN, LOW);
      duration = pulseIn(ECHO_PIN, HIGH);
      distance = (duration/2) / 29.1;
      int irStatus = digitalRead(IR_PIN);
      buzzer = 0; 
  }
}
