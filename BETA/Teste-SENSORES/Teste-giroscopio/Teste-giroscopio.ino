#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

Adafruit_MPU6050 mpu;

void setup() {
  Serial.begin(9600);
  // Inicializa a comunicação I2C
  if (!mpu.begin()) {
    Serial.println("Falha ao inicializar o MPU6050! Verifique as conexões.");
    while (1);
  }
  Serial.println("MPU6050 inicializado com sucesso!");

  // Configura a taxa de amostragem e a faixa de sensibilidade
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
}

void loop() {
  /* Obtém os dados de aceleração e giroscópio */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // Exibe os valores de aceleração
  Serial.print("Acelerometro X: ");
  Serial.print(a.acceleration.x);
  Serial.print(" m/s^2, Y: ");
  Serial.print(a.acceleration.y);
  Serial.print(" m/s^2, Z: ");
  Serial.print(a.acceleration.z);
  Serial.println(" m/s^2");

  // Exibe os valores de rotação
  Serial.print("Giroscopio X: ");
  Serial.print(g.gyro.x);
  Serial.print(" rad/s, Y: ");
  Serial.print(g.gyro.y);
  Serial.print(" rad/s, Z: ");
  Serial.print(g.gyro.z);
  Serial.println(" rad/s");

  // Exibe a temperatura
  Serial.print("Temperatura: ");
  Serial.print(temp.temperature);
  Serial.println(" C");

  Serial.println("");
  delay(500); // Espera 500ms antes da próxima leitura
}
