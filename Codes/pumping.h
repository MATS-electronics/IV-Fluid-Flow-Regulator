#include <Unistep2.h>
#include "button.h"

long const T = 3600*1000;
long initial_t;
long current_t;
int steps;
  
void pump_setup{
  // steps per 25ml obtained in callibration mode
  unistep2 motor(8, 9, 10, 11, 4096, 900); // pins for IN1, IN2, IN3, IN4, steps per rev, step delay(in micros)  
}

void motor_run(int n, int rate){
  
  // n - no of hours(set in Duration) 
  // rate/25ml( set in rate)
  
  initial_t = millis();
  
  while true{
    
    motor.run();
    current_t = millis();
    
    if ((current_t >= initial + T) && (n > 0)){
      motor.move( steps*rate);
      initial_t = current_t;
      n--;
    }
    
    //when stop pressed 
    if //(replace with condition to detect pressed stop)
    {
      motor.stop();
      return;
    }
    
    //when press pause
    if is_button_pressed(start_b){
      int temp_steps = motor.stepsToGo();
      motor.stop();
      
      while (true){
        
        if is_button_pressed(start_b){
          motor.move(temp_steps);
          initial_t = current_t;
          break;
        }

        if is_button_pressed(stop_b){
        {
          return;
        }
      } 
    }

    // when press stop
      if (is_button_pressed(stop_b)){
         motor.stop();
          return;
    }
  }
}
}
