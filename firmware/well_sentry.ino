// WellSentry - Borewell Safety Prototype
// ESP32 + SW-420 + HC-SR04 + Buzzer + LEDs

#define VIBRATION_PIN 27
#define TRIG_PIN 5
#define ECHO_PIN 18

#define BUZZER_PIN 25

#define GREEN_LED 26
#define YELLOW_LED 14
#define RED_LED 12

// Distance threshold for prototype
#define FALL_DISTANCE_CM 30

long readDistanceCM() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000);

  if (duration == 0) {
    return -1;
  }

  return duration * 0.0343 / 2;
}

void safeState() {
  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(RED_LED, LOW);
  digitalWrite(BUZZER_PIN, LOW);
}

void tamperAlert() {
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(YELLOW_LED, HIGH);
  digitalWrite(RED_LED, LOW);

  digitalWrite(BUZZER_PIN, HIGH);
  delay(300);
  digitalWrite(BUZZER_PIN, LOW);
}

void fallAlert() {
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(RED_LED, HIGH);

  digitalWrite(BUZZER_PIN, HIGH);
  delay(1000);
  digitalWrite(BUZZER_PIN, LOW);
}

void setup() {
  Serial.begin(115200);

  pinMode(VIBRATION_PIN, INPUT);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(BUZZER_PIN, OUTPUT);

  pinMode(GREEN_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);

  safeState();

  Serial.println("================================");
  Serial.println("       WellSentry Started");
  Serial.println("================================");
}

void loop() {

  // -----------------------------
  // 1. CAP TAMPER DETECTION
  // -----------------------------

  int vibration = digitalRead(VIBRATION_PIN);

  if (vibration == HIGH) {

    Serial.println("WARNING: CAP TAMPER DETECTED!");

    tamperAlert();

    delay(500);
  }

  // -----------------------------
  // 2. IN-SHAFT FALL DETECTION
  // -----------------------------

  long distance = readDistanceCM();

  if (distance > 0) {

    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    if (distance < FALL_DISTANCE_CM) {

      Serial.println("!!! FALL DETECTED !!!");

      fallAlert();

      delay(1000);
    }
    else {
      safeState();
    }
  }

  delay(100);
}
