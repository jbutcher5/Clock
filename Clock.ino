// { b, c, d, e, f, a, g }

void display_digit(int interface, const int *digit) {
  for (int i = 2; i < 9; i++)
    digitalWrite(i, !digit[i-2]);

  for (int i = 9; i < 14; i++)
    digitalWrite(i, i == interface);
}

void reset_pins() {
  for (int pin = 2; pin < 14; pin++) {
    if (pin <= 8) digitalWrite(pin, HIGH);
    else digitalWrite(pin, LOW);
  }
}

void display_number(int interface, int value) {
  const int DIGITAL_NAN[7] = {1, 1, 1, 1, 1, 1, 1};
  const int DIGITAL_ZERO[7] = {1, 1, 1, 1, 1, 1, 0};
  const int DIGITAL_ONE[7] = {0, 0, 0, 1, 1, 0, 0};
  const int DIGITAL_TWO[7] = {0, 1, 1, 0, 1, 1, 1};
  const int DIGITAL_THREE[7] = {0, 0, 1, 1, 1, 1, 1};
  const int DIGITAL_FOUR[7] = {1, 0, 0, 1, 1, 0, 1};

  const int *buffer;

  if (value == 0) buffer = DIGITAL_ZERO;
  else if (value == 1) buffer = DIGITAL_ONE;
  else if (value == 2) buffer = DIGITAL_TWO;
  else if (value == 3) buffer = DIGITAL_THREE;
  else if (value == 4) buffer = DIGITAL_FOUR;
  else buffer = DIGITAL_NAN;

  display_digit(interface, buffer);
}


void setup() {
  for (int pin = 2; pin < 14; pin++)
    pinMode(pin, OUTPUT);

  reset_pins();
}

void loop() {
  for (int i = 4; i > 0; i--) {
    display_number(i+9, 5-i);
    reset_pins();
  }
}
