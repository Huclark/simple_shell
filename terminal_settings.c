#include "shell.h"

/**
 * set_terminal_mode - Sets the terminal mode to non-canonical (raw) mode
 * @term: Pointer to term_settings struct
*/
void set_terminal_mode(terminal_set *term)
{
	 struct termios new_settings;

	 /* Get the original terminal settings and store them in the struct */
	 tcgetattr(STDIN_FILENO, &(term->original));

	 /* Copy the original settings to a new structure */
	 new_settings.c_lflag &= ~ICANON;

	 /* Disable echo */
	 new_settings.c_lflag &= ~ECHO;

	 /* Set the new terminal settings */
	 tcsetattr(STDIN_FILENO, TCSANOW, &new_settings);
}


/**
 * reset_terminal_mode - Resets the terminal mode to the original settings
 * @term: Pointer to term_settings struct
*/
void reset_terminal_mode(struct term_settings *term)
{
	/* Restore the original terminal settings from the struct */
	tcsetattr(STDIN_FILENO, TCSANOW, &(term->original));
}
