#include "shell.h"

int _myenv(info_t *test)
{
	print_list_str(info->env);
	return (0);
}
char *_getenv(info_t *test, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

int _mysetenv(info_t *test)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

int _myunsetenv(info_t *test)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);

	return (1);
}

int populate_env_list(info_t *test)
{
	list_t *node = NULL;
	size_t i;

	for (i = 1; environ[i]; i++)
		add_node_end(&node, environ[i], 1);
	info->env = node;
	return (1);
}
