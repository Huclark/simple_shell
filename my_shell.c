#include "shell.h"

/**
* main - main function for shell program
* Return: Always return 0 on success.
* @argc: Argument count
* @argv: Argument vector
*/

int main(int argc, char **argv)
{
	(void)argc;
	
	return (shell_loop(argv));
}
