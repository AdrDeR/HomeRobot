// modulename: bdc_encoder.ino


/* Global counter to get time stamp */
static unsigned int g_t_count=0;

/* Timer 1 counter variables */
volatile int timer1_ofl_counter=0;
volatile int timer1_counter;


/* Interrupt Service Routine for Encoder output motor left duty cycle and rotational direction check */
void PinA1(){
  
  unsigned int counter = TCNT1;  // quickly save it
  g_t_count=counter;
  static unsigned int time_stamp_A;
  static int flag=0;

  //cli(); //stop interrupts happening before we read pin values
  
  if(flag==0)
   {
    time_stamp_A=counter;
    flag=1;
   }
   else
   {
    if(!timer1_ofl_counter) {
    time_stamp_A=counter-time_stamp_A;
    flag=0;}
    else
    {
          timer1_ofl_counter=0;
          flag=0;
    }
       
    if(time_stamp_A>0)
     {
      //s_R=264000/time_stamp_A;     
      s_R=90000/time_stamp_A;  
     }

     //if(time_stamp_A>10000)s_R=0;
    }
    
    

  //sei(); //restart interrupts
}

void PinA2(){
  unsigned int counter = TCNT1;  // quickly save it
  
  static int flag2=0;

  //cli(); //stop interrupts happening before we read pin values
   if(!timer1_ofl_counter)     
   {
    time_stamp_A2=(int)counter-(int)g_t_count;
   }
   else
   {
    timer1_ofl_counter=0;
   }
   
    //if(time_stamp_A2<0)
     

  //sei(); //restart interrupts
}

void PinB(){
  unsigned int counter = TCNT1;  // quickly save it
  static unsigned int time_stamp_B;
  static int flag=0;
  cli(); //stop interrupts happening before we read pin values
 
  if(flag==0)
   {
    time_stamp_B=counter;
    flag=1;
    
   }
   else
   {
    time_stamp_B=counter-time_stamp_B;
    flag=0;
    if(time_stamp_B>0)
     {
      //s_L=264000/time_stamp_B;  
      s_L=90000/time_stamp_B;      
     }
   }
   
  sei(); //restart interrupts
}


ISR(TIMER1_OVF_vect)        // interrupt service routine 
{
  //TCNT1 = timer1_counter;   // preload timer
  //timer1_counter=TCNT1;
  timer1_ofl_counter++;
  //digitalWrite(ledPin, digitalRead(ledPin) ^ 1);
}
