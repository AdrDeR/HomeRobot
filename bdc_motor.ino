// set the motor speed

#define   MAXPWMDUTY 80
#define   MAXINTEGRATIVE 4000
#define   PID_SPEED_TS 1
#define   KP .4
#define   KI 0.2



  
void DriveMotor( float speed_L, float speed_R )
{
  if (speed_L>=0)
  {
  analogWrite(pin05_dir1_mot_L, 0);       // 40 langsame fahrt
  analogWrite(pin06_dir2_mot_L, speed_L);   // 40 langsame fahrt
  }
  else
  {
   analogWrite(pin05_dir1_mot_L, -speed_L);   // 40 langsame fahrt
   analogWrite(pin06_dir2_mot_L, 0);       // 40 langsame fahrt
  }
  
  if (speed_R>=0)
  {
   analogWrite(pin08_dir1_mot_R, 0);       // 40 langsame fahrt
   analogWrite(pin09_dir2_mot_R, speed_R);   // 40 langsame fahrt
  }
  else
  {
   analogWrite(pin08_dir1_mot_R, -speed_R);   // 40 langsame fahrt
   analogWrite(pin09_dir2_mot_R, 0);       // 40 langsame fahrt
  }
}


int S_Control_L_PI (float s, float s_p)   // s = speed, s_p = speed setpoint                     
{
  static float  S_Pcon =0, s_out =0, e; 
  static float  S_Icon =0;
  
  // PI Control Calculation 
  e      = (s_p - s);             // Calculate speed error 
  S_Pcon = (PID_SPEED_TS * e * KP);  // Calculate proportional term
  S_Icon = S_Icon + (e * KI);               // Calculate integrative term (Aufintegrieren des Fehlers)
  
  // Limitation of Integrative Sum 
  if (S_Icon > MAXINTEGRATIVE){ S_Icon = MAXINTEGRATIVE;}
   else if (S_Icon < -MAXINTEGRATIVE) { S_Icon = -MAXINTEGRATIVE; }
    
    //SpeedOutputPI_i32 = (SummarizedRpmIcontribution_i32/16 + (PID_SPEED_TS * SpeedPcontribution_i32)/16)/1; // Control loop output (/1000 weil PID_SPEED_TS in ms!)
  s_out = (S_Icon/1 + S_Pcon)/2;  // Control loop output (/1000 weil PID_SPEED_TS in ms!)
   // Limit to MAXPWMDUTY  
  if(s_out < -MAXPWMDUTY){s_out = -MAXPWMDUTY;}
   else if(s_out > MAXPWMDUTY){s_out = MAXPWMDUTY;}
  
  return ((int)s_out);                                     // return controller output
}

int S_Control_R_PI (float s, float s_p)   // s = speed, s_p = speed setpoint                     
{  
  static float  S_Pcon =0, s_out =0, e; 
  static float  S_Icon =0;
  // PI Control Calculation 
  e      = (s_p - s);             // Calculate speed error 
  S_Pcon = (PID_SPEED_TS * e * KP);  // Calculate proportional term
  S_Icon = S_Icon + (e * KI);               // Calculate integrative term (Aufintegrieren des Fehlers)
  
  // Limitation of Integrative Sum 
  if (S_Icon > MAXINTEGRATIVE){ S_Icon = MAXINTEGRATIVE;}
   else if (S_Icon < -MAXINTEGRATIVE) { S_Icon = -MAXINTEGRATIVE; }
    
    //SpeedOutputPI_i32 = (SummarizedRpmIcontribution_i32/16 + (PID_SPEED_TS * SpeedPcontribution_i32)/16)/1; // Control loop output (/1000 weil PID_SPEED_TS in ms!)
  s_out = (S_Icon/1 + S_Pcon)/2;  // Control loop output (/1000 weil PID_SPEED_TS in ms!)
   // Limit to MAXPWMDUTY  
  if(s_out < -MAXPWMDUTY){s_out = -MAXPWMDUTY;}
   else if(s_out > MAXPWMDUTY){s_out = MAXPWMDUTY;}
  
  return ((int)s_out);                                     // return controller output
}
