/*=====TOP-DOWN VIEW======

			3
	        |		1
	5================
			|		2
			4

==========================
roll error > 0


========================*/

//Proportionality constants in the direction of thrust
#define kp_m1_thrust 1.0
#define kp_m2_thrust 1.0
#define kp_m3_thrust 1.0
#define kp_m4_thrust 1.0
#define kp_m5_thrust 1.0


struct Orientation {
	float roll, pitch, yaw;				//AUV actual orientation  (range: -180 to 180)
	float roll_d, pitch_d, yaw_d;		//AUV desired orientation (range: -180 to 180)
}

/* to_360 - takes a degree value from -180 to 180 and converts it to a
			degrees value ranging from 0 to 360
   @param fpFrom180  - a degree value ranging from -180 to 180 derived from the IMU
   @return float    - a scaled degree value ranging from 0 to 360
*/
float to_360(float fpFrom180){
	if (fpFrom180 <= 180 && fpFrom180 >= 0) return fpFrom180;
	else return 360 + fpFrom180;
}
/* get_error - obtains the difference between the setpoint and actual values
   @param fpSetPoint - the desired angular position (-180 to 180)
   @param fpActual	 - the actual angular position (-180 to 180)
   @return fpError 	 - the difference between the angular positions (-180 to 180)
*/
float get_error(float fpSetPoint, float fpActual){
	fpAbsDiff = to_360(fpSetpoint) - to_360(fpActual);
	if (fpAbsDiff >= -180 && fpAbsDiff <= 180)
		return fpAbsDiff;
	else if (fpAbsDiff < -180)
		return fpAbsDiff + 360;
	else
		return -(fpAbsDiff + 360);
}

void adjust(){

}