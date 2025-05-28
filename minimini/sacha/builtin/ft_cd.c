#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "builtin.h"

char *ft_getenv(char *var, char **env_copy)
{
	size_t len;
	int i = 0;
	char *entry;

	if (!var)
		return NULL;
	len = ft_strlen(var);
	while (env_copy[i])
	{
		entry = env_copy[i];
		if (ft_strncmp(entry, var, len) == 0 && entry[len] == '=')
			return entry + len + 1;
		i++;
	}
	return NULL;
}

int ft_cd(char **str, t_shell *shell)
{
	char	*pwd;
	char	*current_directory;
	char	cwd[1024];

	pwd = ft_getenv("PWD", shell->env);
	if (!str[1]) {
		ft_putstr_fd("minishell: cd: missing argument (absolute or relative path required)\n", 2);
		update_env("_", "cd", shell->env);
		return 1;
	}
	if (str[2]) {
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		update_env("_", str[ft_strsize(str) - 1], shell->env);
		return 1;
	}
	if (chdir(str[1]) != 0) {
		perror("minishell: cd");
		update_env("_", str[ft_strsize(str) - 1], shell->env);
		return 1;
	}
	update_env("_", str[ft_strsize(str) - 1], shell->env);
	update_env("OLDPWD", pwd, shell->env);
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		update_env("PWD", cwd, shell->env);    
	return 0;
}

int main(int argc, char **argv, char **envp)
{
	char cwd[1024];
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (1);
	shell->env = ft_strdup_array(envp);
	shell->exit_status = 0;

	if (ft_cd(argv, shell) != 0)
		return 1;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("Current directory: %s\n", cwd);
	else
		perror("getcwd");
	return 0;
}