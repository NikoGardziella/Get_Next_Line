#include "get_next_line.h"
#include <stdio.h>
#include <time.h>
#include <fcntl.h>

int	main(void)
{
	char		*line;
	int			fd;
	int			res;

	clock_t		start;
	clock_t		end;
	double		time;

	fd = open("bible.txt", O_RDONLY);
	start = clock();
	while (1)
	{
		res = get_next_line(fd, &line);
		printf("%d, %s\n", res, line);
		if (res <= 0)
			break ;
		free(line);
	}
	end = clock();
	time = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("\nTime: %f\n", time);

	//printf("-------\nTesting stdin:\n");
	//while (1)
	//{
	//	get_next_line(1, &line);
	//	printf("%s\n", line);
	//}

	//system("leaks test_gnl");
	return (0);
}
