#include "shell.h"

/**
 * main - main function for shell program
 * @argc: Number of argument vectors
 * @argv: Argument vector
 * Return: 0 if successful or 1 if otherwise
*/

int main(int argc, char **argv)
{
	shell_loop();

	return (EXIT_SUCCESS);
}
