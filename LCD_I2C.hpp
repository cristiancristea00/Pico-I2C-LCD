/*******************************************************************************
 * @file LCD_I2C.hpp
 * @author Cristian Cristea
 * @date September 27, 2021
 * @brief Header file for the LCD_I2C class.
 *
 * @copyright Copyright (C) 2021 Cristian Cristea
 ******************************************************************************/

#pragma once

#include <hardware/gpio.h>
#include <hardware/i2c.h>

#include <string_view>
#include <cstdint>
#include <array>

class LCD_I2C final
{
 private:

    using byte = uint8_t;

    // Commands

    static constexpr byte CLEAR_DISPLAY = 0x01;
    static constexpr byte RETURN_HOME = 0x02;
    static constexpr byte ENTRY_MODE_SET = 0x04;
    static constexpr byte DISPLAY_CONTROL = 0x08;
    static constexpr byte CURSOR_SHIFT = 0x10;
    static constexpr byte FUNCTION_SET = 0x20;
    static constexpr byte SET_CGRAM_ADDR = 0x40;
    static constexpr byte SET_DDRAM_ADDR = 0x80;

    // Flags for display entry mode set

    static constexpr byte ENTRY_RIGHT = 0x00;
    static constexpr byte ENTRY_LEFT = 0x02;
    static constexpr byte ENTRY_SHIFT_INCREMENT = 0x01;
    static constexpr byte ENTRY_SHIFT_DECREMENT = 0x00;

    // Flags for display on/off control

    static constexpr byte DISPLAY_ON = 0x04;
    static constexpr byte DISPLAY_OFF = 0x00;
    static constexpr byte CURSOR_ON = 0x02;
    static constexpr byte CURSOR_OFF = 0x00;
    static constexpr byte BLINK_ON = 0x01;
    static constexpr byte BLINK_OFF = 0x00;

    // Flags for cursor or display shift

    static constexpr byte DISPLAY_MOVE = 0x08;
    static constexpr byte CURSOR_MOVE = 0x00;
    static constexpr byte MOVE_RIGHT = 0x04;
    static constexpr byte MOVE_LEFT = 0x00;

    // Flags for function set

    static constexpr byte MODE_8_BIT = 0x10;
    static constexpr byte MODE_4_BIT = 0x00;
    static constexpr byte LINE_2 = 0x08;
    static constexpr byte LINE_1 = 0x00;
    static constexpr byte DOTS_5x10 = 0x04;
    static constexpr byte DOTS_5x8 = 0x00;

    // Flags for backlight control

    static constexpr byte BACKLIGHT = 0x08;
    static constexpr byte NO_BACKLIGHT = 0x00;

    // Special flags

    static constexpr byte ENABLE = 0x04;
    static constexpr byte READ_WRITE = 0x02;
    static constexpr byte REGISTER_SELECT = 0x01;
    static constexpr byte COMMAND = 0x00;
    static constexpr byte CHAR = 0x01;

 public:

    static constexpr byte CUSTOM_SYMBOL_SIZE = 8;
    using array = std::array<byte, CUSTOM_SYMBOL_SIZE>;

 private:

    byte address {};
    byte columns {};
    byte rows {};
    byte backlight {};
    byte display_function {};
    byte display_control {};
    byte display_mode {};

    i2c_inst * I2C_instance {nullptr};

    /**
     * Wrapper function for SDK's internal I2C protocol write function.
     *
     * @param val Value to be written
     */
    inline void I2C_Write_Byte(byte val) const noexcept;

    /**
     * Creates a short impulse on the enable pin of the LCD.
     *
     * @param val Value to be written along with the pulse
     */
    void Pulse_Enable(byte val) const noexcept;

    /**
     * Sends a nibble of data using the I2C protocol.
     *
     * @param val Value to be sent
     */
    inline void Send_Nibble(byte val) const noexcept;

    /**
     * Send a byte of data as two nibbles using the function
     * Send_Nibble(byte val).
     *
     * @param val Value to be sent
     * @param mode The mode used when sending
     */
    inline void Send_Byte(byte val, byte mode) const noexcept;

