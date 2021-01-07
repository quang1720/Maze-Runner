

#define ENA 10 
#define ENB 11 
#define in1 2
#define in2 3
#define in3 4
#define in4 5
const int trigL = A0;     // chân trig của HC-SR04 trái
const int echoL = A1;     // chân echo của HC-SR04 trái
const int trigC = A5;     // chân trig của HC-SR04 giữa
const int echoC = A4;     // chân echo của HC-SR04 giữa
float cambientrai;
float cambientruoc; 
//float cambienphai;
float XungENB=0,XungENA=0;
float hamdoccambien(int trig, int echo)
{
  unsigned long a;
  float d;
  digitalWrite(trig, 0);
  delayMicroseconds(2);
  digitalWrite(trig, 1);
  delayMicroseconds(5);
  digitalWrite(trig, 0);
  a = pulseIn(echo, 1);
  d = a / 2 / 29.412;
  return d;
}
void doccambien()
{
  cambientrai = hamdoccambien(trigL, echoL);
  cambientruoc = hamdoccambien(trigC, echoC);
  //cambienphai=analogRead(A2);
  Serial.print("\n Trai : "); //70
  Serial.print(cambientrai);
//  Serial.print("\n Truoc "); //50
//  Serial.print(cambientruoc);
  //    Serial.print(" Phai "); //40
  //    Serial.println(cambienphai);
}
//============Thiết kế cho xe quẹo trái==========

void QueoPhai() // cho bám trái
{

  analogWrite(ENB, 100); //110   // giá trị đo thực tế
  analogWrite(ENA, 100);
  delay(100);
  while (cambientruoc < 15)
  {
    rephai();
    doccambien();
    delay(100);
  }
}
void rephai()
{
  digitalWrite(in1, LOW); // Left wheel forward
  digitalWrite(in2, HIGH);
  digitalWrite(in4, HIGH); // Right wheel forward
  digitalWrite(in3, LOW);
}
void nghichphai()
{
  digitalWrite(in2, LOW);
  digitalWrite(in1, HIGH);
}
void thuanphai()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
}
void nghichtrai()
{
  digitalWrite(in4, LOW);
  digitalWrite(in3, HIGH);
}
void thuantrai()
{
  digitalWrite(in4, LOW);
  digitalWrite(in3, HIGH);
}
//void BamPhai() // bám phải trái cộng, phải trừ
//{ float Kp = 25 , Kd = 1.2, Ki = 0.05; // Kp = 9.5, Kd = 1.2, Ki = 0;
//  float P, I, D;
//  static int lasterror;
//  int out;
//  float SamplingTime = 0.01;
//  int error = 750 - cambienphai;
//  thuantrai(); thuanphai();
//  P = error * Kp;
//  I += Ki * error * SamplingTime;
//  D = (Kd * (error - lasterror )) / SamplingTime;
//  out = P + I + D;
//  lasterror = error;
//  XungENB = 60 - out/100; //XungENB = 50 - out;
//  XungENA = 60 + out/100; //XungENA = 50 + out;
//  if (XungENB > 255) XungENB = 255;
//  else if (XungENB < 0) XungENB = 0;
//  if (XungENA > 255) XungENA = 255;
//  else if (XungENA < 0) XungENA = 0;
//  analogWrite(ENB, XungENB );//100
//  analogWrite(ENA, XungENA);//100
//}
void BamTrai() // bám trái là trái trừ, phải cộng (XungENB,XungENA)
{
  float Kp = 0.05, Kd = 2, Ki = 0.05; //float Kp = 15 , Kd =7 , Ki = 0.1;
  float P, I, D;
  float lasterror;
  int out;
  float SamplingTime = 0.01;//0.05
  float error = 10 - cambientrai;//13-cambientrai
  thuantrai();
  thuanphai();
  P = error * Kp;
  I = Ki * error * SamplingTime;
  D = (Kd * (error - lasterror)) / SamplingTime;
  out = P + I + D;
  lasterror = error;
  XungENB = 80 - out; // XungENA = 50 - out;
  XungENA = 80 + out; // XungENB = 50 + out;
  
  if (cambientrai > 800)
  {
    XungENA = 200;
    XungENB = 0;
  }
  else
  {
    if (XungENB > 255)
      XungENB = 225;
    else if (XungENB < 0)
      XungENB = 70;

    if (XungENA > 255)
      XungENA = 225;
    else if (XungENA < 0)
      XungENA = 45;
  }

//  Serial.print("\nXungphai: ");
//  Serial.print(XungENA);
//  Serial.print("                        Xungtrai= ");
//  Serial.print(XungENB);
//  Serial.print("\n");
  analogWrite(ENB, XungENB); //100
  analogWrite(ENA, XungENA); //100
}
void setup()
{
  Serial.begin(9600);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(trigL, OUTPUT);
  pinMode(echoL, INPUT);
  pinMode(trigC, OUTPUT);
  pinMode(echoC, INPUT);
}
void loop()
{
  BamTrai();
  doccambien();
  if (cambientruoc < 15)
    QueoPhai();
}
