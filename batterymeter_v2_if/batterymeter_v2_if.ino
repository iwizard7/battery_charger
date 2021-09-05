
int u = 0; // переменная для числа пребразования 0-1023
float u_in = 0.0; // переменная для напряжения
int load = 10; // пин для нагрузки
int led = 13; // светодиод индикации включения нагрузки
float Voff = 1.00; // напряжение выключения

void setup() {
  Serial.begin(9600);
  analogReference(INTERNAL);/* используем внутренний источник опорного 
   напряжения 1.1 В, максимальное входное напрядение на А0 не должно превышать
   напряжение внутреннего ИОН */
  pinMode(A0,INPUT);// A0 - аналоговый вход
  pinMode(load,OUTPUT);// 10 - вЫход для включения транзистора 
  pinMode(led,OUTPUT);// 13 - светодиод индикации
}

void loop() {
  Serial.print("Discharge ");
  Serial.print("U = ");
  u = analogRead(A0); // измерение по входу А0
  u_in = (u * 4.35) / 1023; // пересчет измерения в вольты (на Uвх = 5 В)
  Serial.println(u_in);
 


if (u_in < Voff)
{
Serial.println("Stop discharge!!!");
}
else
{
 digitalWrite(load, HIGH);   // turn the LED on (HIGH is the voltage level)
 digitalWrite(led, HIGH);   
  delay(10000);                       // wait for a 5 second
  digitalWrite(load, LOW);// turn the LED off by making the voltage LOW
  digitalWrite(led, LOW);
}

  delay(500);

  
}
