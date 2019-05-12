/*
 * Project modules
 * 
 * (1) tank_main.ino   = variables declaration/initialization, setup and loop function
 * (2) bdc_encoder.ino =  routines for encoder output handling, including interrupts service routines
 * (3) bdc_motor.ino
 * 
 * Pinning / Setup
 * Pin 2 (Port Interrupt 2) for encoder motor left
 * Pin 3 (Port Interrupt 3) for encoder motor right
 * 
 * Board: ARDUINO MEGA 1650 r3
 * 
 * 
 * 
 */

/*
*******************************************************************************************************
* Module global variables declaration 
*******************************************************************************************************
*/
/* Left side DC Motor control pins motor control IC */
int pin02_Encoder_Left  = 2;  // Hardware interrupt pin at digital pin 2 (INT4).  =Left side Motor
int pin18_Encoder_Left  = 18; // Hardware interrupt pin at digital pin 2 (INT3).  =Left side Motor
int pin04_enable_mot_L = 4;
int pin05_dir1_mot_L   = 5;
int pin06_dir2_mot_L   = 6;

/* Right side DC Motor control pins motor control IC */
int pin03_Encoder_Right = 3;  // Hardware interrupt pin at digital pin 2 (INT5).  =Right Side Motor
int pin07_enable_mot_R = 7;
int pin08_dir1_mot_R   = 8;
int pin09_dir2_mot_R   = 9;
int time_stamp_A2;

/* Motor speed and setpoint variables */
float s_R  = 0;  // Actual speed right motor
float s_L  = 0;  // Actual speed left motor
float sp_R = 30;  // Speed setpoint right motor
float sp_L = 30;  // Speed Setpoint left motor

float s_pwm_L = 0;
float s_pwm_R = 0;  

/* Serial communication */
char rx_byte = 0;


void setup() {
  pinMode( pin02_Encoder_Left,  INPUT );//_PULLUP);  // configure pin2 as an input, pulled HIGH to the logic voltage (5V or 3.3V for most cases)
  pinMode( pin03_Encoder_Right, INPUT );//_PULLUP); // configure pin3 as an input, pulled HIGH to the logic voltage (5V or 3.3V for most cases)
  pinMode( pin18_Encoder_Left, INPUT );//_PULLUP); // set pinB as an input, pulled HIGH to the logic voltage (5V or 3.3V for most cases)
  
  attachInterrupt(digitalPinToInterrupt(2), PinA1,RISING); // set an interrupt on PinA, looking for a rising edge signal and executing the "PinA" Interrupt Service Routine (below)
  attachInterrupt(digitalPinToInterrupt(18),PinA2,RISING); // 18 =MOT B
  attachInterrupt(digitalPinToInterrupt(3), PinB,RISING); // set an interrupt on PinB, looking for a rising edge signal and executing the "PinB" Interrupt Service Routine (below)
  
  //Serial.begin(115200); // start the serial monitor link



  /////////////////////////////////////////////////////////////////////////////////////////////////////////
  // initialize timer1 
  // Timer used for back ground tasks (speed controller calculation, sensor inputs evaluation)
  //
  
  noInterrupts();           // disable all interrupts
  TCCR1A = 0;     // TCCR1A = timer counter control register 1A
  TCCR1B = 0;     // ICNC1 ICES1 WGM13 WGM12 CS12 CS11 CS10
  // Set timer1_counter to the correct value for our interrupt interval
  //timer1_counter = 64911;   // preload timer 65536-16MHz/256/100Hz
  //timer1_counter = 64286;   // preload timer 65536-16MHz/256/50Hz
  //timer1_counter = 34286;   // preload timer 65536-16MHz/256/2Hz
  //timer1_counter = 64000;     // entspricht 20.33 Hz
  //TCNT1 = timer1_counter;     // preload timer
  TCCR1B |= (1 << CS12);      // 256 prescaler. CS12 = Clock Select --> Select the Clock source for the timer --> CS12=>clk/256
  //TCCR1B |= 0x4;            // Direktes schreiben der Registerbits geht auch ... siehe Datenblatt zu TCCR1B, Tabelle auf Seite 173
  //TCCR1B |= (1 << CS11);    // 256 prescaler. CS12 = Clock Select --> Select the Clock source for the timer --> CS12=>clk/256
  
  TIMSK1 |= (1 << TOIE1);   // enable timer overflow interrupt (Interrupt Mask Register)
  interrupts();             // enable all interrupts
  
  Serial.begin(9600);
  Serial.println("Start the program");

  // setup the used pins for configuration inputs of L293D motor control IC
  pinMode(pin04_enable_mot_L, OUTPUT);   // Motor1 enable pin control IC
  pinMode(pin05_dir1_mot_L, OUTPUT);     // Motor1 Direction 01 input pin
  pinMode(pin06_dir2_mot_L, OUTPUT);     // Motor1 Direction 10 input pin

  pinMode(pin07_enable_mot_R, OUTPUT);   // Motor2 enable pin control IC
  pinMode(pin08_dir1_mot_R, OUTPUT);     // Motor2 Direction 01 input pin
  pinMode(pin09_dir2_mot_R, OUTPUT);     // Motor2 Direction 10 input pin

 // pinMode(pin3_speed_mot_L_in, INPUT);  // Motor1 speed input (PWM in)
  //pinMode(pin2_speed_mot_R_in, INPUT);  // Motor2 speed input (PWM in)

  digitalWrite(pin04_enable_mot_L, 1);  // Enable1 pin of L293D
  digitalWrite(pin07_enable_mot_R, 1);  // Enable2 pin of L293D

  DriveMotor(sp_L,sp_R);
  
}



void loop(){

  //if((s_L-s_R)<0)sp_R++;
  
  /* Speed controller muss noch in definiertem Zeitmuster aufgerufen werden! 
   *  Z.B. Timer etc.!! 
   */
  s_pwm_L = S_Control_L_PI ( s_L, sp_L);
  s_pwm_R = S_Control_R_PI ( s_R, sp_R);
  
  //DriveMotor(sp_R,s_pwm_L);
  
  DriveMotor(s_pwm_L,s_pwm_R);
  
  Serial.print("Speed R=");
  Serial.print(s_R);
  Serial.print(" ");
  Serial.print("Speed L=");
  Serial.print(s_L);
  Serial.print(" s_L-s_R=");
  Serial.print(s_L-s_R);
  Serial.print(" s_pwm_L=");
  Serial.print(s_pwm_L);
  
 // Serial.print(" s_Icon=");
 // Serial.print(S_Icon);

  //Serial.print(" error=");
  //Serial.print(e);
  
  Serial.print(" time_stamp_a2=");
  Serial.println(time_stamp_A2);



 
  }
