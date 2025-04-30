#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "iPhone (8)";
const char* password = "palacios";

const char* mqtt_server = "35.197.26.221";

// MQTT topic
const char* topic = "esp32/led";

const int ledPin = 2;

WiFiClient espClient;
PubSubClient client(espClient);


void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP32Client")) {
      Serial.println("connected");
      client.subscribe(topic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  String message;
  for (unsigned int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  Serial.print("Message arrived: ");
  Serial.println(message);

  if (message == "ON") {
    digitalWrite(ledPin, HIGH);
  } else if (message == "OFF") {
    digitalWrite(ledPin, LOW);
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  pinMode(ledPin, OUTPUT);

  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
