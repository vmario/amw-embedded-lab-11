#include "lcdPinout.hpp"

#include <avr/interrupt.h>
#include <util/delay.h>

constexpr uint8_t NIBBLE_MASK{0x0f}; ///< Maska półbajtu.

/**
 * Opcje komendy Entry Mode.
 */
enum ENTRY_MODE_OPTION {
	ENTRY_MODE_OPTION_INCREMENT = 0x02, ///< Inkrementacja adresacji.
};

/**
 * Opcje komendy Display Control.
 */
enum DISPLAY_CONTROL_OPTION {
	DISPLAY_CONTROL_OPTION_CURSOR_BLINK = 0x01, ///< Mrugający kursor.
	DISPLAY_CONTROL_OPTION_CURSOR_ON = 0x02, ///< Widoczny kursors.
	DISPLAY_CONTROL_OPTION_DISPLAY_ON = 0x04, ///< Wyświetlacz włączony.
};

/**
 * Opcje komendy Function Set.
 */
enum FUNCTION_SET_OPTION {
	FUNCTION_SET_OPTION_DUAL_LINE = 0x08, ///< Wyświetlacz z dwoma liniami tekstu.
};

/**
 * Pętla główna.
 */
void mainLoop()
{
}

/**
 * Inicjalizacja przerwań.
 */
void interruptsInitialize()
{
}

/**
 * Parametry interfejsu komunikacyjnego.
 */
enum INTERFACE_LENGTH {
	INTERFACE_LENGTH_4BIT = 0x02, ///< Interfejs 4-bitowy.
	INTERFACE_LENGTH_8BIT = 0x03, ///< Interfejs 8-bitowy.
};

void nibbleWrite(uint8_t value)
{
	constexpr uint8_t LCD_DB_PORT_MASK = (~(NIBBLE_MASK << LCD_DB_OFFSET)) & 0xff;

	LCD_E_PORT |= LCD_E_BIT;
	LCD_DB_PORT = (value << LCD_DB_OFFSET) | (LCD_DB_PORT & LCD_DB_PORT_MASK);
	_delay_us(1);
	LCD_E_PORT &= ~LCD_E_BIT;
	_delay_us(1);
}

void byteWrite(uint8_t value)
{
	nibbleWrite(value >> 4);
	nibbleWrite(value);
}

void commandWrite(uint8_t value)
{
	LCD_RS_PORT &= ~LCD_RS_BIT;
	byteWrite(value);
}

void dataWrite(uint8_t value)
{
	LCD_RS_PORT |= LCD_RS_BIT;
	byteWrite(value);
	_delay_us(37);
}
/**
 * Funkcja główna.
 */
int main()
{
	// init GPIO
	LCD_DB_DIR |= NIBBLE_MASK << LCD_DB_OFFSET;
	LCD_E_DIR |= LCD_E_BIT;
	LCD_RS_DIR |= LCD_RS_BIT;

	// init logic
	_delay_ms(40);
	nibbleWrite(INTERFACE_LENGTH_8BIT);
	_delay_us(4100);
	nibbleWrite(INTERFACE_LENGTH_8BIT);
	_delay_us(100);
	nibbleWrite(INTERFACE_LENGTH_8BIT);
	_delay_us(37);

	// init 4bit
	nibbleWrite(INTERFACE_LENGTH_4BIT);
	_delay_ms(37);

#if 0
	CommandFunctionSet(FUNCTION_SET_OPTION_DUAL_LINE).write();
	CommandDisplayControl().write();
	CommandClear().write();
	CommandEntryMode(ENTRY_MODE_OPTION_INCREMENT).write();
	CommandDisplayControl(DISPLAY_CONTROL_OPTION_DISPLAY_ON | DISPLAY_CONTROL_OPTION_CURSOR_ON).write();
#endif
	commandWrite(0x20 | FUNCTION_SET_OPTION_DUAL_LINE);
	_delay_ms(100);
	commandWrite(0x08);
	_delay_ms(100);
	commandWrite(0x01);
	_delay_ms(100);
	commandWrite(0x04 | ENTRY_MODE_OPTION_INCREMENT);
	_delay_ms(100);
	commandWrite(0x08 | DISPLAY_CONTROL_OPTION_DISPLAY_ON | DISPLAY_CONTROL_OPTION_CURSOR_ON);
	_delay_ms(100);

	// CommandSetDdramAddress(line, column).write();
	uint8_t line{1};
	uint8_t column{2};
	commandWrite(0x80 | ((line * 0x40 + column) & 0x7f));
	_delay_ms(100);

	dataWrite('b');

	while (true) {
	}
}