    /**
     * Sends a command to the LCD display using the function
     * Send_Byte(byte val, byte mode).
     *
     * @param val Value to be sent
     */
    inline void Send_Command(byte val) const noexcept;

    /**
     * Sends a character to the LCD display using the function
     * Send_Byte(byte val, byte mode).
     *
     * @param val Value to be sent
     */
    inline void Send_Char(byte val) const noexcept;

    /**
     * Sends an address or line of a custom character to the LCD display using
     * the function Send_Byte(byte val, byte mode).
     *
     * @param val Value to be sent
     */
    inline void Send_Register_Select(byte val) const noexcept;

    /**
     * Establishes communication with the LCD using the I2C protocol and sets
     * its default state: backlight is off, cursor and cursor blinking is off
     * and the cursor's initial position is set at the beginning of the screen.
     */
    inline void Init() noexcept;

 public:

    /**
     * [Constructor] Initialises the I2C communication protocol using the
     * provided instance and pins and calls the display's Init() function.
     *
     * @param address The I2C address
     * @param columns The LCD's number of columns
     * @param rows The LCD's number of rows
     * @param I2C The I2C instance
     * @param SDA The serial data pin
     * @param SCL The serial clock pin
     */
    LCD_I2C(byte address, byte columns, byte rows, i2c_inst * I2C = PICO_DEFAULT_I2C_INSTANCE,
            uint SDA = PICO_DEFAULT_I2C_SDA_PIN, uint SCL = PICO_DEFAULT_I2C_SCL_PIN) noexcept;

    /**
     * Turns the display on.
     */
    void DisplayOn() noexcept;

    /**
     * Turns the display off.
     */
    void DisplayOff() noexcept;

    /**
     * Turns the backlight on.
     */
    void BacklightOn() noexcept;

    /**
     * Turns the backlight off.
     */
    void BacklightOff() noexcept;

    /**
     * Sets the backlight light on/off according to the parameter.
     *
     * @param light_on True for light on and False for off
     */
    void SetBacklight(bool light_on) noexcept;

    /**
     * Turns the cursor on.
     */
    void CursorOn() noexcept;

    /**
     * Turns the cursor off.
     */
    void CursorOff() noexcept;

    /**
     * Turns the cursor's blinking on.
     */
    void CursorBlinkOn() noexcept;

    /**
     * Turns the cursor's blinking off.
     */
    void CursorBlinkOff() noexcept;

    /**
     * Sets the text flow from left to right.
     */
    void SetTextLeftToRight() noexcept;

    /**
     * Sets the text flow from right to left.
     */
    void SetTextRightToLeft() noexcept;

    /**
     * Clears the display and sets cursor's position at the beginning of the
     * screen.
     */
    void Clear() const noexcept;

    /**
     * Sets cursor's position at the beginning of the screen.
     */
    void Home() const noexcept;

    /**
     * Sets the display's cursor to the position defined by the @p row and
     * @p column.
     *
     * @param row The vertical position (Y axis)
     * @param column The horizontal position (X axis)
     */
    void SetCursor(byte row, byte column) const noexcept;

    /**
     * Prints the character on the display at the current cursor position.
     *
     * @param character The character to be printed
     */
    void PrintChar(byte character) const noexcept;

    /**
     * Prints the string on the display starting at the current cursor position.
     *
     * @param str The string to be printed
     */
    void PrintString(std::string_view str) const noexcept;

    /**
     * Prints the custom character on the display at the current cursor
     * position, by specifying the location in memory.
     *
     * @param location The memory address
     */
    void PrintCustomChar(byte location) const noexcept;

    /**
     * Creates a custom character by specifying the location in memory to be
     * stored (8 locations maximum, starting from 0) and an array of 8 bytes.
     * @code
     * constexpr std::array BELL = {0x04, 0x0E, 0x0E, 0x1F, 0x00, 0x04, 0x00, 0x00};
     * @endcode
     *
     * @param location The memory address
     * @param char_map The byte array
     */
    void CreateCustomChar(byte location, array char_map) const noexcept;
};

