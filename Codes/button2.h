int start_b = 12; // start/Pause button
int stop_b = 13 ; // stop button
long btn_timer = millis();
int state = 1;

void btn_setup(){
  pinMode(start_b,INPUT);
  pinMode(stop_b,INPUT);
}

bool is_button_pressed(int button){
  state = digitalRead(button);
  if ((state == 0) && (millis()> (btn_timer + 250))){
    btn_timer = millis();
    return true;
  }
  else { 
    return false;
  }
}
