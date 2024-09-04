//
//   演算装置
//
//   copyright (c) 2024 okawa yusuke
//

constexpr uint8_t RHS_IN_PINS[] = { 7, 6, 5, 4 };
constexpr uint8_t LHS_IN_PINS[] = { 3, 2, 1, 0 };
constexpr uint8_t SELECT_IN_PINS[] = { 16, 17, 18 };
constexpr uint8_t RESULT_OUT_PINS[] = { 8, 9, 10, 11 };

void setup()
{
    Serial.begin(115200);

    for (uint8_t pin : RHS_IN_PINS)
        pinMode(pin, INPUT);
    for (uint8_t pin : LHS_IN_PINS)
        pinMode(pin, INPUT);
    for (uint8_t pin : SELECT_IN_PINS)
        pinMode(pin, INPUT);
        
    for (uint8_t pin : RESULT_OUT_PINS)
        pinMode(pin, OUTPUT);

    pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
    uint8_t rhs = 0;
    for (uint i = 0; i < sizeof RHS_IN_PINS; ++i)
        bitWrite(rhs, i, digitalRead(RHS_IN_PINS[i]));

    uint8_t lhs = 0;
    for (uint i = 0; i < sizeof LHS_IN_PINS; ++i)
        bitWrite(lhs, i, digitalRead(LHS_IN_PINS[i]));

    uint8_t select = 0;
    for (uint i = 0; i < sizeof SELECT_IN_PINS; ++i)
        bitWrite(select, i, digitalRead(SELECT_IN_PINS[i]));

    int results[]
    {
        rhs + lhs,
        rhs - lhs,
        rhs * lhs,
        rhs / lhs,
        rhs | lhs,
        rhs & lhs,
        rhs ^ lhs,
    };
    uint8_t result = results[select];  // MUX

    for (uint i = 0; i < sizeof RESULT_OUT_PINS; ++i)
        digitalWrite(RESULT_OUT_PINS[i], bitRead(result, i));

    digitalWrite(LED_BUILTIN, millis() % 500 < 100);
}
