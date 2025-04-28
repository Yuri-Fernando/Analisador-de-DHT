#include <arduinoFFT.h>

// Tamanho da amostra do sinal
#define SAMPLES 64

// Variáveis ​​para armazenar as amostras do sinal e os valores da FFT
double vReal[SAMPLES];
double vImag[SAMPLES];

void setup() {
  // Inicializar a comunicação serial
  Serial.begin(9600);
}

void loop() {
  // Capturar amostras do sinal
  for (int i = 0; i < SAMPLES; i++) {
    vReal[i] = analogRead(A0);
    delayMicroseconds(1000);
  }

  // Executar a FFT
  arduinoFFT fft = arduinoFFT();
  fft.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  fft.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
  fft.ComplexToMagnitude(vReal, vImag, SAMPLES);

  // Calcular o THD
  double thd = 0;
  double fundamental = vReal[1];
  for (int i = 2; i <= 9; i++) {
    thd += vReal[i] * vReal[i];
  }
  thd = sqrt(thd) / fundamental;
  thd = thd * 100;

  // Enviar o THD para o monitor serial
  Serial.print("THD: ");
  Serial.print(thd);
  Serial.println("%");

  //Esperar algum tempo
  delay(2000);
}