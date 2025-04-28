#include <arduinoFFT.h>

const int sampleSize = 64;  // Tamanho da amostra
const int adcPin = A0;       // Porta ADC


double vReal[sampleSize];       // Vetor para armazenar a amostra
double vImag[sampleSize];       // Vetor para armazenar a parte imaginária
double THD;                     // Variável para armazenar o THD
double harmonicAmplitudes[9];   // Vetor para armazenar as amplitudes dos harmônicos

void setup() {
  Serial.begin(9600);  // Inicia a comunicação serial
}

void loop() {
  // Lê a amostra
  for (int i = 0; i < sampleSize; i++) {
    vReal[i] = analogRead(adcPin);
    vImag[i] = 0;
    delay(1);  // Tempo para a próxima amostra
  }

  // Executa a FFT
  arduinoFFT fft = arduinoFFT();  // Cria o objeto FFT
  fft.Compute(vReal, vImag, sampleSize, FFT_FORWARD);
  fft.ComplexToMagnitude(vReal, vImag, sampleSize);

  // Encontra as amplitudes dos 9 primeiros harmônicos
  for (int i = 0; i < 9; i++) {
    harmonicAmplitudes[i] = vReal[i];
  }

  // Calcula a THD
  THD = 100 * sqrt(pow(harmonicAmplitudes[1], 2) + pow(harmonicAmplitudes[2], 2) + pow(harmonicAmplitudes[3], 2) + pow(harmonicAmplitudes[4], 2) + pow(harmonicAmplitudes[5], 2) + pow(harmonicAmplitudes[6], 2) + pow(harmonicAmplitudes[7], 2) + pow(harmonicAmplitudes[8], 2)) / harmonicAmplitudes[0];

  // Imprime o THD
  Serial.print("THD: ");
  Serial.println(THD);
}