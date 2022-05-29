//============================智宇科技===========================、
/*前进  按下发出 ONA  松开ONF
  后退：按下发出 ONB  松开ONF
  左转：按下发出 ONC  松开ONF
  右转：按下发出 OND  松开ONF
  停止：按下发出 ONE  松开ONF
  
  蓝牙程序功能是按下对应的按键执行操，松开按键就停止
*/
//#include <SoftwareSerial.h>
int Left_arm_go=11; //左手臂电机 前进
int Left_arm_back=10; //左手臂电机 后退
int Left_leg_go=3; // 左腿电机 前进
int Left_leg_back=2; // 左腿电机 后退
int Left_forearm_go=9; // 左小臂电机 前进
int Left_forearm_back=8; // 左小臂电机 后退
int Left_arm_stop=A1;//若等于5v需要电机翻转
int Right_arm_go=13; //右手臂电机 前进
int Right_arm_back=12; //右手臂电机 后退
int Right_leg_go=5; // 右腿电机 前进
int Right_leg_back=4; // 右腿电机 后退
int Right_forearm_go=7; // 右小臂电机 前进
int Right_forearm_back=6; // 右小臂电机 后退
int Right_arm_stop=A0;//若等于5v需要电机反转

int trigger_left=0;
int trigger_right=0;
int trigger_left_pre=0;
int trigger_right_pre=0;
char getstr;
int DC=180;
int add_left=0;
int add_right=0;
int nosignalCount;
uint8_t RS232_RC=0;

void setup() {
  //初始化电机驱动IO为输出方式
  Serial.begin(9600);
  pinMode(Left_arm_go, OUTPUT); // 11 PWM
  pinMode(Left_arm_back, OUTPUT); //10 PWM
  pinMode(Left_leg_go, OUTPUT); // 3 pwm
  pinMode(Left_leg_back, OUTPUT); // 2 no pwm
  pinMode(Left_forearm_go, OUTPUT);//9 PWM
  pinMode(Left_forearm_back, OUTPUT); //8 no pwm
  pinMode(Left_arm_stop, INPUT); //A1
  pinMode(Right_arm_go, OUTPUT); // 13 pwm
  pinMode(Right_arm_back, OUTPUT); // 12 pwm
  pinMode(Right_leg_go, OUTPUT); //5 no pwm
  pinMode(Right_leg_back, OUTPUT); //4 no pwm
  pinMode(Right_forearm_go, OUTPUT); //7 no pwm
  pinMode(Right_forearm_back, OUTPUT); //6 pwm
  pinMode(Right_arm_stop, INPUT); //A0

  Serial.println("gogogo!");
}

void run(int time) {

  digitalWrite(Left_leg_go, HIGH); // 右电机前进
  digitalWrite(Left_leg_back, LOW);
  // analogWrite(Right_leg_go, DC+add_right); //PWM比例0~255调速，左右轮差异略增减
  // analogWrite(Right_leg_back, 0);
  digitalWrite(Right_leg_go, HIGH); // 左电机前进
  digitalWrite(Right_leg_back, LOW);
  // analogWrite(Left_leg_go, 0); //PWM比例0~255调速，左右轮差异略增减
  // analogWrite(Left_leg_back, DC+add_left);
  delay(time * 100);   //执行时间，可以调整  
}

void brake() //刹车，停车

  {
  digitalWrite(Left_leg_go, LOW);
  digitalWrite(Left_leg_back, LOW);
  digitalWrite(Right_leg_go, LOW);
  digitalWrite(Right_leg_back, LOW);

}

void left(int time) {
  digitalWrite(Right_leg_go, HIGH); // 右电机前进
  digitalWrite(Right_leg_back, LOW);
  // analogWrite(Right_leg_go, DC);
  // analogWrite(Right_leg_back, 0); //PWM比例0~255调速
  digitalWrite(Left_leg_go, LOW); //左轮后退
  digitalWrite(Left_leg_back, LOW);
  // analogWrite(Left_leg_go, 0);
  // analogWrite(Left_leg_back, 0); //PWM比例0~255调速
  delay(time * 100);  //执行时间，可以调整  
}

