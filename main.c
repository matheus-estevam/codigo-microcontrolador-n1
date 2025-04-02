String ssid = "Simulator Wifi";  // SSID para conectar
String password = ""; // Nosso wifi virtual não tem senha (então não faça transações bancárias nesta rede)
String host = "api.thingspeak.com"; // Open things speak API
const int httpPort = 80;
String uriTemp = "/update?api_key=1WCFLHECF3GYNU4Y&field1="; // URI para temperatura
String uriGas = "/update?api_key=1WCFLHECF3GYNU4Y&field2="; // URI para sensor de gás
String apiKeySms = "N3ZK35Y1UGJ63XTV";

int setupESP8266(void) {
  // Start our ESP8266 Serial Communication
  Serial.begin(115200);   // Serial connection over USB to computer
  Serial.println("AT");   // Serial connection on Tx / Rx port to ESP8266
  delay(10);        // Wait a little for the ESP to respond
  if (!Serial.find("OK")) return 1;
    
  // Connect to 123D Circuits Simulator Wifi
  Serial.println("AT+CWJAP=\"" + ssid + "\",\"" + password + "\"");
  delay(10);        // Wait a little for the ESP to respond
  if (!Serial.find("OK")) return 2;
  
  // Open TCP connection to the host:
  Serial.println("AT+CIPSTART=\"TCP\",\"" + host + "\"," + httpPort);
  delay(50);        // Wait a little for the ESP to respond
  if (!Serial.find("OK")) return 3;
  
  return 0;
}

void enviarTemperaturaESP8266(float temp) {
  // Construct our HTTP call
  String httpPacket = "GET " + uriTemp + String(temp) + " HTTP/1.1\r\nHost: " + host + "\r\n\r\n";
  int length = httpPacket.length();
  
  // Imprime o valor da temp na serial
  Serial.println("Valor da temperatura: " + String(temp) + "\n\n");
  
  // Send our message length
  Serial.print("AT+CIPSEND=");
  Serial.println(length);
  delay(10); // Wait a little for the ESP to respond 
  if (!Serial.find(">")) return;

  // Send our http request
  Serial.print(httpPacket);
  delay(10); // Wait a little for the ESP to respond
  if (!Serial.find("SEND OK\r\n")) return;
}

void enviarGasSensorESP8266(int gasSensor) {
  // Construct our HTTP call
  String httpPacket = "GET " + uriGas + String(gasSensor) + " HTTP/1.1\r\nHost: " + host + "\r\n\r\n";
  int length = httpPacket.length();
  
  // Imprime o valor do sensor de gás na serial
  Serial.println("Valor do sensor de gás: " + String(gasSensor) + "\n\n");
  
  // Send our message length
  Serial.print("AT+CIPSEND=");
  Serial.println(length);
  delay(10); // Wait a little for the ESP to respond 
  if (!Serial.find(">")) return;

  // Send our http request
  Serial.print(httpPacket);
  delay(10); // Wait a little for the ESP to respond
  if (!Serial.find("SEND OK\r\n")) return;
}

void sendSms() {
  String uri = "/apps/thinghttp/send_request?api_key=" + apiKeySms;
  String httpPacket = "GET " + uri + " HTTP/1.1\r\nHost: " + host + "\r\n\r\n";
  int length = httpPacket.length();
  
  // Imprime a requisição HTTP no monitor serial para depuração
  Serial.println("HTTP Request for SMS: " + httpPacket);
  
  // Send our message length
  Serial.print("AT+CIPSEND=");
  Serial.println(length);
  delay(500); 

  // Send our http request
  Serial.print(httpPacket);
  delay(1000); // Wait a little for the ESP to respond
  
  // Check for a valid response
  if (Serial.find("SEND OK\r\n")) {
    Serial.println("SMS request sent successfully");
  } else {
    Serial.println("SMS request failed");
  }
}

// Variáveis para armazenar os valores de temperatura e tensão do sensor de gás
float temp; 
float vout; 
float vout1; 

// Pinos utilizados no Arduino
int LED = 13;        // Pino do LED
int gasSensor;       // Pino do sensor de gás
int piezo = 7;       // Pino do buzzer

void setup() { 
  // Configura os pinos como entrada ou saída
  pinMode(A0, INPUT);    // Pino do sensor de gás
  pinMode(A1, INPUT);    // Pino da leitura da tensão
  pinMode(LED, OUTPUT);  // Pino do LED
  pinMode(piezo, OUTPUT); // Pino do buzzer
  
  // Inicia a comunicação serial 
  Serial.begin(9600); 
  setupESP8266();
} 

void loop() { 
  // Lê a tensão do sensor de gás
  vout = analogRead(A1); 
  // Converte a tensão para mV
  vout1 = (vout / 1023) * 5000; 
  // Converte a tensão para graus Celsius
  temp = (vout1 - 500) / 10; 
  
  // Lê o valor do sensor de gás
  gasSensor = analogRead(A0); 
  
  // Verifica se a temperatura é maior ou igual a 80 graus Celsius
  if (temp >= 80) { 
    // Acende o LED se a temperatura for maior ou igual a 80 graus Celsius
    digitalWrite(LED, HIGH); 
  } else { 
    // Apaga o LED se a temperatura for menor que 80 graus Celsius
    digitalWrite(LED, LOW); 
  } 
  
  // Verifica se o valor do sensor de gás é maior ou igual a 100
  if (gasSensor >= 100) { 
    // Ativa o buzzer se o valor do sensor de gás for maior ou igual a 100
    digitalWrite(piezo, HIGH); 
  } else { 
    // Desativa o buzzer se o valor do sensor de gás for menor que 100
    digitalWrite(piezo, LOW); 
  } 
  
  
  enviarTemperaturaESP8266(temp);
  delay(20);
  enviarGasSensorESP8266(gasSensor);
  delay(20);
  
  sendSms();
  
  delay(10000);
}
