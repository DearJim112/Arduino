//============================智宇科技===========================、
/*前进  按下发出 ONA  松开ONF
  后退：按下发出 ONB  松开ONF
  左转：按下发出 ONC  松开ONF
  右转：按下发出 OND  松开ONF
  停止：按下发出 ONE  松开ONF
  
  蓝牙程序功能是按下对应的按键执行操，松开按键就停止
*/
//#include <SoftwareSerial.h>
char getstr;
int Left_motor_go=8; //左电机前进(IN1)
int Left_motor_back=9; //左电机后退(IN2)
int Right_motor_go=10; // 右电机前进(IN3)
int Right_motor_back=11; // 右电机后退(IN4)
int DC=70;
int add_left=0;
int add_right=0;

void setup() {
  //初始化电机驱动IO为输出方式
  Serial.begin(9600);
  pinMode(Left_motor_go, OUTPUT); // PIN 8 (无PWM)
  pinMode(Left_motor_back, OUTPUT); // PIN 9 (PWM)
  pinMode(Right_motor_go, OUTPUT); // PIN 10 (PWM) 
  pinMode(Right_motor_back, OUTPUT); // PIN 11 (PWM)
  Serial.println("gogogo!");
}

void run() {
  digitalWrite(Right_motor_go, HIGH); // 右电机前进
  digitalWrite(Right_motor_back, LOW);
  analogWrite(Right_motor_go, DC+add_right); //PWM比例0~255调速，左右轮差异略增减
  analogWrite(Right_motor_back, 0);
  digitalWrite(Left_motor_go, LOW); // 左电机前进
  digitalWrite(Left_motor_back, HIGH);
  analogWrite(Left_motor_go, 0); //PWM比例0~255调速，左右轮差异略增减
  analogWrite(Left_motor_back, DC+add_left);
  //delay(time * 100);   //执行时间，可以调整  
}

void brake() //刹车，停车

  {
  digitalWrite(Right_motor_go, LOW);
  digitalWrite(Right_motor_back, LOW);
  digitalWrite(Left_motor_go, LOW);
  digitalWrite(Left_motor_back, LOW);

}

void left() {
  digitalWrite(Right_motor_go, HIGH); // 右电机前进
  digitalWrite(Right_motor_back, LOW);
  analogWrite(Right_motor_go, DC);
  analogWrite(Right_motor_back, 0); //PWM比例0~255调速
  digitalWrite(Left_motor_go, LOW); //左轮后退
  digitalWrite(Left_motor_back, LOW);
  analogWrite(Left_motor_go, 0);
  analogWrite(Left_motor_back, 0); //PWM比例0~255调速
  //delay(time * 100);  //执行时间，可以调整  
}

void spin_left(int time) //左转(左轮后退，右轮前进)

  {
  digitalWrite(Right_motor_go, HIGH); // 右电机前进
  digitalWrite(Right_motor_back, LOW);
  analogWrite(Right_motor_go, DC);
  analogWrite(Right_motor_back, 0); //PWM比例0~255调速
  digitalWrite(Left_motor_go, HIGH); //左轮后退
  digitalWrite(Left_motor_back, LOW);
  analogWrite(Left_motor_go, DC);
  analogWrite(Left_motor_back, 0); //PWM比例0~255调速
  //delay(time * 100);  //执行时间，可以调整  
}

void right() {
  digitalWrite(Right_motor_go, LOW); //右电机后退
  digitalWrite(Right_motor_back, LOW);
  analogWrite(Right_motor_go, 0);
  analogWrite(Right_motor_back, 0); //PWM比例0~255调速
  digitalWrite(Left_motor_go, LOW); //左电机前进
  digitalWrite(Left_motor_back, HIGH);
  analogWrite(Left_motor_go, 0);
  analogWrite(Left_motor_back, DC); //PWM比例0~255调速
  //delay(time * 100);  //执行时间，可以调整  
}

void spin_right(int time) //右转(右轮后退，左轮前进)

  {
  digitalWrite(Right_motor_go, LOW); //右电机后退
  digitalWrite(Right_motor_back, HIGH);
  analogWrite(Right_motor_go, 0);
  analogWrite(Right_motor_back, DC); //PWM比例0~255调速
  digitalWrite(Left_motor_go, LOW); //左电机前进
  digitalWrite(Left_motor_back, HIGH);
  analogWrite(Left_motor_go, 0);
  analogWrite(Left_motor_back, DC); //PWM比例0~255调速
  //delay(time * 100);  //执行时间，可以调整    
}

void back() {
  digitalWrite(Right_motor_go, LOW); //右轮后退
  digitalWrite(Right_motor_back, HIGH);
//  analogWrite(Right_motor_go, 0);
//  analogWrite(Right_motor_back, DC+add_right); //PWM比例0~255调速
  digitalWrite(Left_motor_go, HIGH); //左轮后退
  digitalWrite(Left_motor_back, LOW);
//  analogWrite(Left_motor_go, 0);
//  analogWrite(Left_motor_back, DC+add_left); //PWM比例0~255调速
  //delay(time * 100);     //执行时间，可以调整  
}

void loop() {


  getstr=Serial.read(); // 

  if(getstr=='A') {
    Serial.println("go forward!");
    run();
  }

  else if(getstr=='B') {
    Serial.println("go back!");
    back();
  }

  else if(getstr=='C') {
    Serial.println("go left!");
    left();
  }

  else if(getstr=='D') {
    Serial.println("go right!");
    right();

  }

  else if(getstr=='F') {
    Serial.println("Stop!");
    brake();

  }

  else if(getstr=='E') {
    Serial.println("Stop!");
    brake();
  }

  else if(getstr=='2') {
    DC=60;
    add_left=0;
    add_right=0;
    Serial.println("DC=60");
    brake();
  }

  else if(getstr=='5') {
    DC=120;
    add_left=0;
    add_right=0;
    Serial.println("DC=120");
    brake();
  }

  else if(getstr=='8') {
    DC=180;
    add_left=0;
    add_right=0;
    Serial.println("DC=180");
    brake();
  }

  else if(getstr=='1') {
    add_left=3;
    Serial.println(add_left);
    brake();
  }

  else if(getstr=='4') {
    add_left=7;
    Serial.println(add_left);
    brake();
  }

  else if(getstr=='7') {
    add_left=15;
    Serial.println(add_left);
    brake();
  }

  else if(getstr=='3') {
    add_right=3;
    Serial.println(add_right);
    brake();
  }

  else if(getstr=='6') {
    add_right=7;
    Serial.println(add_right);
    brake();
  }

  else if(getstr=='9') {
    add_right=15;
    Serial.println(add_right);
    brake();
  }

}
