#define PIN_RELAY1 A0
#define PIN_RELAY2 A1
#define MAX_DURATION 10000

void setup() {
  Serial.begin(9600); // Initialize serial communication at 9600 baud
  pinMode(PIN_RELAY1, OUTPUT); // Set the relay pin as an output
  pinMode(PIN_RELAY2, OUTPUT); // Set the relay pin as an output
  digitalWrite(PIN_RELAY1, LOW); // Ensure the relay is initially turned off
  digitalWrite(PIN_RELAY2, LOW); // Ensure the relay is initially turned off
}

void loop() {
  String command = Serial.readStringUntil('\n'); // Read the command until a newline character
  command.trim(); // Remove any leading or trailing whitespace

  if (command.length() <= 0)
    return;

  int duration = command.toInt(); // Convert the command to an integer (duration in milliseconds)

  if (duration > MAX_DURATION)
  {
    Serial.print("Duration ");
    Serial.print(duration);
    Serial.print(" is too long (max ");
    Serial.print(MAX_DURATION);
    Serial.println(" milliseconds)");
    return;
  }

  if (duration > 0) {
    // Echo the understood command back to the host
    Serial.print("Resetting for ");
    Serial.print(duration);
    Serial.println(" milliseconds");

    digitalWrite(PIN_RELAY1, HIGH); // Turn the relay on
    digitalWrite(PIN_RELAY2, HIGH); // Turn the relay on
    delay(duration); // Wait for the specified duration
    digitalWrite(PIN_RELAY1, LOW); // Turn the relay off
    digitalWrite(PIN_RELAY2, LOW); // Turn the relay off
  } else {
    // Handle invalid command
    Serial.println("Invalid command received");
  }
}
