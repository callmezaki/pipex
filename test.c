#include<unistd.h>
#include<stdio.h>
#include <sys/wait.h>

int main()
{
	int id = fork();
	int n;
	if (id == 0)
		n = 1;
	else
		n = 6;
	// if (id != 0)
	wait(NULL);
	int i;
	i = n;
	while(i < n +5)
	{
		printf("%d", i);
		i++;
	}
	return(0);
}