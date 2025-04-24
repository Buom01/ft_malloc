#include "libft_malloc.h"
#include <stdio.h>

int main(int argc, char **argv)
{
	show_alloc_mem();
	printf("Allocating %lu bytes for `%s`\n", strlen(argv[1]) + 1,  argv[1]);	

	void *ptr = ft_malloc(strlen(argv[1]) + 1);

	show_alloc_mem();	

	printf("Allocated at %p\n", ptr);

	if (!ptr)
		return 1;

	memcpy(ptr, argv[1], strlen(argv[1]) + 1);

	printf("Copyed as: \"%s\"\n", (char *)ptr);

}
