//
//   命令デコーダ
//
//   copyright (c) 2024 okawa yusuke
//

constexpr int INST_IN_PINS[] = { 0, 1, 2, 3, 4, 5, 6, 7 };

void setup()
{
    Serial.begin(115200);

    for (int pin : INST_IN_PINS)
        pinMode(pin, INPUT);

    pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
    uint8_t inst = 0;

    // 命令値入力
    for (int i = 0; i < 8; ++i)
    {
        bitWrite(inst, i, digitalRead(INST_IN_PINS[i]));
    }
    
    {
        digitalWrite(LED_BUILTIN, millis() % 500 < 100);
    }

    Serial.println(inst);

    delay(10);

}
