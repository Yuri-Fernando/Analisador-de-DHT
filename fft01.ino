#include <arduinoFFT.h> // inclui a biblioteca arduinoFFT

#define SAMPLES 64  // tamanho do vetor de amostras
#define ADC_BITS 10  // resolução do conversor AD
#define VREF 5.0     // tensão de referência do conversor AD
#define SAMPLING_FREQUENCY 6000 // frequencia de amostragem

arduinoFFT FFT = arduinoFFT(); // cria um objeto FFT

double vReal[SAMPLES]; // vetor para armazenar as amostras do sinal
double vImag[SAMPLES]; // vetor para armazenar as partes imaginárias do sinal
double THD;

void setup() {
  Serial.begin(9600);  // inicializa o monitor serial
}

void loop() {
  for (int i = 0; i < SAMPLES; i++) {
    vReal[i] = analogRead(A0) * VREF / (pow(2, ADC_BITS) - 1);
    delayMicroseconds(1.0 / SAMPLING_FREQUENCY * 1000000.0);
  }
  FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
  FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);

  // Calcular THD
  double harmonic_power[9];
  double fundamental_power = vReal[1];
  harmonic_power[0] = fundamental_power;
  THD = 0;
  for (int i = 1; i < 9; i++) {
    harmonic_power[i] = vReal[i*SAMPLES/SAMPLING_FREQUENCY];
    THD += harmonic_power[i]*harmonic_power[i];
  }
  THD = sqrt(THD)/fundamental_power;
  
  
  // Plotar os resultados
  for (int i = 1; i < SAMPLES; i++) {
    //Serial.print(vReal[i]);
    Serial.println(THD);
    //Serial.print(",");
  }
  //Serial.println();
  delay(1000);
}