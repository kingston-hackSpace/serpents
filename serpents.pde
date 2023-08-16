boolean screen[][] = new boolean[8][8];

int[] previous_x = new int[64];
int[] previous_y = new int[64];

int tail_length = 0;

int ball_x = 5;
int ball_y = 5;

int egg_x = 6;
int egg_y = 6;

int state = 0;

void setup(){
size(100,100);
//screen[4][5]=true;

egg_x = int(random(7));
egg_y = int(random(7));

}

void draw(){

readeggstate();
readstate();  
delay(300);
renderscreen();

}

void keyPressed() {
  if (key == CODED) {
      if (keyCode == DOWN) {
        state = 0;
    }   else if (keyCode == UP) {
        state = 1;
    } 
        else if (keyCode == LEFT) {
        state = 2;
    } 
        else if (keyCode == RIGHT) {
        state = 3;
    } 
  } else {
    return;
  }
}

void readeggstate(){
  if (egg_x==ball_x && egg_y==ball_y){
      respawn_egg();
      tail_length+=1;
  }
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

void renderscreen(){
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

void drawscreen(){
  for (int i=0; i<8; i++){
    for (int j=0; j<8; j++){
      if (screen[i][j]==true){
        fill(0,256,0);
        rect((i*10),j*10,8,8);
      }else{
        fill(256,256,0);
        rect((i*10),j*10,8,8);}
    }
  }
}

void update_tail_array(int ballx,int bally){
  
  int[] temp_previous_x = new int[64];
  int[] temp_previous_y = new int[64];
  
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
