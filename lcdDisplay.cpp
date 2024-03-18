#include "lcdDisplay.hpp"

#include "lcdDisplayBus.hpp"
#include "lcdDisplayInstruction.hpp"

#include <util/delay.h>

const LcdDisplay lcdDisplay;

/**
 * Instancja sterownika szyny danych.
 */
const LcdDisplayBus bus;

void LcdDisplay::init() const
{
	bus.initGpio();
	bus.initByInstruction();
	bus.init4Bit();

	bus.instructionWrite(FUNCTION_SET | FUNCTION_SET_DUAL_LINE);
	bus.instructionWrite(DISPLAY_CONTROL);
	bus.instructionWrite(CLEAR_DISPLAY);
	bus.instructionWrite(ENTRY_MODE_SET | ENTRY_MODE_SET_INCREMENT);
	bus.instructionWrite(DISPLAY_CONTROL | DISPLAY_CONTROL_DISPLAY | DISPLAY_CONTROL_CURSOR | DISPLAY_CONTROL_BLINK);
}

void LcdDisplay::write(char symbol) const
{
	bus.dataWrite(symbol);
}

void LcdDisplay::write(const char* text) const
{
}

void LcdDisplay::goTo(uint8_t line, uint8_t column) const
{
}

void LcdDisplay::addSymbol(const uint8_t* symbol, uint8_t position) const
{
}
