#include <arduinoFFT.h>

const int sampleSize = 128;
const double sampleInterval = 0.1;
const double harmonicThreshold = 0.1;
unsigned long samplingFrequency = 1000;

arduinoFFT FFT = arduinoFFT();
double vReal[sampleSize];
double vImag[sampleSize];

void setup() {
  Serial.begin(115200);
  for (int i = 0; i < sampleSize; i++) {
    vReal[i] = analogRead(A0);
    delay(sampleInterval);
    //delayMicroseconds(samplingFrequency);
  }
  FFT.Windowing(vReal, sampleSize, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(vReal, vImag, sampleSize, FFT_FORWARD);
  FFT.ComplexToMagnitude(vReal, vImag, sampleSize);
  double fundamentalFrequency = FFT.MajorPeak(vReal, sampleSize, sampleInterval);
  Serial.print("Fundamental frequency: ");
  Serial.println(fundamentalFrequency);
  for (int i = 0; i < sampleSize / 2; i++) {
    double harmonicFrequency = (i + 1) * fundamentalFrequency;
    double harmonicAmplitude = vReal[i] / fundamentalFrequency;
    double harmonicPhase = atan2(vImag[i], vReal[i]);
    if (harmonicAmplitude > harmonicThreshold) {
      Serial.print("Harmonic frequency: ");
      Serial.print(harmonicFrequency);
      Serial.print(" Amplitude: ");
      Serial.print(harmonicAmplitude);
      Serial.print(" Phase: ");
      Serial.println(harmonicPhase);
    }
  }
}

void loop() {
}