// Hauptsignal
const int PIN_HP_ROT1   = 2;
const int PIN_HP_ROT2   = 3;
const int PIN_HP_GRUEN  = 4;
const int PIN_HP_GELB   = 5;
const int PIN_HP_WEISS  = 6;

// Vorsignal
const int PIN_VR_GELB1  = 7;
const int PIN_VR_GELB2  = 8;
const int PIN_VR_GRUEN1 = 9;
const int PIN_VR_GRUEN2 = 10;

// Vars
const unsigned long FAHRT_DAUER   = 8UL * 60UL * 1000UL;  // 8 Minuten auf Fahrt
const unsigned long RANGIER_DAUER = 20UL * 1000UL;        // 20 Sekunden Rangiersignal
const unsigned long HALT_DAUER    = 3UL * 30UL * 1000UL;  // 3 Minuten Zugfolge

enum SignalState {
  HALT,
  FAHRT,
  RANGIEREN
};

SignalState currentSignalState = HALT;
unsigned long begin = 0;
uint8_t currentProceedSignal = 0; // 0 = Hp1, 1 = Hp2, 2 = Sh1

void setup() {
  pinMode(PIN_HP_ROT1, OUTPUT);
  pinMode(PIN_HP_ROT2, OUTPUT);
  pinMode(PIN_HP_GRUEN, OUTPUT);
  pinMode(PIN_HP_GELB, OUTPUT);
  pinMode(PIN_HP_WEISS, OUTPUT);

  pinMode(PIN_VR_GELB1, OUTPUT);
  pinMode(PIN_VR_GELB2, OUTPUT);
  pinMode(PIN_VR_GRUEN1, OUTPUT);
  pinMode(PIN_VR_GRUEN2, OUTPUT);

  randomSeed(analogRead(0));
  
  setHp0();
  begin = millis();
}

void loop() {
  unsigned long now = millis();

  switch (currentSignalState) {

    case HALT:
      if (now - begin >= HALT_DAUER) {
        currentProceedSignal = random(0, 3);

        switch (currentProceedSignal) {
          case 0:
            currentSignalState = FAHRT;
            setHp1();
            break;
          case 1:
            currentSignalState = FAHRT;
            setHp2();
            break;
          case 2:
            currentSignalState = RANGIEREN;
            setSh1();
            break;
        }

        begin = now;
      }
      break;

    case FAHRT:
      if (now - begin >= FAHRT_DAUER) {
        setHp0();
        currentSignalState = HALT;
        begin = now;
      }
      break;

    case RANGIEREN:
      if (now - begin >= RANGIER_DAUER) {
        setHp0();
        currentSignalState = HALT;
        begin = now;
      }
      break;
  }
}

void dunkelschaltung() {
  digitalWrite(PIN_HP_ROT1, LOW);
  digitalWrite(PIN_HP_ROT2, LOW);
  digitalWrite(PIN_HP_GRUEN, LOW);
  digitalWrite(PIN_HP_GELB, LOW);
  digitalWrite(PIN_HP_WEISS, LOW);

  digitalWrite(PIN_VR_GELB1, LOW);
  digitalWrite(PIN_VR_GELB2, LOW);
  digitalWrite(PIN_VR_GRUEN1, LOW);
  digitalWrite(PIN_VR_GRUEN2, LOW);
}

// Hp0: Halt
void setHp0() {
  dunkelschaltung();

  digitalWrite(PIN_HP_ROT1, HIGH);
  digitalWrite(PIN_HP_ROT2, HIGH);
}

// Hp1: Fahrt
void setHp1() {
  dunkelschaltung();

  digitalWrite(PIN_HP_GRUEN, HIGH);
}

// Hp2: Langsamfahrt
void setHp2() {
  dunkelschaltung();

  digitalWrite(PIN_HP_GRUEN, HIGH);
  digitalWrite(PIN_HP_GELB, HIGH);
}

// Sh1: Rangierfahrt erlaubt, Zugfahrt halten
void setSh1() {
  dunkelschaltung();

  digitalWrite(PIN_HP_ROT1, HIGH);
  digitalWrite(PIN_HP_WEISS, HIGH);
}