void spin_left(int time) //左转(左轮后退，右轮前进)

  {
  digitalWrite(Right_leg_go, HIGH); // 右电机前进
  digitalWrite(Right_leg_back, LOW);
  // analogWrite(Right_leg_go, DC);
  // analogWrite(Right_leg_back, 0); //PWM比例0~255调速
  digitalWrite(Left_leg_go, LOW); //左轮后退
  digitalWrite(Left_leg_back, HIGH);
  // analogWrite(Left_leg_go, DC);
  // analogWrite(Left_leg_back, 0); //PWM比例0~255调速
  delay(time * 100);  //执行时间，可以调整  
}

void right(int time) {
  digitalWrite(Right_leg_go, LOW); //右电机后退
  digitalWrite(Right_leg_back, LOW);
  // analogWrite(Right_leg_go, 0);
  // analogWrite(Right_leg_back, 0); //PWM比例0~255调速
  digitalWrite(Left_leg_go, LOW); //左电机前进
  digitalWrite(Left_leg_back, HIGH);
  // analogWrite(Left_leg_go, 0);
  // analogWrite(Left_leg_back, DC); //PWM比例0~255调速
  delay(time * 100);  //执行时间，可以调整  
}

void spin_right(int time) //右转(右轮后退，左轮前进)

  {
  digitalWrite(Right_leg_go, LOW); //右电机后退
  digitalWrite(Right_leg_back, HIGH);
  // analogWrite(Right_leg_go, 0);
  // analogWrite(Right_leg_back, DC); //PWM比例0~255调速
  digitalWrite(Left_leg_go, HIGH); //左电机前进
  digitalWrite(Left_leg_back, LOW);
  // analogWrite(Left_leg_go, 0);
  // analogWrite(Left_leg_back, DC); //PWM比例0~255调速
  delay(time * 100);  //执行时间，可以调整    
}

void back(int time) {
  digitalWrite(Right_leg_go, LOW); //右轮后退
  digitalWrite(Right_leg_back, HIGH);
//  analogWrite(Right_leg_go, 0);
//  analogWrite(Right_leg_back, DC+add_right); //PWM比例0~255调速
  digitalWrite(Left_leg_go, LOW); //左轮后退
  digitalWrite(Left_leg_back, HIGH);
//  analogWrite(Left_leg_go, 0);
//  analogWrite(Left_leg_back, DC+add_left); //PWM比例0~255调速
  delay(time * 100);     //执行时间，可以调整  
}
//大臂控制
void left_arm_go(int time){
  digitalWrite(Left_arm_go, HIGH);
  digitalWrite(Left_arm_back, LOW);
  delay(time * 100);     //执行时间，可以调整  

}
void left_arm_back(int time){
  digitalWrite(Left_arm_go, LOW);
  digitalWrite(Left_arm_back, HIGH);
  delay(time * 100);     //执行时间，可以调整  
}
void left_arm_break(){
  digitalWrite(Left_arm_go, LOW);
  digitalWrite(Left_arm_back, LOW);
}
void right_arm_go(int time){
  digitalWrite(Right_arm_go, HIGH);
  digitalWrite(Right_arm_back, LOW);
  delay(time * 100);     //执行时间，可以调整  
}
void right_arm_back(int time){
  digitalWrite(Right_arm_go, LOW);
  digitalWrite(Right_arm_back, HIGH);
  delay(time * 100);     //执行时间，可以调整  
}
void right_arm_break(){
  digitalWrite(Right_arm_go, LOW);
  digitalWrite(Right_arm_back, LOW);
}
//小臂控制
void left_forearm_go(int time){
  digitalWrite(Left_forearm_go, HIGH);
  digitalWrite(Left_forearm_back, LOW);
  delay(time * 100);     //执行时间，可以调整  

}
void left_forearm_back(int time){
  digitalWrite(Left_forearm_go, LOW);
  digitalWrite(Left_forearm_back, HIGH);
  delay(time * 100);     //执行时间，可以调整  
}
void left_forearm_break(){
  digitalWrite(Left_forearm_go, LOW);
  digitalWrite(Left_forearm_back, LOW);
}
void right_forearm_go(int time){
  digitalWrite(Right_forearm_go, HIGH);
  digitalWrite(Right_forearm_back, LOW);
  delay(time * 100);     //执行时间，可以调整  
}
void right_forearm_back(int time){
  digitalWrite(Right_forearm_go, LOW);
  digitalWrite(Right_forearm_back, HIGH);
  delay(time * 100);     //执行时间，可以调整  
}
void right_forearm_break(){
  digitalWrite(Right_forearm_go, LOW);
  digitalWrite(Right_forearm_back, LOW);
}

