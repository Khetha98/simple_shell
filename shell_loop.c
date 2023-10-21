#include "declare.h"

/**
 * shell_loop - Main shell loop.
 * @info: Pointer to the info struct for parameters and return value.
 * @av: Argument vector from the main() function.
 *
 * Return: 0 on success, 1 on error, or an error code.
 */

int shell_loop(info_t *info, char **av)
{
	ssize_t read_result = 0;
	int builtin_return = 0;

	while (read_result != -1 && builtin_return != -2)
	{
		initialize_info(info);
		if (is_shell_interactive(info))
			print_string("$ ");
		_write_error_char(BUFFER_FLUSH);
		read_result = get_input(info);
		if (read_result != -1)
		{
			setupInfo(info, av);
			builtin_return = find_builtin(info);
			if (builtin_return == -1)
				find_command(info);
		}
		else if (is_shell_interactive(info))
			write_character('\n');
		cleanupInfo(info, 0);
	}
	writeHistory(info);
	cleanupInfo(info, 1);
	if (!is_shell_interactive(info) && info->status)
		exit(info->status);
	if (builtin_return == -2)
	{
		if (info->error_code == -1)
			exit(info->status);
		exit(info->error_code);
	}
	return builtin_return;
}

/**
 * find_builtin - Find a built-in command.
 * @info: Pointer to the info struct for parameters and return value.
 *
 * Return: -1 if the built-in is not found, 0 if the built-in executed successfully,
 * 1 if the built-in was found but not successful, -2 if the built-in signals exit().
 */

int find_builtin(info_t *info)
{
	int i, built_in_return = -1;
	builtin_table builtintbl[] = {
		{"exit", my_exit},
		{"env", my_environment},
		{"help", my_help},
		{"history", my_history},
		{"setenv", my_set_environment_variable},
		{"unsetenv", my_unset_environment_variable},
		{"cd", my_cd},
		{"alias", my_alias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (str_compare(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_return = builtintbl[i].func(info);
			break;
	}
	return built_in_return;
}

/**
 * find_command - Find a command in the PATH.
 * @info: Pointer to the info struct for parameters and return value.
 *
 * Return: void
 */

void find_command(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->line_count_flag == 1)
	{
		info->line_count++;
		info->line_count_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!is_character_delimiter(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = findCommandInPath(info, get_environment_variable(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_command(info);
	}
	else
	{
		if ((is_shell_interactive(info) || get_environment_variable(info, "PATH=")
			|| info->argv[0][0] == '/') && isExecutableCommand(info, info->argv[0]))
			fork_command(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error_message(info, "not found\n");
		}
	}
}

/**
 * fork_command - Fork a new process to run a command.
 * @info: Pointer to the info struct for parameters and return value.
 *
 * Return: void
 */

void fork_command(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environment(info)) == -1)
		{
			cleanupInfo(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error_message(info, "Permission denied\n");
		}
	}
}