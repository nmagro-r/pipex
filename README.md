*This project has been created as part of the 42 curriculum by nmagro-r.*

# pipex

What a shell does when you type a pipe, written by hand in C with `pipe`, `fork`, `dup2` and `execve`.

```bash
./pipex infile "cmd1" "cmd2" outfile
# does the same as
< infile cmd1 | cmd2 > outfile
```

## Description

The program opens two files, connects two commands with a pipe and runs them at the same time as separate processes:

```
infile ──> [ cmd1 ] ──pipe──> [ cmd2 ] ──> outfile
```

It covers the mandatory part of the project: exactly two commands. Their arguments are split on spaces, so quoted arguments are not supported.

## Instructions

Requires a POSIX system, `make` and a C compiler. [Libft](https://github.com/nmagro-r/Libft) lives in its own repository and comes in as a submodule:

```bash
git clone --recurse-submodules https://github.com/nmagro-r/pipex.git
cd pipex
make
```

Try it:

```bash
printf 'apple\nbanana\ncherry\navocado\n' > in.txt
./pipex in.txt "grep a" "wc -l" out.txt
cat out.txt
```

`out.txt` contains `3`, the same result as `< in.txt grep a | wc -l`.

## How it works

1. **Open the files.** `infile` for reading and `outfile` for writing, created or emptied if needed.
2. **Create the pipe.** `pipe` returns two file descriptors: what goes into one comes out of the other.
3. **Fork twice.** One child for each command.
4. **Rewire each child.** With `dup2`, the first child reads from `infile` and writes into the pipe, and the second reads from the pipe and writes into `outfile`. The commands never know; they just use standard input and output.
5. **Find and run the command.** A name containing `/` is used as a path. Otherwise it is searched for in the directories of `PATH`, and `execve` replaces the child with it. If it cannot be found, the child prints `command not found` and exits with status 127.
6. **Wait.** The parent closes its copies of the pipe, waits for both children and exits with the status of the last command, as a shell does.

The detail that matters most is closing every unused descriptor. `wc -l` only finishes when it reads end-of-file, and it only gets end-of-file when nobody holds the write end of the pipe open. If a single process forgets to close it, the pipeline hangs forever.

## Resources

### References

- [pipe(2)](https://man7.org/linux/man-pages/man2/pipe.2.html)
- [fork(2)](https://man7.org/linux/man-pages/man2/fork.2.html)
- [dup2(2)](https://man7.org/linux/man-pages/man2/dup.2.html)
- [execve(2)](https://man7.org/linux/man-pages/man2/execve.2.html)

### AI Usage

AI assistants were used for two tasks, always with me reviewing and testing the result:

- **Bug fixing:** the `PATH` lookup, the exit status and empty commands.
- **Documentation:** this README, checked against the code.

The design decisions were mine, and I can explain every part of the code.
