#define R_TIRE  7.4
#define D_TIRE  32.0

static float linear_x = 0.0;
static float angular_z = 0.0;
static float vel_ref_r = 0.0;
static float vel_ref_l = 0.0;

void receive_serial(){
  if(Serial.available() > 0){
    String receivedData = Serial.readStringUntil('\n');

    int commandIndex = receivedData.indexOf(',');

    if(commandIndex != -1){
      String linear_x_str = receivedData.substring(0, commandIndex);
      String angular_z_str = receivedData.substring(commandIndex + 1);

      linear_x = linear_x_str.toFloat();
      angular_z = angular_z_str.toFloat();

      Serial.print("x:");
      Serial.print(linear_x);
      Serial.print(" z:");
      Serial.println(angular_z);
    }
  }
}

void cal_wheel_vel(){
  float wh_rad = R_TIRE / 100.0;
  float wh_sep = D_TIRE / 100.0;

  receive_serial();
  
  vel_ref_r = (linear_x/wh_rad) + ((angular_z*wh_sep)/(2.0*wh_rad));
  vel_ref_l = (linear_x/wh_rad) - ((angular_z*wh_sep)/(2.0*wh_rad));
  Serial.print("r:");
  Serial.print(vel_ref_r);
  Serial.print(" l:");
  Serial.println(vel_ref_l);
}
