add_executable(20x4_display main.cpp ../../LCD_I2C.cpp)

# Add program info
pico_set_program_name(20x4_display "Liquid Crystal Display I2C Library - 20x4 LCD Example")
pico_set_program_version(16x2_display "1.0.1")
pico_set_program_url(20x4_display "https://github.com/cristiancristea00/Pico-I2C-LCD/tree/main/examples/20x4-Display")
pico_set_program_description(20x4_display "Copyright (c) 2021 Cristian Cristea")

# Disable serial
pico_enable_stdio_uart(20x4_display 0)
pico_enable_stdio_usb(20x4_display 0)

# Add the libraries to the build
target_link_libraries(20x4_display pico_stdlib hardware_i2c)

# Add pico extras
pico_add_extra_outputs(20x4_display)

# Set float and double implementation
pico_set_float_implementation(20x4_display pico)
pico_set_double_implementation(20x4_display pico)
