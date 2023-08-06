// if one file is using coppy this part before setup 
int start_b = 12; // start/Pause button
int stop_b = 13 ; // stop button
long btn_timer = millis();
int state = 0;
/////////////////////////////////////////////////////////////////

// copy inside setup
void btn_setup(){
  pinMode(start_b,INPUT);
  pinMode(stop_b,INPUT);
}

//declayer every function before setup and define after loop

bool is_button_pressed(int button){
  
  if (millis()- btn_timer >= 250){
    state = ~digitalRead(button);
    if (state == 1){
      btn_timer = millis();
    }
  }
  
  return state;   
}
