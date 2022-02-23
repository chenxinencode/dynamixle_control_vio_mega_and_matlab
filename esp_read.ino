void ESPwait(String stopstr,int timeout_secs)
{
  String response;
  bool found = false;
  char c;
  long timer_init;
  long timer;

  timer_init = millis();
  while (!found) {
    timer = millis();
    if (((timer - timer_init) / 1000) > timeout_secs) { // Timeout?
      Serial.println("!Timeout!");
      timer=0;  // timeout
    }
    if (Serial3.available()) {
      c = Serial3.read();
      response += c;
      if (response.endsWith(stopstr)) {
        found = true;
        delay(10);
        Serial3.flush();
      }
    } // end Serial1_available()
  } // end while (!found)

  if (DEBUG1==true)
  {
    
    String pos1=getValue(response, ',', 0);
    Serial.println(pos1);
    //Serial.println(response);  
  }
  
  else if(DEBUG2==true)
  {
    
    String dxl_pos_str7=getValue(response, ',', 6);
    float dxl_pos7=dxl_pos_str7.toFloat();
    dxl.setGoalPosition(DXL_ID7, dxl_pos7);
  }
  
}
