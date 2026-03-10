/*
 * Smart Agent System for Power Management
 * Developed for: Mayar Nawas (Software Engineering Senior)
 * Features: Battery Monitoring, Load Control, and Visual/Audio Feedback
 */

// Pin Definitions
const int GREEN_LED = 2;
const int RED_LED = 3;
const int BUZZER = 4;
const int BATTERY_PIN = A0; // Potentiometer 1 (Battery Simulator)
const int LOAD_PIN = A1;    // Potentiometer 2 (Load Simulator)

void setup() {
  // Initialize Output Pins
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  
  // Start Serial Communication
  Serial.begin(9600);
  
  // Power-on Self-Test (Flash LEDs)
  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(RED_LED, HIGH);
  delay(500);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, LOW);
  
  Serial.println("--- System Initialized Successfully ---");
}

void loop() {
  // 1. Perception Layer (Reading Sensor Values)
  int batteryRaw = analogRead(BATTERY_PIN);
  int loadRaw = analogRead(LOAD_PIN);
  
  // Mapping readings to percentages (0-100%)
  int batteryLevel = map(batteryRaw, 0, 1023, 0, 100);
  int loadLevel = map(loadRaw, 0, 1023, 0, 100);

  // 2. Logging State (For Debugging)
  Serial.print("Battery: "); Serial.print(batteryLevel);
  Serial.print("% | Load: "); Serial.print(loadLevel);
  Serial.println("%");

  // 3. Decision Logic (Agent Actions)
  
  if (loadLevel > 80) {
    // SCENARIO 1: OVERLOAD DETECTED
    digitalWrite(GREEN_LED, LOW);  // Kill previous state
    digitalWrite(RED_LED, HIGH);   // Visual Warning
    tone(BUZZER, 1000);            // High-pitched sound
    Serial.println("!! CRITICAL ERROR: Power Overload !!");
    delay(1000); 
    
    // Proactive Agent Action: Cut the load
    noTone(BUZZER);
    Serial.println(">> SMART AGENT: Disconnected non-essential loads.");
    digitalWrite(RED_LED, LOW);
    delay(2000); // Wait for system to stabilize
    
  } else if (batteryLevel < 20) {
    // SCENARIO 2: LOW BATTERY WARNING
    digitalWrite(GREEN_LED, LOW);  // Kill previous state
    digitalWrite(RED_LED, HIGH);   // Static Red Alert
    tone(BUZZER, 500);             // Beeping sound
    delay(200);
    noTone(BUZZER);
    Serial.println("?? WARNING: Low Battery Level ??");
    
  } else {
    // SCENARIO 3: SYSTEM STABLE
    digitalWrite(GREEN_LED, HIGH); // System is OK
    digitalWrite(RED_LED, LOW);    // No Alert
    noTone(BUZZER);                // Silence
    Serial.println(">> STATUS: System Operating Normally.");
  }
  
  delay(200); // Sensor update frequency
} 