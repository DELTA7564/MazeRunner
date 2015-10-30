#include "simpletools.h"                      // Include simple tools
#include "ping.h"
#include "abdrive.h" 

#define trig1 1
#define echo1 2
#define pingS 10
#define trig2 11
#define echo2 12

/***************************************
*STACK
*Se encarga de almacenar las direcciones
****************************************/
#define STACK_MAX 100              //tamano del stack
struct Stack {
    int     data[STACK_MAX];
    int     size;
};
typedef struct Stack STACK;
STACK pila;

/***************************************
*DECLARACION DE VARIABLES
*variables, definiciones y funciones globales
****************************************/ 
#define trig1 1
#define echo1 2
#define trig2 4
#define echo2 5
#define pingS 10

void push(int);
int ping4pin_cm(trig, echo);
int pop(void);
int cond = 1;
int izquierda = 2;
int derecha = 3; 

/***************************************
*MAIN
*Aqui inicia el codigo del programa
****************************************/ 
int main(){
  while(1){
    int cmFrom = ping_cm(10);                 // Get cm distance from Ping)))
    int cmRight = ping4pin_cm(trig1, echo1);
    int cmLeft = ping4pin_cm(trig2, echo2);
    print("cmFront = %d\n", cmFrom);           // Display distance
    print("cmRight = %d\n", cmRight);
    print("cmLeft = %d\n", cmLeft);
    
    if(cmFrom<10 && cmLeft<10 && cmRight<10){ //DEAD END
      print("DEAD END");
      drive_goto(26, -25);
      pause(200);
      drive_goto(26, -25);
      pause(200);
      drive_goto(10, 10);
      pause(200);
      push(cond);
    }
    if(cmFrom<10 && cmLeft<10 && cmRight>10){ //ESQUINA DERECHA
      print("esquina derecha");
      drive_goto(20, 20);
      pause(200);
      drive_goto(26, -25);
      pause(200);
      drive_goto(30, 30);
      pause(200);
    }
    if(cmFrom<10 && cmLeft>10 && cmRight<10){ //ESQUINA IZQUIERDA
      print("esquina izquierda");
      drive_goto(20, 20);
      pause(200);
      drive_goto(-25, 26);
      pause(200);
      drive_goto(30, 30);
      pause(200);
    }
    if(cmFrom<10 && cmLeft>10 && cmRight>10){ //INTERSECCION T
      print("interseccion T");
      int AI = pop();
      if(AI==1){
        
        drive_goto(20, 20);
        pause(200);
        drive_goto(26, -25);
        pause(200);
        drive_goto(30, 30);
        pause(200);
      }
      else{
        drive_goto(20, 20);
        pause(200);
        drive_goto(-25, 26);
        pause(200);
        drive_goto(30, 30);
        pause(200);
      }               
    }
    if(cmFrom>10 && cmLeft<10 && cmRight>10){ //RIGHT-FORWARD
      print("right forward");
      int AI = pop();
      if(AI==1){
        drive_goto(10, 10);
        pause(200);
      }
      else{
        drive_goto(20, 20);
        pause(200);
        drive_goto(26, -25);
        pause(200);
        drive_goto(30, 30);
        pause(200);
      }
    }
    if(cmFrom>10 && cmLeft>10 && cmRight<10){ //LEFT-FORWARD
      print("left forrrrward");
      int AI = pop();
      if(AI==1){
        drive_goto(20, 20);
        pause(200);
        drive_goto(-25, 26);
        pause(200);
        drive_goto(30, 30);
        pause(200);
      }
      else{
        drive_goto(10, 10);
        pause(200);
      }
    }
    if(cmFrom>10 && cmLeft<10 && cmRight<10){ //FORWARD
      print("forward");
      drive_goto(10, 10);
      pause(200);
    }
    if(cmFrom>10 && cmLeft>10 && cmRight>10){ //even tho i walk through the valley of death, i shall fear no evil   
      print("void");
      drive_goto(15, 15);
      pause(200);
    }    
    pause(500);
  }    
}  




int ping4pin_cm(int trig, int echo)//trig is trigger pin, echo is echo pin
{
  int dist = 0;
  float i = 0;
  low(trig);//set trig low for start pulse
  low(echo);//set echo low to be safe
  pulse_out(trig, 10);//send the minimum 10 ms pulse on trig to start a ping
  i = pulse_in(echo, 1);
  dist = i/58;//get the pulse durat on back on echo pin
  return dist;
}

void push (int num) {
    if (pila.size == (STACK_MAX - 1)) {
        printf ("Stack is Full\n");
        return;
    }
    else {
        //printf ("Enter the element to be pushed\n");
        //scanf ("%d", &num);
        pila.size = pila.size + 1;
        pila.data[pila.size] = num;
        printf("%d guardado\n",num);
    }
    return;
}

//regresa un valor del stack
int pop (){
    int num;
    if (pila.size == - 1) {
        printf ("Stack is Empty\n");
        return (-1);
    }
    else {
        num = pila.data[pila.size];
        printf ("poped element is = %d\n", num);
        pila.size = pila.size - 1;
    }
    return(num);
}