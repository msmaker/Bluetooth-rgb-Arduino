#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>
SoftwareSerial bluetooth(10, 11);//TX, RX (Bluetooth)

#define P 0x000000//PRETO
#define Z 0x0000FF//AZUL
#define E 0x008000//VERDE
#define R 0x800080//ROXO
#define V 0xFF0000//VERMELLHO
#define L 0xFFA500//LARANJA
#define A 0xFFFF00//AMARELO
#define B 0xFFFFFF//BRANCO
#define led1 3
#define led2 4
#define led3 5

#define PIN 6// Pino de controle
#define LED_COUNT 10// Quantidade de LED's
//Cria uma instância da Classe Adafruit NeoPixel chamado "leds"
Adafruit_NeoPixel leds = Adafruit_NeoPixel(LED_COUNT, PIN, NEO_GRB + NEO_KHZ800);



String comando;
void setup() {
  Serial.begin(9600);
  bluetooth.begin(9600);

  leds.begin(); // Inicia a fita de LED
  clearLEDs();   // Apaga todos os LEDs
  leds.show(); // Atualiza o estados dos LEDs


  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

}

void loop() {

  comando = "";

  if (bluetooth.available()) {
    while (bluetooth.available()) {
      char caracter = bluetooth.read();

      comando += caracter;
      delay(1);
    }

    Serial.println(comando);

    leds.setPixelColor(0, comando.toInt()); //Aciona o LED requerido
    leds.show();//Atualiza o LED


    if (comando.indexOf("led1") >= 0) {
      digitalWrite(led1, !digitalRead(led1));

    }

    bluetooth.print("{");

    if (digitalRead(led1)) {
      bluetooth.println("l1on");
      // leds.setPixelColor(0, 255); //Aciona o LED requerido
      //leds.show();//Atualiza o LED
    } else {
      bluetooth.println("l1of");
    }

    bluetooth.print("}");



  }
}

//Função liga led individual
void ligaLED(int g, unsigned long fita)//Recebe a posição e tempo de Delay
{
  leds.setPixelColor(g, fita);//Aciona o LED requerido
  leds.show();//Atualiza o LED
}


//Função apaga LED individual
void apagaLED(int g, unsigned long fita)//Recebe a posição e tempo de Delay
{
  leds.setPixelColor(g, 0);//Desaciona o LED requerido
  leds.show();//Atualiza o LED
}

//Função apaga LEDs geral
void clearLEDs()
{
  for (int p = 0; p < LED_COUNT; p++)
  {
    leds.setPixelColor(p, 0);
    leds.show();
  }
}
