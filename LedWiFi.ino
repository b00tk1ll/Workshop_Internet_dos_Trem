#include <ESP8266WiFi.h>
 
const char* ssid = "Wifi";
const char* password = "Senha";
 
int ledPin = 0; // GPIO13---D3 no NODEMCU
WiFiServer server(80);
 
void setup() {
  Serial.begin(115200);
  delay(10);
 
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
 
  // Conectar a Rede WIFI
  Serial.println();
  Serial.println();
  Serial.print("Conectando a: ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi Conectado");
 
  // Iniciando Server
  server.begin();
  Serial.println("Server Iniciado");
 
  // Imprimindo URL
  Serial.print("Use a URL para conectar a lampada: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
 
}
 
void loop() {
  // Checar se um Cliente está conctado
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Aguardar Cliente
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // LEr a primeira linha da requisição
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  // Validar a requisição
 
  int value = LOW;
  if (request.indexOf("/LED=ON") != -1)  {
    digitalWrite(ledPin, HIGH);
    value = HIGH;
  }
  if (request.indexOf("/LED=OFF") != -1)  {
    digitalWrite(ledPin, LOW);
    value = LOW;
  }
 
 
  // Retornar resposta ao sevidor
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
 
  client.print("O led está: ");
 
  if(value == HIGH) {
    client.print("Ligado");
  } else {
    client.print("Desligado");
  }
  client.println("<br><br>");
  client.println("<a href=\"/LED=ON\"\"><button>On </button></a>");
  client.println("<a href=\"/LED=OFF\"\"><button>Off </button></a><br />");  
  client.println("</html>");
 
  delay(1);
  Serial.println("Cliente Desconectado");
  Serial.println("");
 
}
