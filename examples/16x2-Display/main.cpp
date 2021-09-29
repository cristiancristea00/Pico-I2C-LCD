#include <pico/binary_info/code.h>
#include "../../LCD_I2C.hpp"
#include <memory>

int main()
{
    constexpr auto I2C = PICO_DEFAULT_I2C_INSTANCE;
    constexpr auto SDA = PICO_DEFAULT_I2C_SDA_PIN;
    constexpr auto SCL = PICO_DEFAULT_I2C_SCL_PIN;
    constexpr auto I2C_ADDRESS = 0x27;
    constexpr auto LCD_COLUMNS = 16;
    constexpr auto LCD_ROWS = 2;

    bi_decl(bi_1pin_with_name(SDA, "[SDA] LCD screen serial data pin"))
    bi_decl(bi_1pin_with_name(SCL, "[SCL] LCD screen serial clock pin"))

    auto lcd = std::make_unique<LCD_I2C>(I2C_ADDRESS, LCD_COLUMNS, LCD_ROWS, I2C, SDA, SCL);

    constexpr LCD_I2C::array HEART = {0x00, 0x0A, 0x1F, 0x1F, 0x1F, 0x0E, 0x04, 0x00};
    constexpr auto HEART_LOC = 0;
    lcd->CreateCustomChar(HEART_LOC, HEART);

    static constexpr size_t PAUSE_MS = 2000;

    lcd->BacklightOn();

    while (true)
    {
        lcd->SetCursor(0, 0);
        lcd->PrintString("RaspberryPi Pico");
        lcd->SetCursor(1, 0);
        lcd->PrintString("I2C LCD Library ");
        sleep_ms(PAUSE_MS);
        lcd->SetCursor(0, 0);
        lcd->PrintString("I2C LCD Library ");
        lcd->SetCursor(1, 0);
        lcd->PrintString("Made with love ");
        lcd->PrintCustomChar(HEART_LOC);
        sleep_ms(PAUSE_MS);
        lcd->SetCursor(0, 0);
        lcd->PrintString("Made with love ");
        lcd->PrintCustomChar(HEART_LOC);
        lcd->SetCursor(1, 0);
        lcd->PrintString("       by       ");
        sleep_ms(PAUSE_MS);
        lcd->SetCursor(0, 0);
        lcd->PrintString("       by       ");
        lcd->SetCursor(1, 0);
        lcd->PrintString("Cristian Cristea");
        lcd->PrintCustomChar(HEART_LOC);
        sleep_ms(PAUSE_MS);
    }
}
