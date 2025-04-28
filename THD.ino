#define N 9 // Número de harmônicas
#define M 64 // Tamanho do sinal
int adc_value[M]; // Sinal lido da porta ADC

void setup() {
  // Inicialização do Arduino
}

void loop() {
  for (int i = 0; i < M; i++) {
    adc_value[i] = analogRead(A0); // Lê o sinal da porta ADC
  }

  // Calcula a DFT do sinal
  float real[N], imag[N];
  for (int k = 0; k < N; k++) {
    real[k] = 0;
    imag[k] = 0;
    for (int n = 0; n < M; n++) {
      real[k] += adc_value[n] * cos(2 * PI * k * n / M);
      imag[k] -= adc_value[n] * sin(2 * PI * k * n / M);
    }
  }

  // Imprime os resultados
  for (int k = 0; k < N; k++) {
    Serial.print("Harmônica ");
    Serial.print(k);
    Serial.print(": ");
    Serial.print(real[k]);
    Serial.print(" + ");
    Serial.print(imag[k]);
    Serial.println("i");
  }

  delay(1000); // Aguarda 1 segundo antes de realizar a próxima leitura
}