#include "mbed.h"
#include <SPISlave.h>

/*=====TOP-DOWN VIEW======

            3
            |       1
    5================
            |       2
            4

========================*/

//Proportionality constants in the direction of thrust
#define kp_m1_roll_thrust 0.002
#define kp_m1_pitch_thrust 0.002
#define kp_m2_roll_thrust 0.002
#define kp_m2_pitch_thrust 0.002
#define kp_m3_thrust 0.005
#define kp_m4_thrust 0.005
#define kp_m5_thrust 0.005


float m1_speed, m2_speed, m3_speed, m4_speed, m5_speed; //the speed output to the motors (between -1.0 and 1.0)

float roll, pitch, yaw;             //AUV actual orientation  (range: -180 to 180)
float roll_d, pitch_d, yaw_d;       //AUV desired orientation (range: -180 to 180)
float roll_error, pitch_error, yaw_error;   //the roll, pitch, and yaw errors (range: -180 to 180)

/*SPI communication with Arduino*/
SPISlave rpy_ins(p5, p6, p7, p8);   // mosi, miso, sclk, ssel

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
   @param fpActual   - the actual angular position (-180 to 180)
   @return fpError   - the difference between the angular positions (-180 to 180)
*/
float get_error(float fpSetPoint, float fpActual){
    double fpAbsDiff = to_360(fpSetPoint) - to_360(fpActual);
    if (fpAbsDiff >= -180 && fpAbsDiff <= 180)
        return fpAbsDiff;
    else if (fpAbsDiff < -180)
        return fpAbsDiff + 360;
    else
        return -(fpAbsDiff + 360);
}

/*  set_rpy - saves roll, pitch , yaw from IMU code
    @param roll_n - the new roll (-180 to 180)
    @param pitch_n - the new pitch (-180 to 180)
    @param yaw_n - the new yaw (-180 to 180)
    */
void set_rpy(float roll_n, float pitch_n, float yaw_n){
    roll = roll_n;
    pitch = pitch_n;
    yaw = yaw_n;
}

/*  get_rpy_errors - calculates roll, pitch, and yaw errors
*/
void get_rpy_errors(){
    roll_error = get_error(roll_d, roll);
    pitch_error = get_error(pitch_d, pitch);
    yaw_error = get_error(yaw_d, yaw);
}

/* adjust - applies proportional control to motors
*/
void adjust(){
    get_rpy_errors();
    //adjust motors 1,2 and 5
    if (roll_error > 0){
        if(pitch_error > 0){
            m1_speed = kp_m1_roll_thrust*roll_error + kp_m1_pitch_thrust*pitch_error;
            m2_speed = kp_m2_pitch_thrust*pitch_error;
            }
        else{
            m1_speed = kp_m1_roll_thrust*roll_error;
            m2_speed = 0;
            m5_speed = kp_m5_thrust*(-roll_error);
            }
    }
    else{
        if(pitch_error > 0){
            m1_speed = kp_m1_pitch_thrust*pitch_error;
            m2_speed = kp_m2_roll_thrust*roll_error + kp_m2_pitch_thrust*pitch_error;
            }
        else{
            m1_speed = 0;
            m2_speed = kp_m2_roll_thrust*roll_error;
            m5_speed = kp_m5_thrust*(-roll_error);
            }   
    }
    
    //adjust motor 3 and 4
    if (yaw_error < 0){
        m3_speed = kp_m3_thrust * yaw_error;
        m4_speed = 0;
        }
    else{
        m3_speed = 0;
        m4_speed = kp_m4_thrust * (-yaw_error);
    }
}

int main(){
roll_d = 0;
pitch_d = 0;
yaw_d = 0;
roll = 0;
pitch = -0;
yaw = 0;

rpy_in.format(,);   // __ bits per spi frame, ___ polarity, detect on ___ edge
rpy_in.frequency(4000000); // set SPI bus frequency

char to_float[4] = {0,0,0,0};

while(1){

    for (int i = 0, i < 4, ++i){
        while(!rpy_in.receive()){}
            *(to_float+i) = rpy_in.read();
    }
    roll = (float)to_float;

    for (int i = 0, i < 4, ++i){
        while(!rpy_in.receive()){}
            *(to_float+i) = rpy_in.read();
    }
    pitch = (float)to_float;

    for (int i = 0, i < 4, ++i){
        while(!rpy_in.receive()){}
            *(to_float+i) = rpy_in.read();
    }
    yaw = (float)to_float;
    
    set_rpy(roll, pitch, yaw);
    adjust();

}

}