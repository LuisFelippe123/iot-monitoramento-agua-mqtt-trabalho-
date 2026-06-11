#include <WiFi.h>
#include <PubSubClient.h>

// ===== CONFIGURAÇÃO WIFI =====
const char* ssid = "SEU_WIFI";
const char* password = "SUA_SENHA";

// ===== CONFIGURAÇÃO MQTT =====
const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;

const char* topic_pub = "sensor/nivel_agua";
const char* topic_sub = "atuador/alerta";

// ===== PINOS =====
#define TRIG_PIN 5
#define ECHO_PIN 18
#define LED_PIN 21
#define BUZZER_PIN 22

// ===== CONFIGURAÇÃO DO RESERVATÓRIO =====
// Altura útil considerada para os testes
const float ALTURA_MAXIMA = 50.0; // cm

WiFiClient espClient;
PubSubClient client(espClient);

// ===== WIFI =====
void setup_wifi() {
delay(10);

Serial.println();
Serial.println("Conectando ao Wi-Fi...");

WiFi.begin(ssid, password);

while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}

Serial.println();
Serial.println("Wi-Fi conectado!");
Serial.print("IP: ");
Serial.println(WiFi.localIP());
}

// ===== MQTT CALLBACK =====
void callback(char* topic, byte* message, unsigned int length) {

String msg;

for (int i = 0; i < length; i++) {
msg += (char)message[i];
}

Serial.print("Mensagem recebida: ");
Serial.println(msg);

if (msg == "ON") {
digitalWrite(LED_PIN, HIGH);
digitalWrite(BUZZER_PIN, HIGH);
}

if (msg == "OFF") {
digitalWrite(LED_PIN, LOW);
digitalWrite(BUZZER_PIN, LOW);
}
}

// ===== RECONEXÃO MQTT =====
void reconnect() {

while (!client.connected()) {

```
Serial.print("Conectando ao broker MQTT...");

if (client.connect("ESP32Client")) {

  Serial.println(" conectado!");

  client.subscribe(topic_sub);

} else {

  Serial.print("Falha. Código: ");
  Serial.println(client.state());

  delay(2000);
}
```

}
}

// ===== LEITURA HC-SR04 =====
float medirDistancia() {

digitalWrite(TRIG_PIN, LOW);
delayMicroseconds(2);

digitalWrite(TRIG_PIN, HIGH);
delayMicroseconds(10);

digitalWrite(TRIG_PIN, LOW);

long duration = pulseIn(ECHO_PIN, HIGH);

float distancia = duration * 0.034 / 2;

return distancia;
}

// ===== SETUP =====
void setup() {

Serial.begin(115200);

pinMode(TRIG_PIN, OUTPUT);
pinMode(ECHO_PIN, INPUT);

pinMode(LED_PIN, OUTPUT);
pinMode(BUZZER_PIN, OUTPUT);

digitalWrite(LED_PIN, LOW);
digitalWrite(BUZZER_PIN, LOW);

setup_wifi();

client.setServer(mqtt_server, mqtt_port);
client.setCallback(callback);

Serial.println("Sistema iniciado.");
}

// ===== LOOP =====
void loop() {

if (!client.connected()) {
reconnect();
}

client.loop();

float distancia = medirDistancia();

// Cálculo do percentual de ocupação
float nivel = ((ALTURA_MAXIMA - distancia) / ALTURA_MAXIMA) * 100;

// Limitar valores
if (nivel < 0) nivel = 0;
if (nivel > 100) nivel = 100;

Serial.print("Distancia: ");
Serial.print(distancia);
Serial.print(" cm | Nivel: ");
Serial.print((int)nivel);
Serial.println(" %");

char mqttMsg[10];
sprintf(mqttMsg, "%d %%", (int)nivel);

client.publish(topic_pub, mqttMsg);

if (nivel >= 80) {

```
Serial.println("Status: ALERTA! Nivel critico atingido!");

digitalWrite(LED_PIN, HIGH);
digitalWrite(BUZZER_PIN, HIGH);

client.publish(topic_sub, "ON");
```

} else {

```
Serial.println("Status: NORMAL");

digitalWrite(LED_PIN, LOW);
digitalWrite(BUZZER_PIN, LOW);

client.publish(topic_sub, "OFF");
```

}

Serial.println("MQTT publicado com sucesso!");
Serial.println();

delay(2000);
}
