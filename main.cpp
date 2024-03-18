#include "lcdDisplay.hpp"

/**
 * Funkcja główna.
 */
int main()
{
	lcdDisplay.init();
	lcdDisplay.write('a');
	lcdDisplay.goTo(1, 2);
	lcdDisplay.write("Hello, world!");

	while (true) {
	}
}
