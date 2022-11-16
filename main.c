#include "shell.h"

/**
 * main - Simple Shell Project.
 * @ac: main function parameter arg count
 * @av:  main function parameter arg vector
 * Return: 0 for success, 1 for error
 */
int main(int ac, char **av)
{
	info_t it[] = { INFO_INIT };
	int id = 2;

	asm("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (id)
		: "r" (id));

	if (ac == 2)
	{
		id = open(av[1], O_RDONLY);
		if (id == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(av[0]);
				_eputs(": 0: Can't open ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		it->readfd = id;
	}
	populate_env_list(it);
	read_history(it);
	hsh(it, av);
	return (EXIT_SUCCESS);
}
