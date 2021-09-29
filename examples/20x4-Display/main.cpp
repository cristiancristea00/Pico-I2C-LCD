#include <pico/binary_info/code.h>
#include "../../LCD_I2C.hpp"
#include <memory>

int main()
{
    constexpr auto I2C = PICO_DEFAULT_I2C_INSTANCE;
    constexpr auto SDA = PICO_DEFAULT_I2C_SDA_PIN;
    constexpr auto SCL = PICO_DEFAULT_I2C_SCL_PIN;
    constexpr auto I2C_ADDRESS = 0x27;
    constexpr auto LCD_COLUMNS = 20;
    constexpr auto LCD_ROWS = 4;

    bi_decl(bi_1pin_with_name(SDA, "[SDA] LCD screen serial data pin"))
    bi_decl(bi_1pin_with_name(SCL, "[SCL] LCD screen serial clock pin"))

    auto lcd = std::make_unique<LCD_I2C>(I2C_ADDRESS, LCD_COLUMNS, LCD_ROWS, I2C, SDA, SCL);

    constexpr LCD_I2C::array HEART = {0x00, 0x0A, 0x1F, 0x1F, 0x1F, 0x0E, 0x04, 0x00};
    constexpr auto HEART_LOC = 0;
    lcd->CreateCustomChar(HEART_LOC, HEART);

    lcd->BacklightOn();
    lcd->SetCursor(0, 1);
    lcd->PrintString("Raspberry Pi Pico");
    lcd->SetCursor(1, 2);
    lcd->PrintString("I2C LCD Library");
    lcd->SetCursor(2, 2);
    lcd->PrintString("Made with love ");
    lcd->PrintCustomChar(HEART_LOC);
    lcd->SetCursor(3, 0);
    lcd->PrintString("by Cristian Cristea");
}
