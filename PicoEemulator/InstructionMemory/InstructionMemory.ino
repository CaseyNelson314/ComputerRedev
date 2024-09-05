//
//   命令メモリ
//
//   copyright (c) 2024 okawa yusuke
//

// カウント値: 4bit
// 命令メモリ: 10bit * 2^4

constexpr int COUNT_IN_PINS[] = { 0, 1, 2, 3 };
constexpr int MEM_OUT_PINS[] = { 28, 27, 26, 22, 21, 20, 19, 18, 17, 16 };

constexpr uint16_t INST_MEM[16] = {
    0b00'0000'0000,
    0b01'0101'0001,
    0b10'1010'0010,
    0b11'1111'0011,
    0b00'0000'0100,
    0b00'0000'0101,
    0b00'0000'0110,

    0b00'0000'1000,

    0b00'0000'0000,
    0b00'0000'0000,
    0b00'0000'0000,
    0b00'0000'0000,
    0b00'0000'0000,
    0b00'0000'0000,
    0b00'0000'0000,
    0b00'0000'0000,
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
        for (int i = 0; i < 10; ++i)
            digitalWrite(MEM_OUT_PINS[i], bitRead(INST_MEM[instAddress], i));
    }
    
    {
        digitalWrite(LED_BUILTIN, millis() % 500 < 100);
    }

    Serial.println(instAddress);
}
