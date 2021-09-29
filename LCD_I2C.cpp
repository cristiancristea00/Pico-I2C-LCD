/*******************************************************************************
 * @file LCD_I2C.cpp
 * @author Cristian Cristea
 * @date September 27, 2021
 * @brief Source file for the LCD_I2C class.
 *
 * @copyright Copyright (C) 2021 Cristian Cristea
 ******************************************************************************/

#include "LCD_I2C.hpp"

LCD_I2C::LCD_I2C(byte address, byte columns, byte rows, i2c_inst * I2C, uint SDA, uint SCL) noexcept
        : address(address), columns(columns), rows(rows), backlight(NO_BACKLIGHT), I2C_instance(I2C)
{
    static constexpr size_t BAUD_RATE = 100'000;

    i2c_init(I2C, BAUD_RATE);
    gpio_set_function(SDA, GPIO_FUNC_I2C);
    gpio_set_function(SCL, GPIO_FUNC_I2C);
    gpio_pull_up(SDA);
    gpio_pull_up(SCL);
    Init();
}

inline void LCD_I2C::I2C_Write_Byte(byte val) const noexcept
{
    static byte data;

    data = val | backlight;
    i2c_write_blocking(I2C_instance, address, &data, 1, false);
}

void LCD_I2C::Pulse_Enable(byte val) const noexcept
{
    static constexpr uint16_t DELAY = 600;

    sleep_us(DELAY);
    I2C_Write_Byte(val | ENABLE);
    sleep_us(DELAY);
    I2C_Write_Byte(val & ~ENABLE);
    sleep_us(DELAY);
}

inline void LCD_I2C::Send_Nibble(byte val) const noexcept
{
    I2C_Write_Byte(val);
    Pulse_Enable(val);
}

inline void LCD_I2C::Send_Byte(byte val, byte mode) const noexcept
{
    static constexpr byte UPPER_NIBBLE = 0B1111'0000;

    static byte high;
    static byte low;

    high = val & UPPER_NIBBLE;
    low = (val << 4) & UPPER_NIBBLE;

    Send_Nibble(high | mode);
    Send_Nibble(low | mode);
}

inline void LCD_I2C::Send_Command(byte val) const noexcept
{
    Send_Byte(val, COMMAND);
}

inline void LCD_I2C::Send_Char(byte val) const noexcept
{
    Send_Byte(val, CHAR);
}

void LCD_I2C::Send_Register_Select(byte val) const noexcept
{
    Send_Byte(val, REGISTER_SELECT);
}

inline void LCD_I2C::Init() noexcept
{
    display_mode = ENTRY_LEFT | ENTRY_SHIFT_DECREMENT;
    display_function = MODE_4_BIT | LINE_2 | DOTS_5x8;
    display_control = DISPLAY_ON | CURSOR_OFF | BLINK_OFF;

    Send_Command(0x03);
    Send_Command(0x03);
    Send_Command(0x03);
    Send_Command(0x02);

    Send_Command(ENTRY_MODE_SET | display_mode);
    Send_Command(FUNCTION_SET | display_function);
    DisplayOn();
    Clear();
    Home();
}

void LCD_I2C::DisplayOn() noexcept
{
    display_control |= DISPLAY_ON;
    Send_Command(DISPLAY_CONTROL | display_control);
}

void LCD_I2C::DisplayOff() noexcept
{
    display_control &= ~DISPLAY_ON;
    Send_Command(DISPLAY_CONTROL | display_control);
}

void LCD_I2C::BacklightOn() noexcept
{
    backlight = BACKLIGHT;
    I2C_Write_Byte(backlight);
}

void LCD_I2C::BacklightOff() noexcept
{
    backlight = NO_BACKLIGHT;
    I2C_Write_Byte(backlight);
}

void LCD_I2C::SetBacklight(bool light_on) noexcept
{
    if (light_on)
    {
        BacklightOn();
    }
    else
    {
        BacklightOff();
    }
}

void LCD_I2C::CursorOn() noexcept
{
    display_control |= CURSOR_ON;
    Send_Command(DISPLAY_CONTROL | display_control);
}

void LCD_I2C::CursorOff() noexcept
{
    display_control &= ~CURSOR_ON;
    Send_Command(DISPLAY_CONTROL | display_control);
}

void LCD_I2C::CursorBlinkOn() noexcept
{
    display_control |= BLINK_ON;
    Send_Command(DISPLAY_CONTROL | display_control);
}

void LCD_I2C::CursorBlinkOff() noexcept
{
    display_control &= ~BLINK_ON;
    Send_Command(DISPLAY_CONTROL | display_control);
}

void LCD_I2C::SetTextLeftToRight() noexcept
{
    display_mode |= ENTRY_LEFT;
    Send_Command(ENTRY_MODE_SET | display_mode);
}

void LCD_I2C::SetTextRightToLeft() noexcept
{
    display_mode &= ~ENTRY_LEFT;
    Send_Command(ENTRY_MODE_SET | display_mode);
}

void LCD_I2C::Clear() const noexcept
{
    Send_Command(CLEAR_DISPLAY);
}

void LCD_I2C::Home() const noexcept
{
    Send_Command(RETURN_HOME);
}

void LCD_I2C::SetCursor(byte row, byte column) const noexcept
{
    static const std::array ROW_OFFSETS = {0x00, 0x40, 0x00 + columns, 0x40 + columns};

    row = std::min(rows, row);
    column = std::min(columns, column);
    Send_Command(SET_DDRAM_ADDR | (ROW_OFFSETS.at(row) + column));
}

void LCD_I2C::PrintChar(byte character) const noexcept
{
    Send_Char(character);
}

void LCD_I2C::PrintString(std::string_view str) const noexcept
{
    for (char const CHARACTER: str)
    {
        PrintChar(CHARACTER);
    }
}

void LCD_I2C::PrintCustomChar(byte location) const noexcept
{
    Send_Register_Select(location);
}

void LCD_I2C::CreateCustomChar(byte location, array const char_map) const noexcept
{
    static constexpr byte MAX_CUSTOM_CHARS = 8;

    location = std::min(MAX_CUSTOM_CHARS, location);
    Send_Command(SET_CGRAM_ADDR | (location << 3));
    for (size_t i = 0; i < CUSTOM_SYMBOL_SIZE; ++i)
    {
        Send_Register_Select(char_map.at(i));
    }
}
