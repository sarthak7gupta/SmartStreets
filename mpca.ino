int period = 500, periodmain = 5000, a = 0, i = 0, j = 0;
unsigned long time1 = 0, time2 = 0;
float s, e;
unsigned long t1 = 0, t2 = 0;

int SL1 = 11, SL2 = 10, SL3 = 9;

int LDR = A0;

int IR1 = A2, IR2 = A1, IR3 = A3;

// int R1 = 4, R2 = 7, R3 = 1;
// int Y1 = 3, Y2 = 6, Y3 = 12;
// int G1 = 2, G2 = 5, G3 = 8;

void yellow(int i) {
	if (i == 0) {
		digitalWrite(3, 1);
		digitalWrite(6, 1);
		digitalWrite(2, 0);
		digitalWrite(7, 0);
		digitalWrite(1, 1);
	} else if (i == 1) {
		digitalWrite(12, 1);
		digitalWrite(6, 1);
		digitalWrite(1, 0);
		digitalWrite(5, 0);
		digitalWrite(4, 1);
	} else if (i == 2) {
		digitalWrite(12, 1);
		digitalWrite(3, 1);
		digitalWrite(8, 0);
		digitalWrite(4, 0);
		digitalWrite(7, 1);
	}
}

void green(int i) {
	if (i == 0) {
		digitalWrite(2, 1);
		digitalWrite(7, 1);
		digitalWrite(1, 1);
		digitalWrite(4, 0);
		digitalWrite(3, 0);
		digitalWrite(6, 0);
		digitalWrite(5, 0);
		digitalWrite(12, 0);
		digitalWrite(8, 0);
	} else if (i == 1) {
		digitalWrite(4, 1);
		digitalWrite(5, 1);
		digitalWrite(1, 1);
		digitalWrite(3, 0);
		digitalWrite(2, 0);
		digitalWrite(7, 0);
		digitalWrite(6, 0);
		digitalWrite(12, 0);
		digitalWrite(8, 0);
	} else if (i == 2) {
		digitalWrite(8, 1);
		digitalWrite(4, 1);
		digitalWrite(7, 1);
		digitalWrite(3, 0);
		digitalWrite(2, 0);
		digitalWrite(6, 0);
		digitalWrite(5, 0);
		digitalWrite(1, 0);
		digitalWrite(12, 0);
	}
}

void setup() {
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(1, OUTPUT);
  Serial.begin (9600);

  pinMode(SL1, OUTPUT);
  pinMode(SL2, OUTPUT);
  pinMode(SL3, OUTPUT);

  pinMode(LDR, INPUT);

  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(IR3, INPUT);
}

void loop() {
	if (!a && (millis() > time2 + period)) {
		time1 = millis();
		green(i++);
		i %= 3;
		a = 1;
	}
	if (a && (millis() > time1 + periodmain)) {
		time2 = millis();
		yellow(j++);
		j %= 3;
		a = 0;
	}
	if (analogRead(LDR) <= 200) {
		analogWrite(SL1, 255 / 5);
		analogWrite(SL2, 255 / 5);
		analogWrite(SL3, 255 / 5);
		if (analogRead(IR1) < 50) analogWrite(SL1, 0); else analogWrite(SL1, 51);
		if (analogRead(IR2) < 50) analogWrite(SL2, 0); else analogWrite(SL2, 51);
		if (analogRead(IR3) < 50) analogWrite(SL3, 0); else analogWrite(SL3, 51);
	} else {
		analogWrite(SL1, 255);
		analogWrite(SL2, 255);
		analogWrite(SL3, 255);
	}
	if (analogRead(IR1) < 50) t1 = millis();
	if (analogRead(IR2) < 50) t2 = millis();
	if (t2 - t1 < 1000 && t2 - t1 > 0) {
		Serial.println(10000 / (t2 - t1));
		Serial.println("cm/s TOO FAST");
		t2 = t1 = 0;
	}
}