
int u = 0; // переменная для числа пребразования 0-1023
float u_in = 0.0; // переменная для напряжения 0.0-5.0

void setup() {
Serial.begin(9600);
  pinMode(A0,INPUT);// A0 - аналоговый вход
}

void loop() {
  Serial.print("U = ");
  u = analogRead(A0); // измерение 
  u_in = (u * 4.77) / 1023; // пересчет измерения в вольты
    Serial.println(u_in);


  delay(500);
}
