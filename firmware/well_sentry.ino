#include <WiFi.h>
#include <HTTPClient.h>

char ssid[] = "Varun";
char pass[] = "varun123";

const char* BLYNK_AUTH_TOKEN = "9gjCsSlxKj-FITSyNPtqqbYkqYuATZ9w";
const char* BLYNK_SERVER = "blr1.blynk.cloud"; // change region prefix if yours differs

const int VIBRATION_PIN = 4;
const int GREEN_LED = 18;
const int BUZZER = 21;      // avoid GPIO2 (strapping pin)

const int TRIG_PIN = 22;
const int ECHO_PIN = 19;
const int RED_LED = 23;     // avoid GPIO15 (strapping pin)

const int IMPACT_THRESHOLD_CM = 8;
const int IMPACT_CONFIRM_NEEDED = 3;

bool lastVibrationTriggered = false;
bool lastImpactDetected = false;
int impactConfirmCount = 0;

void setup() {
  Serial.begin(115200);

  pinMode(VIBRATION_PIN, INPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  digitalWrite(GREEN_LED, HIGH);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(RED_LED, OUTPUT);
  digitalWrite(RED_LED, LOW);

  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(400);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi connected!");
  Serial.println("BoreGuard online with phone alerts.");
}

long readDistanceCM() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH, 20000);
  return duration * 0.034 / 2;
}

// Sends a named event to Blynk (triggers the push notification)
void sendBlynkEvent(String eventCode) {
  if (WiFi.status() != WL_CONNECTED) return;
  HTTPClient http;
  String url = "http://" + String(BLYNK_SERVER) + "/external/api/logEvent?token=" + String(BLYNK_AUTH_TOKEN) + "&code=" + eventCode;
  http.begin(url);
  int httpCode = http.GET();
  Serial.print("Blynk event '" + eventCode + "' sent, response: ");
  Serial.println(httpCode);
  http.end();
}

// Updates a datastream value (V0, V1) so the app dashboard shows current status
void updateBlynkPin(String pin, String value) {
  if (WiFi.status() != WL_CONNECTED) return;
  HTTPClient http;
  String url = "http://" + String(BLYNK_SERVER) + "/external/api/update?token=" + String(BLYNK_AUTH_TOKEN) + "&pin=" + pin + "&value=" + value;
  http.begin(url);
  http.GET();
  http.end();
}

void loop() {
  // ---- Layer 1: Vibration / cap breach check ----
  bool vibrationTriggered = (digitalRead(VIBRATION_PIN) == LOW); // flip to HIGH if reversed on your module

  if (vibrationTriggered && !lastVibrationTriggered) {
    digitalWrite(GREEN_LED, LOW);
    tone(BUZZER, 1000, 300);
    Serial.println("LAYER 1 ALERT: Vibration/cap breach detected!");
    sendBlynkEvent("cap_breach");
    updateBlynkPin("V0", "BREACH DETECTED");
  } else if (!vibrationTriggered && lastVibrationTriggered) {
    digitalWrite(GREEN_LED, HIGH);
    Serial.println("Cap secure again.");
    updateBlynkPin("V0", "Secure");
  }
  lastVibrationTriggered = vibrationTriggered;

  // ---- Layer 2: Mesh impact check (debounced) ----
  long distance = readDistanceCM();
  bool rawClose = (distance > 0 && distance < IMPACT_THRESHOLD_CM);
  if (rawClose) {
    impactConfirmCount++;
  } else {
    impactConfirmCount = 0;
  }
  bool impactDetected = (impactConfirmCount >= IMPACT_CONFIRM_NEEDED);

  if (impactDetected && !lastImpactDetected) {
    digitalWrite(RED_LED, HIGH);
    tone(BUZZER, 2500, 500);
    Serial.print("LAYER 2 ALERT: Impact detected at mesh! Distance = ");
    Serial.print(distance);
    Serial.println(" cm");
    sendBlynkEvent("mesh_impact");
    updateBlynkPin("V1", "IMPACT DETECTED");
  } else if (!impactDetected && lastImpactDetected) {
    digitalWrite(RED_LED, LOW);
    Serial.println("Mesh clear.");
    updateBlynkPin("V1", "Clear");
  }
  lastImpactDetected = impactDetected;

  delay(150);
}
