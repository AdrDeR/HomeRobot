// set the motor speed
void DriveMotor( float speed1, float speed2 )
{
  if (speed1>=0)
  {
  analogWrite(pin05_dir1_mot_L, 0);       // 40 langsame fahrt
  analogWrite(pin06_dir2_mot_L, speed1);   // 40 langsame fahrt
  }
  else
  {
   analogWrite(pin05_dir1_mot_L, -speed1);   // 40 langsame fahrt
   analogWrite(pin06_dir2_mot_L, 0);       // 40 langsame fahrt
  }
  
  if (speed2>=0)
  {
   analogWrite(pin08_dir1_mot_R, 0);       // 40 langsame fahrt
   analogWrite(pin09_dir2_mot_R, speed2);   // 40 langsame fahrt
  }
  else
  {
   analogWrite(pin08_dir1_mot_R, -speed2);   // 40 langsame fahrt
   analogWrite(pin09_dir2_mot_R, 0);       // 40 langsame fahrt
  }
}
