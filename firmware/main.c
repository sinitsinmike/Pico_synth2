#include <tusb.h>
#include <pico/stdlib.h>
#include <pico-synth/tui.h>

static ps_tui_t tui = {
    .i2c = {
        .i2c = i2c1,
        .baudrate = 400000,
        .basepin = 2,
    },

    .eeprom = {
        .ic = PS_TUI_EEPROM_24LC512,
    },

    .encoder = {
        .button = 9,
        .a = 10,
        .b = 11,
        .button_debounce_us = 250000,
        .rotate_debounce_us = 2000,
    },

    .oled = {
        .controller = PS_TUI_OLED_SH1106,
    },
};


int
main(void)
{
    set_sys_clock_khz(133000, true);
    stdio_uart_init_full(uart0, 115200, 16, 17);
    tusb_init();

    hard_assert(ps_tui_init(&tui) == PICO_OK);

    while (1) {
        tud_task();
        hard_assert(ps_tui_task(&tui) == PICO_OK);
    }

    return 0;
}
