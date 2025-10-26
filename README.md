# ft_Malloc

A rather UNIX project

## What's done ?
- All the project
- Bonus: Thread safe
- Bonus: Kind of `show_alloc_mem_ex()`
- Bonus: Defragment

## Compile the lib
`make`

## Use the provided `main.c`
```
$ clang main.c -Isrcs -L. -lft_malloc -o main
$ ./main A B
```

## Attention point
- "Each zone must contain at least 100 allocations.": An same zone must contain at least 100 allocations.
- Maybe you think that you may keep 1 more allocation for performance ? For instance at least one zone of each ? You would fail the correction.
- The correction subject use unclear tests and is overcomplicated.
- Provided tests don't really explain why you failed.

## External tester
I use https://github.com/c-bertran/malloc/
Copy `tests` into the folder

If you are on 42's dump:
	Double free are not testables with it, so
	Edit srcs/edge_cases.c
	Empty `test_double_free`

Edit tests/Makefile to update `-I` and `-L` to srcs

Run `make` into tests
