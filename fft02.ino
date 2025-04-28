#include <arduinoFFT.h>
#define SAMPLES 128 // Tamanho da amostra
#define SAMPLING_FREQUENCY 4000 // Frequência de amostragem

arduinoFFT FFT = arduinoFFT(); // Cria um objeto FFT
unsigned int sampling_period_us;
double vReal[SAMPLES];
double vImag[SAMPLES];

void setup() {
  Serial.begin(115200); // Inicia a comunicação serial
  sampling_period_us = round(1000000 * (1.0 / SAMPLING_FREQUENCY));
}

void loop() {
  for (int i = 0; i < SAMPLES; i++) {
    vReal[i] = analogRead(A0); // Lê o sinal de entrada na porta A0
    vImag[i] = 0;
    delayMicroseconds(sampling_period_us);
  }

  FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD); // Aplica a janela de Hamming
  FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD); // Executa a DFT
  FFT.ComplexToMagnitude(vReal, vImag, SAMPLES); // Calcula a magnitude do resultado

  double THD = 0;
  for (int i = 1; i <= 9; i++) { // Calcula a distorção harmônica para as 9 primeiras harmônicas
    THD += vReal[i] * vReal[i];
  }
  THD = sqrt(THD)/vReal[1] * 100; // Calcula o percentual de distorção harmônica

  Serial.print("Distorção harmônica (THD): ");
  Serial.print(THD);
  Serial.println("%");
  delay(800);

  // Plotar os resultados
  // Código para plotar os resultados aqui
}