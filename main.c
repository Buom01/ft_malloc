#include "libft_malloc.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
	show_alloc_mem();
	printf("Allocating %lu bytes for `%s`\n", strlen(argv[1]) + 1,  argv[1]);	

	void *ptr = malloc(strlen(argv[1]) + 1);


	printf("Allocated at %p\n", ptr);

	if (!ptr)
		return 1;

	memcpy(ptr, argv[1], strlen(argv[1]) + 1);

	printf("Copyed as: \"%s\"\n", (char *)ptr);


	show_alloc_mem();	

	ptr = realloc(ptr, strlen(argv[2]) + 1);


	printf("Allocated realloc at %p\n", ptr);

	if (!ptr)
		return 1;

	memcpy(ptr, argv[2], strlen(argv[2]) + 1);

	printf("Copyed realloc as: \"%s\"\n", (char *)ptr);


	show_alloc_mem();

	free(ptr);
}
