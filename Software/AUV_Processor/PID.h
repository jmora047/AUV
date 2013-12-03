



class AUV
{
/* Public Functions ----------------------------------------------------------- */
    float get_pitch(void);
	float get_roll(void);
	float get_yaw(void);
	
	void set_roll(float _roll);
	void set_pitch(float _pitch);
	void set_yaw(float _yaw);
	//sets desired RPM
	void set_desired_rpy(float _roll_d, _pitch_d, _yaw_d);

  public:
	//actual roll, pitch, yaw
	float roll_a;
	float pitch_a;
	float yaw_a;
	//desired roll, pitch, yaw
    float roll_d;
	float pitch_d;
	float yaw_d;
};