constexpr uint8_t CATHODE[] = { 9, 10, 11, 12, 13, 14, 15 };
constexpr uint8_t ANODE[] = { 17, 16 };

constexpr uint8_t INPUT_PINS[][4] = { { 0, 1, 2, 3 }, { 4, 5, 6, 7 } };

void setup()
{
    for (int pin : CATHODE)
        pinMode(pin, OUTPUT);

    for (int pin : ANODE)
        pinMode(pin, OUTPUT);

    for (const auto& pins : INPUT_PINS)
        for (int pin : pins)
            pinMode(pin, INPUT);
}

void loop()
{

    uint values[2]{};

    for (uint pinIdx = 0; pinIdx < 2; ++pinIdx)
    {
        uint value = 0;
        for (uint i = 0; i < 4; ++i)
        {
            bitWrite(value, i, digitalRead(INPUT_PINS[pinIdx][i]));
        }
        values[pinIdx] = value & 0xf;
    }

    for (uint value : values)
    {
        Serial.print(value);
        Serial.print(" ");
    }
    Serial.println();


    for (uint anodIdx = 0; anodIdx < 2; ++anodIdx)
    {
        digitalWrite(ANODE[anodIdx], LOW);

        static const uint8_t format[]{
            0b0111111,  // 0
            0b0001001,  // 1
            0b1011110,  // 2
            0b1011011,  // 3
            0b1101001,  // 4
            0b1110011,  // 5
            0b1110111,  // 6
            0b0011001,  // 7
            0b1111111,  // 8
            0b1111011,  // 9
            0b1111101,  // A
            0b1100111,  // B
            0b0110110,  // C
            0b1001111,  // D
            0b1110110,  // E
            0b1110100,  // F
            // 0b1000000,  // 真中
            // 0b0100000,  // 左上
            // 0b0010000,  // 上
            // 0b0001000,  // 右上
            // 0b0000100,  // 左下
            // 0b0000010,  // 下
            // 0b0000001,  // 右下
        };

        const uint value = values[anodIdx];

        for (uint cathIdx = 0; cathIdx < 7; ++cathIdx)
            digitalWrite(CATHODE[cathIdx], bitRead(format[value], cathIdx));

        delay(10);

        digitalWrite(ANODE[anodIdx], HIGH);
    }
}
