#define PIN_LED 13
unsigned int count = 0;
unsigned int toggle = 0;

void setup() {
  pinMode(PIN_LED, OUTPUT);
  Serial.begin(115200); // Initialize serial port
  while (!Serial) {
    ; // wait for serial port to connect.
  }
  Serial.println("Hello World!");
  count = toggle = 0;
  digitalWrite(PIN_LED, LOW); // turn off LED.
}

void loop() {
  Serial.println(++count);
  
  toggle = !toggle; // toggle LED value.
  digitalWrite(PIN_LED, toggle); // update LED status.
  
  delay(1000); // wait for 1,000 milliseconds
}

  int toggle_state(int toggle) {
    return toggle;
  }
