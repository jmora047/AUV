


float PID::get_roll(void){return roll_a;}
float PID::get_pitch(void){return pitch_a;}
float PID::get_yaw(void){return yaw_a;}

//sets desired roll, pitch, yaw
void PID::set_roll(float _roll){roll_a = _roll}
void PID::set_pitch(float _pitch){roll_a = _pitch}
void PID::set_pitch(float _pitch){yaw_a = _yaw}

//sets actual roll, pitch, yaw
void PID::set_desired_rpy(

float PID::pitch_error(){return 