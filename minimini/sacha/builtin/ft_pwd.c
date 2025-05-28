#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include "builtin.h"

int ft_pwd(char **str, char **env)
{
    char cwd[1024];

    update_env("_", str[ft_strsize(str) - 1], env);
    if (getcwd(cwd, sizeof(cwd)) != NULL)
        return (printf("%s\n", cwd), 0);
    else
        return (perror("pwd"), 1);
}

int main(int argc, char **argv, char **envp)
{
    int return_status;
	char **env;

	env = ft_strdup_array(envp);

    return_status = ft_pwd(argv, env);
    printf("code retour: %d\n", return_status);
}
