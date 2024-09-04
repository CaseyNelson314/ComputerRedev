constexpr uint8_t CATHODE[] = { 9, 10, 11, 12, 13, 14, 15 };
constexpr uint8_t ANODE[] = { 16, 17 };

void setup()
{
    for (int pin : CATHODE)
        pinMode(pin, OUTPUT);

    for (int pin : ANODE)
        pinMode(pin, OUTPUT);
}

void loop()
{
    for (int pin : CATHODE)
        digitalWrite(pin, HIGH);

    for (int pin : ANODE)
        digitalWrite(pin, LOW);
}
