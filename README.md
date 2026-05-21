# 🌊 Sistema IoT para Monitoramento de Nível de Água com MQTT

## 📌 Descrição do Projeto

Este projeto apresenta o desenvolvimento de um sistema IoT capaz de monitorar o nível de água em tempo real utilizando o microcontrolador ESP32, sensor ultrassônico HC-SR04 e comunicação via protocolo MQTT.

A solução foi desenvolvida com foco em aplicações de prevenção de enchentes urbanas, oferecendo uma alternativa de baixo custo, eficiente e com monitoramento remoto.

---

## 🎯 Objetivo

Desenvolver um sistema capaz de:

- Monitorar o nível da água em tempo real
- Enviar dados via internet utilizando MQTT
- Acionar alertas locais (LED e buzzer)
- Permitir monitoramento remoto por meio de broker MQTT

---

## ⚙️ Tecnologias Utilizadas

- ESP32
- Sensor Ultrassônico HC-SR04
- Protocolo MQTT
- Arduino IDE
- Wi-Fi (Comunicação)
- Protoboard e Jumpers

---

## 🧰 Componentes Utilizados

- ESP32
- Sensor HC-SR04
- LED
- Buzzer
- Resistores
- Protoboard
- Jumpers

---

## 🔌 Esquema do Circuito

📷 O circuito do projeto pode ser visualizado abaixo:


---

## 🔄 Funcionamento do Sistema

O sistema funciona da seguinte forma:

1. O ESP32 é inicializado e conectado à rede Wi-Fi
2. É realizada a conexão com o broker MQTT
3. O sensor ultrassônico mede a distância da água
4. O sistema calcula o nível da água
5. Se o nível ultrapassar o limite crítico:
   - LED é acionado
   - Buzzer emite som
6. Os dados são enviados via MQTT
7. O sistema pode receber comandos remotos para acionamento dos atuadores

---

## 🔁 Fluxo do Sistema

📷 Fluxograma do funcionamento:


---

## 📡 Comunicação MQTT

O sistema utiliza os seguintes tópicos:

- `sensor/nivel_agua` → envio de dados do sensor
- `atuador/alerta` → recebimento de comandos

---

## 📊 Resultados Obtidos

O sistema apresentou:

- Baixa latência na leitura do sensor
- Resposta rápida no acionamento de atuadores
- Comunicação estável via MQTT

Tempo médio de resposta:

- Sensor: 125 ms  
- Atuador: 88 ms  

---

## 📹 Vídeo do Projeto

🔗 

---

## 💻 Código do Projeto

O código desenvolvido realiza:

- Leitura do sensor ultrassônico
- Processamento do nível de água
- Comunicação com broker MQTT
- Acionamento de atuadores

---

## 📈 Possíveis Melhorias

- Desenvolvimento de aplicativo mobile
- Armazenamento em nuvem
- Uso de energia solar
- Integração com sistemas de alerta urbano

---

## 📚 Referências

- MQTT. Disponível em: http://mqtt.org
- Arduino. Disponível em: https://www.arduino.cc
- BERTOLETI, P. Controle e Monitoramento IoT com NodeMCU e MQTT
- NODE-RED. Interacting with Arduino

---

## 👨‍💻 Autor

**Luís Felippe de Carvalho Monteiro**  
Análise e Desenvolvimento de Sistemas – 5º Semestre  
Universidade Presbiteriana Mackenzie
