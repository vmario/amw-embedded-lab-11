#include "lcdDisplay.hpp"

/**
 * Funkcja główna.
 */
int main()
{
	lcdDisplay.init();
	lcdDisplay.goTo(0, 0);
	lcdDisplay.write('a');

	while (true) {
	}
}
