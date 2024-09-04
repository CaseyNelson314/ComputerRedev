//
//   マルチプレクサ
//
//   copyright (c) 2024 okawa yusuke
//


constexpr uint8_t IN_PINS[4][4] = { 
    {  0,  1,  2,  3 },
    {  4,  5,  6,  7 },
    {  8,  9, 10, 11 },
    { 12, 13, 14, 15 },
};

const uint8_t SELECT_IN_PINS[] = { 27, 26 };

constexpr uint8_t OUT_PINS[] = { 21, 20, 19, 18 };

void setup()
{
    Serial.begin(115200);

    for (const auto& pins : IN_PINS)
        for (int pin : pins)
            pinMode(pin, INPUT);

    for (int pin : SELECT_IN_PINS)
        pinMode(pin, INPUT);

    for (int pin : OUT_PINS)
        pinMode(pin, OUTPUT);

    pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
    uint8_t select = 0;

    // 選択信号入力
    {
        for (uint i = 0; i < sizeof SELECT_IN_PINS; ++i)
            bitWrite(select, i, digitalRead(SELECT_IN_PINS[i]));
    }

    // 入力を選択し出力
    {
        const auto& inputPins = IN_PINS[select];
        for (uint i = 0; i < sizeof OUT_PINS; ++i)
            digitalWrite(OUT_PINS[i], digitalRead(inputPins[i]));
    }
    
    {
        digitalWrite(LED_BUILTIN, millis() % 500 < 100);
    }

    Serial.println(select);
}
