// センサー1
int analogIN0 = A0;
int D0 = 7;
int Aval0 = 0;
int Dval0 = 0;

//センサー2
int analogIN1 = A1;
int D1 = 6;
int Aval1 = 0;
int Dval1 = 0;

void setup() {
    // put your setup code here, to run once:
    pinMode(A0, INPUT);
    pinMode(D0, INPUT);
    pinMode(A1, INPUT);
    pinMode(D1, INPUT);
    Serial.begin(9600);
}

void loop() {
    Aval0 = analogRead(analogIN0);
    Dval0 = digitalRead(D0);

    Aval1 = analogRead(analogIN1);
    Dval1 = digitalRead(D1);

    Serial.print("Analog val0:");
    Serial.print(Aval0);
    Serial.print(", Digital val0:");
    Serial.print(Dval0);
    Serial.print(", Analog val1:");
    Serial.print(Aval1);
    Serial.print(", Digital val1:");
    Serial.println(Dval1);

    delay(800);

}