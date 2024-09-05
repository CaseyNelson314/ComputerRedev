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


    // プログラムカウンタ用
    void countup()
    {
        ++value;
    }

    void putValue()
    {
        for (uint i = 0; i < setPins.size(); ++i)
        {
            digitalWrite(outPins[i], bitRead(value, i));
        }
    }

    void onClockFall()
    {
        for (uint i = 0; i < setPins.size(); ++i)
        {
            bitWrite(value, i, digitalRead(setPins[i]));
        }
    }
};

Register regs[] {
    { { 5, 6, 7, 8 }, { 15, 14, 13, 12 } },
    { { 1, 2, 3, 4 }, { 11, 10, 9, 8 } },
    { { 1, 2, 3, 4 }, { 11, 10, 9, 8 } }, // PC
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



    // regs[0].show(0b1101);
    // regs[1].show(0b0001);

    digitalWrite(LED_BUILTIN, millis() % 500 < 100);
}
