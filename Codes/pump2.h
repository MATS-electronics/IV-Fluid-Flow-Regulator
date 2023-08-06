#include <Stepper.h>


long const T = 3600*1000;
long initial_t;
long current_t;
int steps_per_ml; // steps per 1ml obtained in callibration mode
  
void pump_setup(){

  Stepper motor(200,8, 9, 10, 11); // steps per rev, pins for IN1, IN2, IN3, IN4, 
  motor.setSpeed(60); 
}

void motor_run(int n, int rate){  
  
  initial_t = millis();
  double stp_count = steps_per_ml*rate;
  bool motor_running = true; 
  
  while true{
    
    current_t = millis();

    if (motor_running){
      motor.step(10);
      stp_count =- 10;
      level_sensor();
    }

    if ((current_t >= initial + T) && (n > 0)){
      motor_running = true;
      initial_t = current_t;
      n--;
    }
    

    //when press pause
    if (digitalRead(start_b) == 0){
      int temp_steps = motor.stepsToGo();
      motor_running = false;
      
      while (true){
        
        if (digitalRead(start_b) == 0){
          motor_running = true;
          initial_t = current_t;
          break;
        }

        if (digitalRead(stop_b) == 0){
        
          return;
        }
      } 
    }

    // when press stop
      if (digitalRead(stop_b) == 0){
         motor_running = false;
          return;
    }
  }
}

