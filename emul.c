#include "shell.h"

/**
 * _myex - exits the shell
 * @inf: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int _myex(info_v *inf)
{
	int excheck;

	if (inf->argb[1])  /* If there is an exit arguement */
	{
		excheck = _erratoia(inf->argb[1]);
		if (excheck == -1)
		{
			inf->stat = 2;
			print_err(inf, "Illegal number: ");
			_heputs(inf->argb[1]);
			_heputchar('\n');
			return (1);
		}
		inf->error_num = _erratoia(inf->argb[1]);
		return (-2);
	}
	inf->error_num = -1;
	return (-2);
}

/**
 * _myhelpo - changes the current directory of the process
 * @inf: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _myhelpo(info_v *inf)
{
	char **arg_arr;

	arg_arr = inf->argb;
	_putsa("help call works. Function not yet implemented \n");
	if (0)
		_putsa(*arg_arr); /* temp att_unused workaround */
	return (0);
}


/**
 * _mycmd - changes the current directory of the process
 * @inf: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _mycmd(info_v *inf)
{
	char *s, *dir, buff[1024];
	int chdir_ret;

	s = getcwd(buff, 1024);
	if (!s)
		_putsa("TODO: >>getcwd failure emsg here<<\n");
	if (!inf->argb[1])
	{
		dir = _getenva(inf, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = _getenva(inf, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcompare(inf->argb[1], "-") == 0)
	{
		if (!_getenva(inf, "OLDPWD="))
		{
			_putsa(s);
			_putchar('\n');
			return (1);
		}
		_putsa(_getenva(inf, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = _getenva(inf, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(inf->argb[1]);
	if (chdir_ret == -1)
	{
		print_err(inf, "can't cd to ");
		_heputs(inf->argb[1]), _heputchar('\n');
	}
	else
	{
		_setenva(inf, "OLDPWD", _getenva(inf, "PWD="));
		_setenva(inf, "PWD", getcwd(buff, 1024));
	}
	return (0);
}


