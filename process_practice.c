#include "./philo_bonus/include/philo_bonus.h"

int	main(void)
{
	int pids[5];
	int	n;
	int	i;

	i = 0;
	n = 5;
	while (i < n)
	{
		pids[i] = fork();

		if (pids[i] < 0)
			return (printf("Error creating process %d\n", i), 1);
		else if (pids[i] == 0)
		{
			printf("Child %d\n", i);
			return (0);
		}
		else
		{
		}
		i++;
	}
	printf("Parent\n");
	return (0);
}