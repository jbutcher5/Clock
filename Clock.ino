// { b, c, d, e, f, a, g }

typedef struct {
  int hours;
  int minutes;
} Time;

void display_array(int interface, const int *digit) {
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

void display_digit(int interface, int value) {
  const int DIGITAL_ZERO[7] = {1, 1, 1, 1, 1, 1, 0};
  const int DIGITAL_ONE[7] = {0, 0, 0, 1, 1, 0, 0};
  const int DIGITAL_TWO[7] = {0, 1, 1, 0, 1, 1, 1};
  const int DIGITAL_THREE[7] = {0, 0, 1, 1, 1, 1, 1};
  const int DIGITAL_FOUR[7] = {1, 0, 0, 1, 1, 0, 1};
  const int DIGITAL_FIVE[7] = {1, 0, 1, 1, 0, 1, 1};
  const int DIGITAL_SIX[7] = {1, 1, 1, 1, 0, 1, 1};
  const int DIGITAL_SEVEN[7] = {0, 0, 0, 1, 1, 1, 0};
  const int DIGITAL_EIGHT[7] = {1, 1, 1, 1, 1, 1, 1};
  const int DIGITAL_NINE[7] = {1, 0, 0, 1, 1, 1, 1};

  const int *buffer;

  if (value == 0) buffer = DIGITAL_ZERO;
  else if (value == 1) buffer = DIGITAL_ONE;
  else if (value == 2) buffer = DIGITAL_TWO;
  else if (value == 3) buffer = DIGITAL_THREE;
  else if (value == 4) buffer = DIGITAL_FOUR;
  else if (value == 5) buffer = DIGITAL_FIVE;
  else if (value == 6) buffer = DIGITAL_SIX;
  else if (value == 7) buffer = DIGITAL_SEVEN;
  else if (value == 8) buffer = DIGITAL_EIGHT;
  else if (value == 9) buffer = DIGITAL_NINE;
  else buffer = DIGITAL_ZERO;

  display_array(interface, buffer);
}

void display_number(int n) {
  int a;

  a = n % 10;

  display_digit(10, a);
  reset_pins();

  n /= 10;

  a = n % 10;

  display_digit(11, a);
  reset_pins();

  n /= 10;

  a = n % 10;

  display_digit(12, a);
  reset_pins();

  n /= 10;

  a = n % 10;

  display_digit(13, a);
  reset_pins();
}

void to_time(Time *buffer, unsigned long ms) {
  ms %= (unsigned long)(8.64*pow(10, 7));

  buffer->minutes = (int)ms / (int)(3.6*pow(10, 6));
  buffer->hours = (int)ms / (int)(3.6*pow(10, 6));
}

void setup() {
  for (int pin = 2; pin < 14; pin++)
    pinMode(pin, OUTPUT);

  reset_pins();


}

void loop() {
  static int is_initial = 1;
  static unsigned long last_update;
  static int i = -1;

  unsigned long time = millis();

  if (time > last_update + 1000 || is_initial) {

    last_update = time;
    i++;
  }

  is_initial = 0;

  display_number(i);
}
