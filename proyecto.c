/* 
  ActivityBot Calibrate.c

  Calibrate the ActivityBot's servos and encoders

  http://learn.parallax.com/activitybot/calibrate-your-activitybot
*/

#include "simpletools.h"
#include "abcalibrate.h"
#include "abdrive.h"
#include "ping.h" 
int *core1;
int *core2;
void sens();
void driving();
volatile int cmDist;    

int main(){
  simpleterm_close();
  core1 = cog_run(sens, 200);
  core2 = cog_run(driving, 200);   
  
}
void sens(){
  while(1){
    cmDist = ping_cm(9);                 // Get cm distance from Ping))) 
    pause(50); 
  }    
}
void driving(){
  drive_trimSet(0, 0, 0);
  while(1){
    simpleterm_open();                        // Open SimpleIDE Terminal for this core
    print("cmDist = %d\n", cmDist);
    simpleterm_close(); 
    
    if(cmDist>20){
      drive_speed(50, 50);

    }else{  
      drive_goto(64, -64);
      while(cmDist < 20);
    }       
  }     
}    
