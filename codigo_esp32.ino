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

WiFiClient espClient;
PubSubClient client(espClient);

// ===== FUNÇÃO WIFI =====
void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Conectando ao WiFi...");
  
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi conectado!");
}

// ===== RECEBER COMANDOS MQTT =====
void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Mensagem recebida: ");

  String msg;
  for (int i = 0; i < length; i++) {
    msg += (char)message[i];
  }

  Serial.println(msg);

  if (msg == "ON") {
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(BUZZER_PIN, HIGH);
  } else if (msg == "OFF") {
    digitalWrite(LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
  }
}

// ===== CONECTAR MQTT =====
void reconnect() {
  while (!client.connected()) {
    Serial.print("Conectando ao MQTT...");

    if (client.connect("ESP32Client")) {
      Serial.println("conectado!");
      client.subscribe(topic_sub);
    } else {
      Serial.print("falhou, rc=");
      Serial.print(client.state());
      delay(2000);
    }
  }
}

// ===== MEDIR DISTÂNCIA =====
float medirDistancia() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  float distance = duration * 0.034 / 2;

  return distance;
}

// ===== SETUP =====
void setup() {
  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

// ===== LOOP =====
void loop() {
  if (!client.connected()) {
    reconnect();
  }

  client.loop();

  float distancia = medirDistancia();

  Serial.print("Distancia: ");
  Serial.println(distancia);

  // Definir limite crítico (ex: < 10 cm)
  if (distancia < 10) {
    Serial.println("ALERTA: Nivel alto!");
    
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(BUZZER_PIN, HIGH);

    client.publish(topic_pub, "ALERTA NIVEL ALTO");
  } else {
    digitalWrite(LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);

    client.publish(topic_pub, "Nivel normal");
  }

  delay(2000);
}
