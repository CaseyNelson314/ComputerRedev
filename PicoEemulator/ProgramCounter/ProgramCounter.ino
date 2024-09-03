//
//   プログラムカウンタ
//
//   copyright (c) 2024 okawa yusuke
//


constexpr int CLOCK_IN_PIN = 2;

constexpr int COUNT_OUT_PINS[] = { 28, 27, 26, 22 };

void setup()
{
    Serial.begin(115200);

    pinMode(CLOCK_IN_PIN, INPUT_PULLUP);

    for (int pin : COUNT_OUT_PINS)
        pinMode(pin, OUTPUT);

    pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
    static uint8_t counter;

    // クロック入力
    {
        static bool prev;
        const bool curr = digitalRead(CLOCK_IN_PIN) == LOW;
        if (curr and not prev)
        {
            ++counter;
            if (counter > 0b1111)
                counter = 0;
        }
        prev = curr;
    }

    // カウント値出力
    {
        for (int i = 0; i < 4; ++i)
            digitalWrite(COUNT_OUT_PINS[i], bitRead(counter, i));
    }

    {
        digitalWrite(LED_BUILTIN, millis() % 500 < 100);
    }

    Serial.println(counter);
    delayMicroseconds(100);
}
