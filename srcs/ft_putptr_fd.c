#include "libft_malloc.h"

char	*ft_ptrtoa(void *ptr)
{
	static char	str[16];
	size_t	ptrcpy;
	size_t	strlen;

	strlen = 2;
	ptrcpy = (size_t)ptr;
	while (ptrcpy / 16)
	{
		ptrcpy /= 16;
		strlen++;
	}
	str[strlen] = '\0';
	ptrcpy = (size_t)ptr;
	while (strlen > 0)
	{
		str[--strlen] = "0123456789ABCDEF"[ptrcpy % 16];
		ptrcpy /= 16;
	}
	return (str);
}

void	ft_putptr_fd(void *ptr, int fd)
{
	ft_putstr_fd(ft_ptrtoa(ptr), fd);
}
