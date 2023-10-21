#include "declare.h"

/**
 * my_exit - Exits the shell.
 *
 * @info: Structure containing potential arguments. Used to maintain
 *        a consistent function prototype.
 *
 * Return: Exits with a given exit status (0) if info->argv[0] != "exit".
 */

int my_exit(info_t *info)
{
	int exit_status;

	if (info->argv[1])  /* If there is an exit argument */
	{
		exit_status = string_to_integer(info->argv[1]);

		if (exit_status == -1)
		{
			info->status = 2;
			print_error_message(info, "Illegal number: ");
			_print_error_string(info->argv[1]);
			_write_error_char('\n');
			return (1);
		}

		info->error_code = string_to_integer(info->argv[1]);
		return (-2);
	}

	info->error_code = -1;
	return (-2);
}

/**
 * my_cd - Changes the current directory of the process.
 *
 * @info: Structure containing potential arguments. Used to maintain
 *        a consistent function prototype.
 *
 * Return: Always 0.
 */

int my_cd(info_t *info)
{
	char *current_dir, *new_dir, buffer[1024];
	int chdir_result;

	current_dir = getcwd(buffer, 1024);

	if (!current_dir)
		print_string("TODO: >>getcwd failure error message here<<\n");

	if (!info->argv[1])
	{
		new_dir = get_environment_variable(info, "HOME=");

		if (!new_dir)
			chdir_result = /* TODO: What should this be? */
				chdir((new_dir = get_environment_variable(info, "PWD=")) ? new_dir : "/");
		else
			chdir_result = chdir(new_dir);
	}
	else if (str_compare(info->argv[1], "-") == 0)
	{
		if (!get_environment_variable(info, "OLDPWD="))
		{
			print_string(current_dir);
			_write_error_char('\n');
			return (1);
		}

		print_string(get_environment_variable(info, "OLDPWD="));
		_write_error_char('\n');
		chdir_result = /* TODO: What should this be? */
			chdir((new_dir = get_environment_variable(info, "OLDPWD=")) ? new_dir : "/");
	}
	else
		chdir_result = chdir(info->argv[1]);

	if (chdir_result == -1)
	{
		print_error_message(info, "can't cd to ");
		_print_error_string(info->argv[1]);
		_write_error_char('\n');
	}
	else
	{
		set_environment_variable(info, "OLDPWD", get_environment_variable(info, "PWD="));
		set_environment_variable(info, "PWD", getcwd(buffer, 1024));
	}

	return (0);
}


/**
 * my_help - Displays help information.
 *
 * @info: Structure containing potential arguments. Used to maintain
 *        a consistent function prototype.
 *
 * Return: Always 0.
 */

int my_help(info_t *info)
{
	char **argument_array;

	argument_array = info->argv;

	print_string("Help call works. Function not yet implemented.\n");

	if (0)
		print_string(*argument_array);

	return (0);
}