int latchPin1 = 5; // 12 RCLK of Anode 74HC595
int clockPin1 = 6; // 11 SRCLK of Anode 74HC595
int dataPin1 = 7;  // 14 SER of Anode 74HC595

int latchPin2 = 4; // 12 RCLK of Cathode 74HC595
int clockPin2 = 10; // 11 SRCLK of Cathode 74HC595
int dataPin2 = 8;  // 14 SER of Cathode 74HC595

byte faces[][3] = {
    {0x0f, 0x20, 0x0f},
    {0x0f, 0x70, 0x0f},
    {0x01, 0x20, 0x01},
    {0x0e, 0x20, 0x0e}
};

byte segments[12];


void setup() {
    pinMode(latchPin1, OUTPUT);
    pinMode(clockPin1, OUTPUT);
    pinMode(dataPin1, OUTPUT);

    pinMode(latchPin2, OUTPUT);
    pinMode(clockPin2, OUTPUT);
    pinMode(dataPin2, OUTPUT);
    randomSeed(analogRead(0));
}


void refreshDisplay() {
    for (int digit = 0; digit < 12; digit++) {
        PORTD &= ~0x30;  // Latch 1 and 2 off
        shiftOut(dataPin2, clockPin2, MSBFIRST, ~segments[digit]);
        shiftOut(dataPin1, clockPin1, MSBFIRST, 1 << digit >> 8);
        shiftOut(dataPin1, clockPin1, MSBFIRST, 1 << digit);
        PORTD |= 0x30;  // Latch 1 and 2 on
        delayMicroseconds(50);
    }
}


void loop() {
    int randNumber = random(50, 200);
    for (int i = 0; i < randNumber; i += 1) {
        refreshDisplay();
    }

    int facePosition = random(0, 4);
    int faceIndex = random(0, sizeof(faces) / 3);
    memcpy(segments + facePosition * 3, faces[faceIndex], 3);
}
