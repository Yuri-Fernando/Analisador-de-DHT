const int sampleSize = 64; // tamanho da amostra
int adcValue[sampleSize]; // vetor para armazenar os valores de entrada

void setup() {
  Serial.begin(9600); // inicializar comunicação serial
  for (int i = 0; i < sampleSize; i++) {
    adcValue[i] = analogRead(A0); // ler o valor de entrada
    delay(10); // esperar um pouco antes de ler o próximo valor
  }
}

void loop() {
  float rmsValue = 0; // valor RMS inicial
  float thdValue = 0; // valor THD inicial
  float thdNumerator = 0; // numerador da equação THD
  
  for (int i = 0; i < sampleSize; i++) {
    rmsValue += (adcValue[i] * adcValue[i]); // calcular o valor RMS
  }
  rmsValue = sqrt(rmsValue / sampleSize); // calcular a raiz quadrada do valor RMS

  for (int i = 1; i <= 3; i++) {
    float harmonicValue = 0; // valor harmônico inicial
    for (int j = 0; j < sampleSize; j++) {
      harmonicValue += (adcValue[j] * cos(i * j)); // calcular o valor harmônico
    }
    thdNumerator += (harmonicValue * harmonicValue); // adicionar ao numerador da equação THD
  }

  thdValue = sqrt(thdNumerator) / rmsValue; // calcular o valor THD
  thdValue = thdValue * 100; // converter para porcentagem
  Serial.print("THD: "); // imprimir o valor THD no monitor serial
  Serial.println(thdValue);
  delay(2000);
}