#include <term/term.h>

static volatile struct limine_terminal_request terminal_request = {
    .id = LIMINE_TERMINAL_REQUEST,
    .revision = 0
};

struct limine_terminal *terminal;

void term_print(const char* str)
{
	while(*str)
	{
		term_print_char(*str);
		str++;
	}
}
void term_print_char(const char ch)
{
	/* Converts the char passed into a string */
	char to_print[2] = {ch, '\0'};
	terminal_request.response->write(terminal, to_print, 1);
}
void term_printn(const char* str, size_t len)
{
	terminal_request.response->write(terminal, str, len);
}
void term_init()
{
	/* Checks if the terminal even exists, if it doesn't hang */
	if (terminal_request.response == NULL || terminal_request.response->terminal_count < 1)
	{
        hang();
    }

	/* Grab a limine terminal */
	terminal = terminal_request.response->terminals[0];
	
}