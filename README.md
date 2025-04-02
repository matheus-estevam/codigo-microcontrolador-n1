# Alarme de Incêndio com ESP8266 e ThingSpeak

## 📌 Descrição do Projeto
Este projeto consiste em um **sistema de alarme de incêndio** baseado no ESP8266, que monitora temperatura e presença de gases inflamáveis. Os dados dos sensores são enviados para a **plataforma ThingSpeak** via conexão Wi-Fi, e **um alerta SMS** é disparado quando valores críticos são atingidos.

## 🚀 Funcionalidades
- Monitoramento contínuo da **temperatura** e **nível de gás** no ambiente.
- **Ativação de LED e buzzer** para alerta local quando valores críticos são detectados.
- **Envio de dados para o ThingSpeak** para registro e análise remota.
- **Notificação via SMS** para alertar sobre condições perigosas.

## 🛠 Componentes Utilizados
- **ESP8266** (para conexão Wi-Fi e envio de dados)
- **Sensor de Temperatura** (para medir variações térmicas)
- **Sensor de Gás** (para detectar presença de gases inflamáveis)
- **Buzzer (Piezo)** (para alerta sonoro)
- **LED** (para indicação visual de perigo)
- **ThingSpeak API** (para registro e monitoramento online)

## ⚙️ Esquemático Elétrico e Ligações
Os sensores e atuadores são conectados ao Arduino, que se comunica com o ESP8266. O diagrama de conexões pode ser visualizado no **Tinkercad** para facilitar a montagem.

## 💻 Código Fonte (Resumo)
O código foi estruturado em funções para:
- **Configurar e conectar o ESP8266 ao Wi-Fi**
- **Ler os sensores de temperatura e gás**
- **Ativar alertas locais (LED e buzzer)**
- **Enviar dados ao ThingSpeak via requisições HTTP**
- **Disparar notificações SMS**

## 🧪 Testes e Validação
- Testes foram realizados no **Tinkercad** para verificar a resposta dos sensores.
- Foram simuladas condições de **alta temperatura e presença de gás** para validar os alertas.
- A comunicação com o **ThingSpeak e envio de SMS** foi testada e ajustada para garantir confiabilidade.

## 🔧 Melhorias Futuras
- Implementação de **um display LCD** para exibição local dos dados.
- Uso de um **relé** para ativar um sistema de ventilação automaticamente.
- Integração com um **banco de dados** para histórico de medições e relatórios.

## 📜 Conclusão
Este projeto demonstra a **eficiência da IoT na segurança doméstica**, permitindo monitoramento remoto e acionamento de alertas automáticos. A modularização do código facilita futuras melhorias e expansões. 🚀

