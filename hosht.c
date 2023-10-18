#include "shell.h"

/**
 * hosht - main shell loop
 * @inf: the parameter & return info struct
 * @aa: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hosht(info_v *inf, char **aa)
{
	ssize_t rr = 0;
	int builtin_rret = 0;

	while (rr != -1 && builtin_rret != -2)
	{
		clear_inf(inf);
		if (interact(inf))
			_putsa("$ ");
		_heputchar(BUF_FLUSH);
		rr = have_input(inf);
		if (rr != -1)
		{
			set_inf(inf, aa);
			builtin_rret = find_blt(inf);
			if (builtin_rret == -1)
				findcmd(inf);
		}
		else if (interact(inf))
			_putchar('\n');
		free_inf(inf, 0);
	}
	write_hist(inf);
	free_inf(inf, 1);
	if (!interact(inf) && inf->stat)
		exit(inf->stat);
	if (builtin_rret == -2)
	{
		if (inf->error_num == -1)
			exit(inf->stat);
		exit(inf->error_num);
	}
	return (builtin_rret);
}

/**
 * find_blt - finds a builtin command
 * @inf: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int find_blt(info_v *inf)
{
	int i, built_in_rret = -1;
	bltin_v builtintbl[] = {
		{"exit", _myex},
		{"env", _myenva},
		{"help", _myhelpo},
		{"history", _myhist},
		{"setenv", _mysetenva},
		{"unsetenv", _myunsetenva},
		{"cd", _mycmd},
		{"alias", _myaliasa},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcompare(inf->argb[0], builtintbl[i].type) == 0)
		{
			inf->line_c++;
			built_in_rret = builtintbl[i].fun(inf);
			break;
		}
	return (built_in_rret);
}

/**
 * findcmd - finds a command in PATH
 * @inf: the parameter & return info struct
 *
 * Return: void
 */
void findcmd(info_v *inf)
{
	char *path = NULL;
	int i, k;

	inf->pth = inf->argb[0];
	if (inf->linec_f == 1)
	{
		inf->line_c++;
		inf->linec_f = 0;
	}
	for (i = 0, k = 0; inf->arga[i]; i++)
		if (!is_dell(inf->arga[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = findpth(inf, _getenva(inf, "PATH="), inf->argb[0]);
	if (path)
	{
		inf->pth = path;
		forkcmd(inf);
	}
	else
	{
		if ((interact(inf) || _getenva(inf, "PATH=")
			|| inf->argb[0][0] == '/') && iscmd(inf, inf->argb[0]))
			forkcmd(inf);
		else if (*(inf->arga) != '\n')
		{
			inf->stat = 127;
			print_err(inf, "not found\n");
		}
	}
}

/**
 * forkcmd - forks a an exec thread to run cmd
 * @inf: the parameter & return info struct
 *
 * Return: void
 */
void forkcmd(info_v *inf)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(inf->pth, inf->argb, get_environa(inf)) == -1)
		{
			free_inf(inf, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(inf->stat));
		if (WIFEXITED(inf->stat))
		{
			inf->stat = WEXITSTATUS(inf->stat);
			if (inf->stat == 126)
				print_err(inf, "Permission denied\n");
		}
	}
}

