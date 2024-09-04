//
//   命令デコーダ
//
//   copyright (c) 2024 okawa yusuke
//

constexpr uint8_t INST_IN_PINS[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

constexpr uint8_t ALU_SELECT_OUT_PINS[] = { 28, 27, 26 };
constexpr uint8_t MUX_RHS_SELECT_OUT_PINS[] = { 19, 18 };
constexpr uint8_t MUX_LHS_SELECT_OUT_PINS[] = { 17, 16 };
constexpr uint8_t DEMUX_SELECT_OUT_PINS[] = { 21, 20 };
constexpr uint8_t IMM_OUT_PINS[] = { 12, 13, 14, 15 };

void setup()
{
    Serial.begin(115200);

    for (uint8_t pin : INST_IN_PINS)
        pinMode(pin, INPUT);

    pinMode(LED_BUILTIN, OUTPUT);
}

void setMuxSelect(uint8_t select, const uint8_t* pins, uint len)
{
    for (uint i = 0; i < len; ++i)
        digitalWrite(pins[i], bitRead(select, i));
}

void loop()
{
    uint16_t inst = 0;

    // 命令値入力
    for (int i = 0; i < 10; ++i)
    {
        bitWrite(inst, i, digitalRead(INST_IN_PINS[i]));
    }

    uint8_t opecode = inst & 0b1111;

    // 4bit目以降が0のとき演算装置を使用
    if ((opecode & 0b1000 >> 3) == 0)
    {

        // [rd(2)] [rs1(2)] [rs2(2)] [opecode(4)]

        uint8_t muxLhsSelect = inst & 0b00'1100'0000 >> 6; /* rs1 */
        uint8_t muxRhsSelect = inst & 0b00'0011'0000 >> 4; /* rs2 */
        
        uint8_t aluSelect    = inst & 0b111;

        uint8_t demuxSelect  = inst & 0b11'0000'0000 >> 8; /* rd  */

        setMuxSelect(muxLhsSelect, MUX_LHS_SELECT_OUT_PINS, sizeof MUX_LHS_SELECT_OUT_PINS);
        setMuxSelect(muxRhsSelect, MUX_RHS_SELECT_OUT_PINS, sizeof MUX_RHS_SELECT_OUT_PINS);
        setMuxSelect(demuxSelect , DEMUX_SELECT_OUT_PINS  , sizeof DEMUX_SELECT_OUT_PINS  );

        for (uint i = 0; i < sizeof ALU_SELECT_OUT_PINS; ++i)
            digitalWrite(ALU_SELECT_OUT_PINS[i], bitRead(aluSelect, i));
    }

    // 即値セット
    if (opecode == 0b1000)
    {
        uint8_t imm         = inst & 0b00'1111'0000 >> 4;
        uint8_t demuxSelect = inst & 0b11'0000'0000 >> 8; /* rd  */

        setMuxSelect(demuxSelect , DEMUX_SELECT_OUT_PINS  , sizeof DEMUX_SELECT_OUT_PINS  );

        for (uint i = 0; i < sizeof IMM_OUT_PINS; ++i)
            digitalWrite(IMM_OUT_PINS[i], bitRead(imm, i));
    }

    
    {
        digitalWrite(LED_BUILTIN, millis() % 500 < 100);
    }

    Serial.print("0b");
    Serial.println(inst, BIN);

    delay(10);

}
