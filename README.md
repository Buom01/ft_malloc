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
```Shell
$ clang -Iincludes -L. -lft_malloc main.c -o main
$ LD_LIBRARY_PATH=$(pwd):$LD_LIBRARY_PATH valgrind ./main initial_buffer the_reallocated_buffer
```

## Attention point
- "Each zone must contain at least 100 allocations.": An same zone must contain at least 100 allocations.
- Maybe you think that you may keep 1 more allocation for performance ? For instance at least one zone of each ? You would fail the correction.
- The correction subject use unclear tests and is overcomplicated.
- Provided tests don't really explain why you failed.

## External tester
### Manually
I use https://github.com/c-bertran/malloc/
Copy `tests` into the folder
Run `make` into tests

### Command
`git clone https://github.com/c-bertran/malloc/ malloc_tests && cp -r malloc_tests/tests . && cd tests && make`