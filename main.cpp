#include <pico/binary_info/code.h>
#include "LCD_I2C.hpp"
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
}
