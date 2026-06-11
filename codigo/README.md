Sistema IoT para Monitoramento de Nível de Água Utilizando MQTT
Descrição
Este projeto foi desenvolvido para a disciplina Objetos Inteligentes Conectados e tem como objetivo realizar o monitoramento do nível da água em tempo real utilizando tecnologias de Internet das Coisas (IoT).

O sistema utiliza um sensor ultrassônico HC-SR04 conectado a um microcontrolador ESP32 para medir continuamente o nível da água em um reservatório. Os dados coletados são processados pelo ESP32 e enviados através do protocolo MQTT para monitoramento remoto.

Quando o nível da água ultrapassa o limite crítico configurado (80% da capacidade do reservatório), o sistema aciona automaticamente um LED e um buzzer para indicar situação de alerta.

Componentes Utilizados
ESP32
Sensor ultrassônico HC-SR04
LED
Buzzer
Protoboard
Cabos Jumpers
Funcionamento
O sensor HC-SR04 mede a distância entre o sensor e a superfície da água.
O ESP32 calcula o percentual de ocupação do reservatório.
O nível é enviado para um broker MQTT.
Quando o nível ultrapassa 80%, o LED e o buzzer são acionados.
Os dados podem ser acompanhados remotamente em tempo real.
Comunicação MQTT
Corretor
broker.hivemq.com

Porta
1883

Tópicos Utilizados
sensor/nivel_agua

Publicação das leituras do sensor.

atuador/alerta

Publicação dos eventos de alerta do sistema.

Estrutura do Repositório
codigo/

Código-fonte do ESP32.

documentacao/

Artigo científico do projeto.

imagens/

Imagens do protótipo, MQTT e monitor serial.

diagramas/

Fluxograma e esquema eletrônico.

Demonstração
O projeto realiza:

Monitoramento contínuo do nível da água;
Envio de dados utilizando MQTT;
Acionamento de alertas visuais e sonoros;
Monitoramento remoto em tempo real.
Autor
Luís Felippe de Carvalho Monteiro

RA: 10415452
