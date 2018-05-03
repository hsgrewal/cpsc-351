# Assignment 1

## Goals
1. To gain hands-on experience with `fork()`, `exec()`, and `wait()` system
    calls
2. To master the basics of multi-process application development
3. To appreciate the performance and fault-tolerance benefits of multi-process
    applications
4. To implement a multi-process downloader application

## Part I: Shell
This is a simple shell program called `shell`. During execution, the parent
process prints out the prompt:
> `cmd>`

It will then wait for the user to enter a command (`ls`, `ps`, `pwd`, etc.).

The parent process then uses `fork()` to create a child. It then calls `wait()`
to wait for the child process to terminate. The child process uses the
`execlp()` system call to replace its program with the program specified at
the command line. After the child process produces its output, the parent
process prompts the user to enter another command.

The parent process will repeat this sequence until the user enters `exit` to
exit the shell.

#### Compile
`g++ shell.cpp -o shell`

#### Execute
`./shell`

#### Usage
`cmd> <COMMAND>`

**NOTE:** The shell program does not support arguments to be passed along with
commands.

## Part II: Downloader
*File downloaders* programs are used to download files from the Internet. Two
different types of *multi-process downloaders* are implemented in this
assignment:

1. *serial* - downloads files one by one
2. *parallel* - downloads multiple files in parallel

The performance of the two downloaders is compared. Both downloader use `wget`
program to download files. Usage of `wget` is: `wget <FILE URL>`

The parent process first read the file [urls.txt](urls.txt), containing the
URLs of the files to be downloaded. Next, the parent forks the child processes.

### Serial Downloader
The serial downloader downloads files one by one. After the parent process
has read the [urls.txt](urls.txt) file, it will:

1. Fork off a child process
2. Child process will use
    `execlp("/usr/bin/wget", "wget", <URL STRING>, NULL)` system call to
    replace its program with `wget` program.
3. The parent executes `wait()` system call until the child exits
4. The parent forks off another child process to download next file
5. Repeat until all files are downloaded

#### Compile
`g++ serial.cpp -o serial`

#### Execute
`./serial`

**NOTE:** Ensure that a txt file containing urls ("urls.txt") is in the
current directory

### Parallel Downloader
1. The parent forks off *n* children, where *n* is the number of URLs in
    [urls.txt](urls.txt)
2. Each child process executes
    `execlp("/usr/bin/wget", "wget", <URL STRING>, NULL)`
3. The parent executes `wait()` system call (*n* times) and waits for all
    children to terminate
4. The parent exits

#### Compile
`g++ parallel.cpp -o parallel`

#### Execute
`./parallel`

**NOTE:** Ensure that a txt file containing urls ("urls.txt") is in the
current directory

### Performance
Use `time` program to measure differences in execution times of the two
downloaders. Usage:
```
time ./serial
time ./parallel
```
**NOTE:** Performance difference is amplified with more and larger files.
