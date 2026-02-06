/* COMSC 243PC: Physical Computing Workshop
 * RC Charging lab (Arduino Uno)
 * 
 * This program repeatedly charges and discharges an RC circuit
 * and outputs timing and voltage readings to Serial Monitor
 */

#define chargePin 7   // digital pin for charging/discharging capacitor
#define analogPin A0  // Arduino analog input for measuring capacitor voltage
#define buzzerPin 8   // buzzer pin (optional)

#define ADC_RESOLUTION  1024   // Arduino Uno is 10-bit ADC (0-1023)
#define THRESHOLD_LOW   ADC_RESOLUTION*0.001  // ~0.1% of full scale
#define THRESHOLD_HIGH  ADC_RESOLUTION*0.99 //99% of full scale  // ~99.9% of full scale

#define enableDelay false    // set false for fastest sampling
#define enableBuzzer false  // set true to enable buzzer

// Convert ADC reading to voltage (0-5V for Arduino Uno)
float adc2volt(int adc) {
  return adc * 5.0f / ADC_RESOLUTION;
}

void setup(){
  pinMode(chargePin, OUTPUT);
  digitalWrite(chargePin, LOW);

  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW);
  
  Serial.begin(9600); // start Serial Monitor
}

void loop(){
  int adcValue = analogRead(analogPin); // read capacitor voltage

  // Print time (seconds) and voltage (if buzzer disabled)
  if(!enableBuzzer) {
    Serial.print(millis()/1000.0, 4);
    Serial.print("s ");
    Serial.println(adc2volt(adcValue), 4);
  }

  // If voltage is very low, start charging
  if(adcValue < THRESHOLD_LOW){
    digitalWrite(chargePin, HIGH);
    if(enableBuzzer) digitalWrite(buzzerPin, HIGH);
  }  

  // If voltage is very high, start discharging
  if(adcValue > THRESHOLD_HIGH){
    digitalWrite(chargePin, LOW);
    if(enableBuzzer) digitalWrite(buzzerPin, LOW);
  }

  // Optional delay for readability
  if(enableDelay) {
    delay(50);
  }
}
