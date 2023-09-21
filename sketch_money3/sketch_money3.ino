//инициализируем переменные
int coin1 = 0;
int coin2 = 0;
int coin5 = 0;
int coin10 = 0;
int coin0 = 0;
int coin_summ = 0;

// функция отправки конца команды
// команда поступающая в дисплей должна кончаться символами «0xFF0xFF0xFF»
void comandEnd() {
  for (int i = 0; i < 3; i++) {
    Serial3.write(0xff);
  }
}

// отправка на Nextion (номер экрана, название переменной) + данные
void SendText(String dev, int data)
{
  Serial3.print(dev);   // Отправляем данные dev(номер экрана, название переменной) на Nextion
  Serial3.print("=\"");   // Отправляем данные =(знак равно, далее передаем сами данные) на Nextion
  Serial3.print(data);  // Отправляем данные data(данные) на Nextion
  Serial3.print("\"");
  comandEnd();
  dev = "";    // Очищаем переменную
  data = 0;   // Очищаем переменную
}
// описываем порты
void myEvent1()
{
  coin1++;
}
void myEvent2()
{
  coin2++;
}
void myEvent10()
{
  coin10++;
}
void myEvent5()
{
  coin5++;
}

void setup() {
  // открываем последовательный порт
  Serial.begin(9600);
  Serial3.begin(9600);
  attachInterrupt(5, myEvent1, FALLING);
  attachInterrupt(4, myEvent2, FALLING);
  attachInterrupt(3, myEvent10, FALLING);
  attachInterrupt(2, myEvent5, FALLING);


}
void loop()
{
  // ждём данные от дисплея
  if (Serial3.available())
  {
    char inc;    
    inc = Serial3.read();
    if (inc == 0x0A)
    {       
    int count = 0;
    count = (coin5 - coin0) * 5;
    coin_summ = count;
    SendText("tsum5.txt", count);
    count = (coin2 - coin5) * 2;
    coin_summ += count;
    SendText("tsum2.txt", count);
    count = (coin10 - coin2) * 10;
    coin_summ += count;
    SendText("tsum10.txt", count);
    count = coin1 - coin10;
    coin_summ += count;
    SendText("tsum1.txt", count);
    SendText("tsumm.txt", coin_summ);

     coin1 = 0;
          coin2 = 0;
          coin5 = 0;
          coin10 = 0;
          coin0 = 0;
          coin_summ = 0;
  }
 }
}
