#define PIN_LED  9
#define PIN_TRIG 12
#define PIN_ECHO 13

#define SND_VEL 346.0
#define INTERVAL 100
#define PULSE_DURATION 10
#define _DIST_MIN 100.0
#define _DIST_MAX 300.0

#define TIMEOUT ((INTERVAL / 2) * 1000.0)
#define SCALE (0.001 * 0.5 * SND_VEL)

unsigned long last_sampling_time;

void setup() {
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  digitalWrite(PIN_TRIG, LOW);
  
  Serial.begin(9600);
}

void loop() {
  float distance;

  if (millis() < (last_sampling_time + INTERVAL))
    return;

  distance = USS_measure(PIN_TRIG, PIN_ECHO);

  int ledBrightness = 255;

  if (distance < _DIST_MIN) {
    ledBrightness = 255;
  } else if (distance > _DIST_MAX) {
    ledBrightness = 255;
  } else if (distance < 150) {
    ledBrightness = map(distance, _DIST_MIN, 150, 255, 128);
  } else if (distance < 200) {
    ledBrightness = map(distance, 150, 200, 128, 0);
  } else if (distance < 250) {
    ledBrightness = map(distance, 200, 250, 0, 128);
  } else {
    ledBrightness = map(distance, 250, _DIST_MAX, 128, 255);
  }

  analogWrite(PIN_LED, ledBrightness);

  Serial.print("Min:");        Serial.print(_DIST_MIN);
  Serial.print(", distance:"); Serial.print(distance);
  Serial.print(", Max:");      Serial.print(_DIST_MAX);
  Serial.println("");
  
  last_sampling_time += INTERVAL;
}

float USS_measure(int TRIG, int ECHO) {
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(PULSE_DURATION);
  digitalWrite(TRIG, LOW);
  
  return pulseIn(ECHO, HIGH, TIMEOUT) * SCALE;
}
