#include <Arduino.h>
#include <LedControl.h>

#define UMIDADE_ANALOGICA A0
#define FOTO_PIN A1
#define LED_UMIDADE_PIN 6

LedControl lc = LedControl(10, 9, 8, 1); // DIN, CLK, CS, número de matrizes

void setup() {
  Serial.begin(9600);
  pinMode(UMIDADE_ANALOGICA, INPUT);
  pinMode(LED_UMIDADE_PIN, OUTPUT);

  lc.shutdown(0, false);   // Ativar a matriz de LED
  lc.setIntensity(0, 8);   // Definir a intensidade da matriz de LED
  lc.clearDisplay(0);      // Limpar o display da matriz de LED
}

void exibirPadraoCoracao(byte * pattern) {
  for (int row = 0; row < 8; row++) {
    lc.setRow(0, row, pattern[row]);
  }
}

void loop() {
  int valorUmidade = analogRead(UMIDADE_ANALOGICA);
  int umidadePercentual = map(valorUmidade, 1023, 315, 0, 100);

  int valorFoto = analogRead(FOTO_PIN);
  int fotoPercentual = map(valorFoto, 315, 1023, 100, 0);

  Serial.print("Umidade encontrada: ");
  Serial.print(umidadePercentual);
  Serial.println(" %");

  Serial.print("Luminosidade encontrada: ");
  Serial.print(fotoPercentual);
  Serial.println(" %");

  digitalWrite(LED_UMIDADE_PIN, fotoPercentual > 30 && umidadePercentual > 60);

  if (umidadePercentual >= 81) {
    Serial.println("Status: Solo completamente úmido");
    byte coracaoCompleto[] = {
      B01111000,
      B11111100,
      B11111110,
      B01111111,
      B01111111,
      B11111110,
      B11111100,
      B01111000
    };
    exibirPadraoCoracao(coracaoCompleto);
  } else if (umidadePercentual >= 61) {
    Serial.println("Status: Solo úmido");
    byte coracaoQuatroSeis[] = {
      B01111000,
      B10011100,
      B10011110,
      B01011111,
      B01011111,
      B10011110,
      B10011100,
      B01111000
    };
    exibirPadraoCoracao(coracaoQuatroSeis);
  } else if (umidadePercentual >= 41) {
    Serial.println("Status: Solo parcialmente úmido");
    byte coracaoMeio[] = {
      B01111000,
      B10001100,
      B10001110,
      B01001111,
      B01001111,
      B10001110,
      B10001100,
      B01111000
    };
    exibirPadraoCoracao(coracaoMeio);
  } else if (umidadePercentual >= 21) {
    Serial.println("Status: Solo pouco úmido");
    byte coracaoUmTerco[] = {
      B01111000,
      B10000100,
      B10000110,
      B01000111,
      B01000111,
      B10000110,
      B10000100,
      B01111000
    };
    exibirPadraoCoracao(coracaoUmTerco);
  } else if (umidadePercentual >= 10){
    Serial.println("Status: Solo quase seco");
    byte coracaoUmSeis[] = {
      B01111000,
      B10000100,
      B10000010,
      B01000011,
      B01000011,
      B10000010,
      B10000100,
      B01111000
    };
    exibirPadraoCoracao(coracaoUmSeis);
  } else {
    Serial.println("Satatus: Solo Seco");
    byte coracaoVazio[] = {
      B01111000,
      B10000100,
      B10000010,
      B01000001,
      B01000001,
      B10000010,
      B10000100,
      B01111000
    };
    exibirPadraoCoracao(coracaoVazio);
  }

  delay(1500);
}
