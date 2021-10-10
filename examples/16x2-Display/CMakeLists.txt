add_executable(16x2_display main.cpp ../../LCD_I2C.cpp)

# Add program info
pico_set_program_name(16x2_display "Liquid Crystal Display I2C Library - 16x2 LCD Example")
pico_set_program_version(16x2_display "1.0.2")
pico_set_program_url(16x2_display "https://github.com/cristiancristea00/Pico-I2C-LCD/tree/main/examples/16x2-Display")
pico_set_program_description(16x2_display "Copyright (c) 2021 Cristian Cristea")

# Disable serial
pico_enable_stdio_uart(16x2_display 0)
pico_enable_stdio_usb(16x2_display 0)

# Add the libraries to the build
target_link_libraries(16x2_display pico_stdlib hardware_i2c)

# Add pico extras
pico_add_extra_outputs(16x2_display)

# Set float and double implementation
pico_set_float_implementation(16x2_display pico)
pico_set_double_implementation(16x2_display pico)
