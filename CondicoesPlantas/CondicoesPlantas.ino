#define umidadeAnalogica A0 // Pino A0 para leitura analógica do sensor de umidade
const int fotoPin = A1;    // Pino A1 para o fotoresistor
int ledUmidadePin = 6;     // Pino 6 para o LED da umidade
int ledLuminosidadePin = 5; // Pino 5 para o LED da luminosidade

#include "LedControl.h" //Inclui a biblioteca LedControl para controlar a Matriz de Led
LedControl lc=LedControl(10,9,8,1); // Declara as entradas DIN, CLK e CS da Matriz de Led

void setup() {
  Serial.begin(9600);               // Inicializa a comunicação serial
  pinMode(umidadeAnalogica, INPUT); // Define o pino do sensor de umidade como entrada
  pinMode(ledUmidadePin, OUTPUT);   // Define o pino do LED da umidade como saída
  
  lc.shutdown(0,false); //Ativa a Matriz de Led
  lc.setIntensity(0,8); //Declara a intensidade da Matriz de Led
  lc.clearDisplay(0); //Limpa o Display da Matriz, dexando-o desligado por padrão
}

void loop() {
  int valorUmidade = analogRead(umidadeAnalogica); // Lê a umidade do sensor analógico
  int umidadePercentual = map(valorUmidade, 0, 1023, 0, 100); // Mapeia para uma escala de 0 a 100

  int valorFoto = analogRead(fotoPin); // Lê o valor do fotoresistor
  int fotoPercentual = map(valorFoto, 0, 1023, 100, 0); // Mapeia inversamente para uma escala de 0 a 100

  Serial.print("Umidade encontrada: ");
  Serial.print(umidadePercentual);
  Serial.println(" %");

  Serial.print("Luminosidade encontrada: ");
  Serial.print(fotoPercentual);
  Serial.println(" %");

if (fotoPercentual > 60) {
  if (valorUmidade <= 100 && valorUmidade >= 81) { //Se 'valorUmidade' for maior-igual a 81 e menor-igual que 100, a Matriz de Led exibe um coração completo
    Serial.println("Status: Solo Completamente Úmido"); //Dada a condição estabelecida anteriormente o monitor serial exibira uma mensagem
    byte customPatternA[] = { //Cria um objeto customPatterA com bytes personalizados na forma de um coração
      B01111000,
      B11111100,
      B11111110,
      B01111111,
      B01111111,
      B11111110,
      B11111100,
      B01111000,
    };
    for (int a = 0; a < 8; a++) { //Define a ativação de cada uma das 8 linhas da Matriz
      lc.setRow(0, a, customPatternA[a]); //Define que a ativação será do objeto customPatternA
    }
    digitalWrite(ledUmidadePin, HIGH);
  } 

  else if (valorUmidade <= 80 && valorUmidade >= 61) { //Se 'valorUmidade' for maior-igual a 61 e menor que 80, a Matriz de Led exibe um coração 4/6 preenchido
    Serial.println("Status: Solo Úmido "); //Dada a condição estabelecida anteriormente o monitor serial exibira uma mensagem
    byte customPatternB[] = { //Cria um objeto customPatterB com bytes personalizados na forma de um coração
      B01111000,
      B10011100,
      B10011110,
      B01011111,
      B01011111,
      B10011110,
      B10011100,
      B01111000,
    };
    for (int b = 0; b < 8; b++) { //Define a ativação de cada uma das 8 linhas da Matriz
      lc.setRow(0, b, customPatternB[b]); //Define que a ativação será do objeto customPatternB
    }
    digitalWrite(ledUmidadePin, HIGH);
  }

    else if (valorUmidade <= 60 && valorUmidade >= 41) { //Se 'valorUmidade' for maior-igual a 41 e menor que 60, a Matriz de Led exibe um coração 1/2 preenchido
      Serial.println("Status: Solo parcialmente úmido"); //Dada a condição estabelecida anteriormente o monitor serial exibira uma mensagem
      byte customPatternC[] = { //Cria um objeto customPatterC com bytes personalizados na forma de um coração
        B01111000,
        B10001100,
        B10001110,
        B01001111,
        B01001111,
        B10001110,
        B10001100,
        B01111000,
      };
      for (int c = 0; c < 8; c++) { //Define a ativação de cada uma das 8 linhas da Matriz
        lc.setRow(0, c, customPatternC[c]); //Define que a ativação será do objeto customPatternC
      }
      digitalWrite(ledUmidadePin, LOW);
    }

  else if (valorUmidade <= 40 && valorUmidade >= 21) { //Se 'valorUmidade' for maior-igual a 21 e menor que 40, a Matriz de Led exibe um coração 1/3 preenchido
    Serial.println("Status: Solo pouco úmido"); //Dada a condição estabelecida anteriormente o monitor serial exibira uma mensagem
    byte customPatternD[] = { //Cria um objeto customPatterD com bytes personalizados na forma de um coração
      B01111000,
      B10000100,
      B10000110,
      B01000111,
      B01000111,
      B10000110,
      B10000100,
      B01111000,
    };
    for (int d = 0; d < 8; d++) { //Define a ativação de cada uma das 8 linhas da Matriz
      lc.setRow(0, d, customPatternD[d]); //Define que a ativação será do objeto customPatternD
    }
    digitalWrite(ledUmidadePin, LOW);
  }
  
    else if (valorUmidade <= 20 && valorUmidade >= 11) { //Se 'valorUmidade' for maior-igual a 11 e menor que 20, a Matriz de Led exibe um coração 1/6 preenchido
      Serial.println("Status: Solo quase seco"); //Dada a condição estabelecida anteriormente o monitor serial exibira uma mensagem
      byte customPatternE[] = { //Cria um objeto customPatterE com bytes personalizados na forma de um coração
        B01111000,
        B10000100,
        B10000010,
        B01000011,
        B01000011,
        B10000010,
        B10000100,
        B01111000,
      };
      for (int e = 0; e < 8; e++) { //Define a ativação de cada uma das 8 linhas da Matriz
        lc.setRow(0, e, customPatternE[e]); //Define que a ativação será do objeto customPatternE
      }
      digitalWrite(ledUmidadePin, LOW);
    }

  else { //Se 'valorUmidade' for igual a 0, a Matriz de Led exibe um coração vazio
    Serial.println("Status: Solo totalmente seco"); //Dada a condição estabelecida anteriormente o monitor serial exibira uma mensagem
    byte customPatternF[] = { //Cria um objeto customPatterF com bytes personalizados na forma de um coração
      B01111000,
      B10000100,
      B10000010,
      B01000001,
      B01000001,
      B10000010,
      B10000100,
      B01111000,
    };
    for (int f = 0; f < 8; f++) { //Define a ativação de cada uma das 8 linhas da Matriz
      lc.setRow(0, f, customPatternF[f]); //Define que a ativação será do objeto customPatternF
    }
    digitalWrite(ledUmidadePin, LOW);
  }
} else {
    if (valorUmidade <= 100 && valorUmidade >= 81) { //Se 'valorUmidade' for maior-igual a 81 e menor-igual que 100, a Matriz de Led exibe um coração completo
    Serial.println("Status: Solo Completamente Úmido"); //Dada a condição estabelecida anteriormente o monitor serial exibira uma mensagem
    byte customPatternA[] = { //Cria um objeto customPatterA com bytes personalizados na forma de um coração
      B01111001,
      B11111100,
      B11111110,
      B01111111,
      B01111111,
      B11111110,
      B11111100,
      B01111001,
    };
    for (int a = 0; a < 8; a++) { //Define a ativação de cada uma das 8 linhas da Matriz
      lc.setRow(0, a, customPatternA[a]); //Define que a ativação será do objeto customPatternA
    }
    digitalWrite(ledUmidadePin, HIGH);
  } 

  else if (valorUmidade <= 80 && valorUmidade >= 61) { //Se 'valorUmidade' for maior-igual a 61 e menor que 80, a Matriz de Led exibe um coração 4/6 preenchido
    Serial.println("Status: Solo Úmido "); //Dada a condição estabelecida anteriormente o monitor serial exibira uma mensagem
    byte customPatternB[] = { //Cria um objeto customPatterB com bytes personalizados na forma de um coração
      B01111001,
      B10011100,
      B10011110,
      B01011111,
      B01011111,
      B10011110,
      B10011100,
      B01111001,
    };
    for (int b = 0; b < 8; b++) { //Define a ativação de cada uma das 8 linhas da Matriz
      lc.setRow(0, b, customPatternB[b]); //Define que a ativação será do objeto customPatternB
    }
    digitalWrite(ledUmidadePin, HIGH);
  }

    else if (valorUmidade <= 60 && valorUmidade >= 41) { //Se 'valorUmidade' for maior-igual a 41 e menor que 60, a Matriz de Led exibe um coração 1/2 preenchido
      Serial.println("Status: Solo parcialmente úmido"); //Dada a condição estabelecida anteriormente o monitor serial exibira uma mensagem
      byte customPatternC[] = { //Cria um objeto customPatterC com bytes personalizados na forma de um coração
        B01111001,
        B10001100,
        B10001110,
        B01001111,
        B01001111,
        B10001110,
        B10001100,
        B01111001,
      };
      for (int c = 0; c < 8; c++) { //Define a ativação de cada uma das 8 linhas da Matriz
        lc.setRow(0, c, customPatternC[c]); //Define que a ativação será do objeto customPatternC
      }
      digitalWrite(ledUmidadePin, LOW);
    }

  else if (valorUmidade <= 40 && valorUmidade >= 21) { //Se 'valorUmidade' for maior-igual a 21 e menor que 40, a Matriz de Led exibe um coração 1/3 preenchido
    Serial.println("Status: Solo pouco úmido"); //Dada a condição estabelecida anteriormente o monitor serial exibira uma mensagem
    byte customPatternD[] = { //Cria um objeto customPatterD com bytes personalizados na forma de um coração
      B01111001,
      B10000100,
      B10000110,
      B01000111,
      B01000111,
      B10000110,
      B10000100,
      B01111001,
    };
    for (int d = 0; d < 8; d++) { //Define a ativação de cada uma das 8 linhas da Matriz
      lc.setRow(0, d, customPatternD[d]); //Define que a ativação será do objeto customPatternD
    }
    digitalWrite(ledUmidadePin, LOW);
  }
  
    else if (valorUmidade <= 20 && valorUmidade >= 11) { //Se 'valorUmidade' for maior-igual a 11 e menor que 20, a Matriz de Led exibe um coração 1/6 preenchido
      Serial.println("Status: Solo quase seco"); //Dada a condição estabelecida anteriormente o monitor serial exibira uma mensagem
      byte customPatternE[] = { //Cria um objeto customPatterE com bytes personalizados na forma de um coração
        B01111001,
        B10000100,
        B10000010,
        B01000011,
        B01000011,
        B10000010,
        B10000100,
        B01111001,
      };
      for (int e = 0; e < 8; e++) { //Define a ativação de cada uma das 8 linhas da Matriz
        lc.setRow(0, e, customPatternE[e]); //Define que a ativação será do objeto customPatternE
      }
      digitalWrite(ledUmidadePin, LOW);
    }

  else { //Se 'valorUmidade' for igual a 0, a Matriz de Led exibe um coração vazio
    Serial.println("Status: Solo totalmente seco"); //Dada a condição estabelecida anteriormente o monitor serial exibira uma mensagem
    byte customPatternF[] = { //Cria um objeto customPatterF com bytes personalizados na forma de um coração
      B01111001,
      B10000100,
      B10000010,
      B01000001,
      B01000001,
      B10000010,
      B10000100,
      B01111001,
    };
    for (int f = 0; f < 8; f++) { //Define a ativação de cada uma das 8 linhas da Matriz
      lc.setRow(0, f, customPatternF[f]); //Define que a ativação será do objeto customPatternF
    }
    digitalWrite(ledUmidadePin, LOW);
  }
}
  delay(1500); //Atraso de 1500ms
}