void loop() {
// 机械止点的信号
  trigger_left_pre=trigger_left;
  trigger_right_pre=trigger_right;
  trigger_left=analogRead(Left_arm_stop);
  trigger_right=analogRead(Right_arm_stop);

  if ((trigger_left>800)&&(trigger_left_pre<800)){
    Serial.println("trigger_left>800");
    Serial.println(trigger_left);

  }
  else if((trigger_left<100)&&(trigger_left_pre>100)){
    Serial.println("trigger_left<100");
    Serial.println(trigger_left);

  }
  if ((trigger_right>800)&&(trigger_right_pre<800)){
    Serial.println("trigger_right>800");
    Serial.println(trigger_right);

  }
  else if((trigger_right<100)&&(trigger_right_pre>100)){
    Serial.println("right and pre");
    Serial.println(trigger_right);
    Serial.println(trigger_right_pre);
  }

  getstr=Serial.read(); 
//forward
  if(getstr=='A') {
    Serial.println("go forward!");
    run(1);
  }
//back
  else if(getstr=='B') {
    Serial.println("go back!");
    back(1);
  }
//left
  else if(getstr=='C') {
    Serial.println("go left!");
    left(1);
  }
//right
  else if(getstr=='D') {
    Serial.println("go right!");
    right(1);

  }
//stop
  else if(getstr=='F') {
    Serial.println("Stop!");
    brake();

  }
//stop
  else if(getstr=='E') {
    Serial.println("Stop!");
    brake();
  }
//左手正转
  else if(getstr=='1') {
    left_arm_go(1);
    Serial.println("left_arm_go");
  }
//左手反转
  else if(getstr=='2') {
    left_arm_back(1);
    Serial.println("left_arm_back");
  }
//左手小臂正转
  else if(getstr=='3') {
    left_forearm_go(1);
    Serial.println("left_forearm_go");
  }
//左手小臂反转
  else if(getstr=='4') {
    left_forearm_back(1);
    Serial.println("left_forearm_back");
  }
//右手正转
  else if(getstr=='5') {
    right_arm_go(1);
    Serial.println("right_arm_go");
  }
//right_arm_back
  else if(getstr=='6') {
    right_arm_back(1);
    Serial.println("right_arm_back");
  }
//right_forearm_go
  else if(getstr=='7') {
    right_forearm_go(1);
    Serial.println("right_forearm_go");  
    }
//right_forearm_back
  else if(getstr=='8') {
    right_forearm_back(1);
    Serial.println("right_forearm_back"); 
    }
//forward
  else if(getstr=='b') {
    Serial.println("go forward!");
    run(1);
    nosignalCount=0;
    brake();
  }
//go left!
  else if(getstr=='c') {
    Serial.println("go left!");
    left(1);
    nosignalCount=0;
    brake();
  }
//go right!
    else if(getstr=='d') {
    Serial.println("go right!");
    right(1);
    brake();
  }
    else if(getstr=='e') {
    Serial.println("go left!");
    left(1);
    brake();
  }
    else if(getstr=='f') {
    Serial.println("go right!");
    right(1);
    brake();
  }
//沒有報文
    else
    { 
      RS232_RC=RS232_RC+1;
      nosignalCount=nosignalCount+1;
      if (nosignalCount>1000000)
      {
        spin_right(1);
        Serial.println("spin_right!");
        nosignalCount=0;
        brake();
      }
      if (RS232_RC==254){
     
      //没收到指令 小臂 大臂 就停止运动
      right_forearm_break();
      right_arm_break();
      left_forearm_break();
      left_arm_break();
      }

    }
    
}