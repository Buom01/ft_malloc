#include "malloc.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	printf("Using pagesize value: %ld\n", (sysconf(_SC_PAGESIZE)));
	if (argc < 3)
	{
		printf("Usage: ./main INITIAL_BUFFER REALLOC_BUFFER\n");
		exit(1);
	}

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
