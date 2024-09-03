//
//   命令メモリ
//
//   copyright (c) 2024 okawa yusuke
//

// カウント値: 4bit
// 命令メモリ: 8bit * 2^4

constexpr int COUNT_IN_PINS[] = { 0, 1, 2, 3 };
constexpr int MEM_OUT_PINS[] = { 28, 27, 26, 22, 21, 20, 19, 18 };

constexpr uint8_t INST_MEM[16] = { 
    0x00,
    0x01,
    0x02,
    0x03,
    0x04,
    0x05,
    0x06,
    0x07,
    0x08,
    0x09,
    0x0a,
    0x0b,
    0x0c,
    0x0d,
    0x0e,
    0x0f,
};

void setup()
{
    Serial.begin(115200);

    for (int pin : COUNT_IN_PINS)
        pinMode(pin, INPUT);

    for (int pin : MEM_OUT_PINS)
        pinMode(pin, OUTPUT);

    pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
    int instAddress = 0;

    // カウント値入力 -> カウント値は命令メモリの要素を指定するアドレスとなる
    {
        for (int i = 0; i < 4; ++i)
            bitWrite(instAddress, i, digitalRead(COUNT_IN_PINS[i]));
    }

    // 命令メモリ内の値を出力
    {
        for (int i = 0; i < 8; ++i)
            digitalWrite(MEM_OUT_PINS[i], bitRead(INST_MEM[instAddress], i));
    }
    
    {
        digitalWrite(LED_BUILTIN, millis() % 500 < 100);
    }

    Serial.println(instAddress);
}
