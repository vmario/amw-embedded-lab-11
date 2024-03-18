#include <avr/io.h>

#define LCD_RS_DIR DDRB
#define LCD_RS_PORT PORTB
#define LCD_RS_BIT _BV(PB0)

#define LCD_E_DIR DDRB
#define LCD_E_PORT PORTB
#define LCD_E_BIT _BV(PB1)

#define LCD_DB_DIR DDRD
#define LCD_DB_PORT PORTD
#define LCD_DB_OFFSET PD4
