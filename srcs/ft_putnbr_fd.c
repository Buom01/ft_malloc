#include "malloc.h"
#include "libft.h"


char	*ft_itoa_noalloc(int n)
{
	int			positive;
	long		posinb;
	int			posinbcpy;
	size_t		strlen;
	static char	str[16];

	positive = (n >= 0);
	strlen = 2 + !positive;
	posinb = (long)n * positive + -1 * !positive * (long)n;
	posinbcpy = posinb;
	while (posinbcpy / 10)
	{
		posinbcpy /= 10;
		strlen++;
	}
	str[--strlen] = '\0';
	while (strlen - !positive > 0)
	{
		str[--strlen] = '0' + (posinb % 10);
		posinb /= 10;
	}
	return (str);
}

void	ft_putnbr_fd_noalloc(int n, int fd)
{
	ft_putstr_fd(ft_itoa_noalloc(n), fd);
}
