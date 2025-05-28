#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>


int main (int argc, char **argv, char **env)
{
	char *arr[] = {"cat", "-e out", NULL};

	execve("/usr/bin/cat", arr, env);
}
