
int u = 0; // переменная для числа пребразования 0-1023
float u_in = 0.0; // переменная для напряжения
int load = 10;

void setup() {
  Serial.begin(9600);
  analogReference(INTERNAL);/* используем внутренний источник опорного 
   напряжения 1.1 В, максимальное входное напрядение на А0 не должно превышать
   напряжение внутреннего ИОН */
  pinMode(A0,INPUT);// A0 - аналоговый вход
  pinMode(load,OUTPUT);// 10 - вЫход для включения транзистора 
}

void loop() {
  Serial.print("U = ");
  u = analogRead(A0); // измерение по входу А0
  u_in = (u * 4.00) / 1023; // пересчет измерения в вольты (на Uвх = 5 В)
  Serial.println(u_in);
  digitalWrite(load, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(3000);                       // wait for a second
  digitalWrite(load, LOW);    // turn the LED off by making the voltage LOW
  delay(500);
}
