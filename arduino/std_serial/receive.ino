void receive_serial(){
  if(Serial.available() > 0){
    String receivedData = Serial.readStringUntil('\n');

    float linear_x, angular_z;
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
