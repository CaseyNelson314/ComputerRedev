//
//   レジスタ
//
//   copyright (c) 2024 okawa yusuke
//

#include <array>

/// @brief レジスタ (D-FF)
class Register
{
    const std::array<int, 4> setPins;
    const std::array<int, 4> outPins;

    uint8_t value; // 4bit

public:
    Register(
        const std::array<int, 4> setPins,
        const std::array<int, 4> outPins)
        : setPins(setPins)
        , outPins(outPins)
        , value()
    {}

    void begin()
    {
        for (int pin : setPins)
            pinMode(pin, INPUT);

        for (int pin : outPins)
            pinMode(pin, OUTPUT);
    }

    void onClockFall()
    {
        for (uint i = 0; i < setPins.size(); ++i)
        {
            digitalWrite(outPins[i], digitalRead(setPins[i]));
        }
    }
};

Register regs[] {
    { { 1, 2, 3, 4 }, { 11, 10, 9, 8 } },
    { { 5, 6, 7, 8 }, { 15, 14, 13, 12 } },
};

void setup()
{
    for (auto& reg : regs)
        reg.begin();

    pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
    if (Serial.available())
    {
        for (auto& reg : regs)
            reg.onClockFall();
        Serial.read();
    }
    digitalWrite(LED_BUILTIN, millis() % 500 < 100);
}
