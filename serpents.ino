/*
****************************************************************************************************************
      _______     ______   _______      _______    ________     __          ________    _______
    /______    /______    /______/    /_______/   /_______    /   |    /       /      /_______
   ______/   /_______   /       |    /          /________   /     |___/       /       _______/
   
****************************************************************************************************************

A TEST OF THE MAX7219

*/

#include "LedControl.h" //  need the library
LedControl lc=LedControl(12,11,10,1); // 



// pin 12 is connected to the MAX7219 pin 1
// pin 11 is connected to the CLK pin 13
// pin 10 is connected to LOAD pin 12
// 1 as we are only using 1 MAX7219

int screen[][8] = {{0,0,0,0,0,0,0,0},
                   {0,0,0,0,0,0,0,0},
                   {0,0,0,0,0,0,0,0},
                   {0,0,0,0,0,0,0,0},
                   {0,0,0,0,0,0,0,0},
                   {0,0,0,0,0,0,0,0},
                   {0,0,0,0,0,0,0,0},
                   {0,0,0,0,0,0,0,0}};
                   
int previous_x[64] = {0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0};

int previous_y[64] = {0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0};

int tail_length = 0;

int state = 0;

int ball_x = 5;
int ball_y = 5;

int egg_x = 6;
int egg_y = 6;

void setup()
{
  // the zero refers to the MAX7219 number, it is zero for 1 chip
  lc.shutdown(0,false);// turn off power saving, enables display
  lc.setIntensity(0,15);// sets brightness (0~15 possible values)
  lc.clearDisplay(0);// clear screen

  egg_x = int(random(7));
  egg_y = int(random(7));

  pinMode(7,INPUT); 
  pinMode(8,INPUT); 
  pinMode(9,INPUT); 
  pinMode(10,INPUT);  
}

void loop(){
  readinput();
  readstate(); 
  render_screen();
  }

 void readinput(){
  if(digitalRead(7)==true){state = 0;}
  else if (digitalRead(8)==true){state = 1;}
  else if (digitalRead(9)==true){state = 2;}
  else if (digitalRead(10)==true){state = 3;}
  }

void readstate(){
    if (state == 0){move_down();}
    else if (state ==1){move_up();}
    else if (state ==2){move_left();}
    else if (state ==3){move_right();}
    else {return;}
}

void move_down(){if (ball_y==7){
            update_tail_array(ball_x,ball_y);
            ball_y=0;
            collision_detect();}
            else{  
            update_tail_array(ball_x,ball_y);
            ball_y+=1;
            collision_detect();}
          }

void move_up(){ if (ball_y==0){
            update_tail_array(ball_x,ball_y);
            ball_y=7;
            collision_detect();}
            else{
            update_tail_array(ball_x,ball_y);
            ball_y-=1;
            collision_detect();}
          }

void move_left(){ if (ball_x==0){
            update_tail_array(ball_x,ball_y);
            ball_x=7;
            collision_detect();}
            else
            {update_tail_array(ball_x,ball_y);
            ball_x-=1;
            collision_detect();}}

void move_right(){  if (ball_x==7){
            update_tail_array(ball_x,ball_y);
            ball_x=0;collision_detect();}
            else
            {update_tail_array(ball_x,ball_y);
            ball_x+=1;collision_detect();}}


void render_screen(){
  drawbackground(); 
  drawegg(); 
  drawball(); 
  draw_tail(); 
  drawscreen();
}

void drawbackground(){
  for (int i=0; i<8; i++){
    for (int j=0; j<8; j++){
      screen[i][j]=false;   
    }
  }
}

void drawegg(){
    screen[egg_x][egg_y]= true; 
}

void drawball(){
    screen[ball_x][ball_y]= true;
  }

  void update_tail_array(int ballx,int bally){
  
  int temp_previous_x[64] = {0,0,0,0,};
  
  int temp_previous_y[64] = {};
  
  for (int i=0; i<64; i++){
    temp_previous_x[i]=previous_x[i];
    temp_previous_y[i]=previous_y[i];
  }
  
  previous_x[0]=ballx;
  previous_y[0]=bally;
  
  for (int i=0; i<63; i++){
    previous_x[i+1]=temp_previous_x[i];
    previous_y[i+1]=temp_previous_y[i];
  }
  
}
  void collision_detect(){
  for (int i=0; i<tail_length+1; i++){
    if(ball_x==previous_x[i] && ball_y==previous_y[i]){restart();}
   }
  }

void restart(){
for (int i=0; i<63; i++){
    previous_x[i]=0;
    previous_y[i]=0;
}
    egg_x = int(random(7));
    egg_y = int(random(7));;
    tail_length=0;
    ball_x=int(random(7));
    ball_y=int(random(7));
}
  
void respawn_egg(){
for (int i=0; i<tail_length+1; i++){
    if(egg_x==previous_x[i] && egg_y==previous_y[i]){
      respawn_egg();
      }
      else{      
      egg_x = int(random(7));
      egg_y = int(random(7));
      }
   }
}

void draw_tail(){
  for (int i=0; i<tail_length; i++){
    screen[previous_x[i]][previous_y[i]]= true;
 }
}

void drawscreen()
{
  for (int row=0; row<8; row++)
  {
    for (int col=0; col<8; col++)
    {
      if(screen[col][row]==true){
      lc.setLed(0,col,row,true);}
      else{
      lc.setLed(0,col,row,false);
      }
      }
    }
  }
