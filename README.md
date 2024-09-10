# 42-Pipex
Use important programming concepts - redirection, piping and forking - to create a program in which the results of one command are fed into to another one. The idea of the project is to basically mimic what happens in a terminal like bash or zsh when you redirect or pipe commands.

## Preamble
This is an awesome project. It isn't that big, but it taught me some very important concepts in programming that I hadn't know about before. But when I learned them, it felt like a whole new dimension had opened up before me - and I'm sure any programmer who's reading this can relate to this feeling. Great stuff.

But before going into the project itself, we should quickly recap what redirection and piping actually do in the shell.

### Redirection
Redirection is exactly what it sounds like: youe redirect the input or output of a program to something else.

without redirection:
```
> echo "Hello, World!\n"
Hello, World!
>
```
The output got sent to the standard output, in this case the terminal.

Now with redirection:
```
> echo "Hello, World!\n" > results.txt
# no output in the terminal
> cat results.txt
Hello, World!
>
```
The echo command's output got redirected to a file (we didn't need to use the touch command because the redirection will automatically create a file if one doesn't already exists). Be careful with redirecting to any existing files, though, because using '>' will overwrite the data in it (use '>>' to append to the end of the file).

To redirect the input of command, use '<' instead.
```
> cat example.txt
one
two
three
> grep "two" < example.txt
two
>
```
Using '<<' will create a here_doc, which will take in input from the standard input until EOF (end of file). This can be done by either pressing ctrl-D or writing 'EOF'.

Redirections are typically used with files, but any input/output (I/O) resource will do. There is also a lot more to redirections than what was explained here, and I do recommend looking it up, but let's keep it short, ok?

### Piping
Whereas redirection is typically used with files and such, piping is used to chain programs and commands to each other, where the previous commands output is redirected as input to the next command. The symbol used for piping is '|'.
```
> echo "one\ntwo\nthree" | grep "two"
two
>
```
You can chain as many commands together as you want and yes, that means you can do some pretty powerful stuff. Of course, you can always use redirections and piping together.
```
> cat example.txt
one
two
three
> grep "two" < example.txt | wc > results.txt
> cat results.txt
    1    1    4
>
```

Ok, Now that we know what we're trying to replicate with the program, let's get into the new interesting things in the project!

## New concepts learned in the project
So now we know how redirection and piping work in the CLI, but how do you do the same in a C-program? How do you link two two programs together in C? Wait a second, how do you even run a program _inside_ your program, let alone two?

Let's start with that first.
### execve and fork
To execute a file, use the execve() function.
> int execve(const char *path, char *const argv[], char *const envp[]);

A quick example:
```
#include <stdio.h>

int main() {
	char *args[] = {"/bin/echo", "this is the echo command!\n", NULL};
	char *env[] = {"PATH=/bin", NULL};

	printf("Before execve\n");
	execve(args[0], args, env);
	printf("After execve\n");
	return(0);
}
```
```
> ./a.out
Before execve
this is the echo command!
>
```
You'll notice two things. First, the execve() worked. Second, for some reason the second printf-statement didn't show up. That's because it didn't happen; the a.out _process image_ got replaced by by the echo process image (the process image is the in-memory representation of a process). So when you run execve, your program gets entirely replaced by what you put in the execve arguments and if it didn't, something went wrong and there was an error.

Ok, One question cleared just for a new one to take its place: how are we supposed to execute two commands in our program? This is where _forking_ comes in.

The fork() function is for creating a new process. Behold:
```
#include <stdio.h>
#include <unistd.h>

int main() {
	printf("Before forking\n");
	fork();
	printf("After forking\n");
	return(0);
}
```
```
> ./a.out
Before forking
After forking
After forking
```
As you can see, the string "After forking" gets printed twice. That is because the fork() creates a carbon copy of the original process which then continues from that point forward alongside the original one. "But wait," I hear you say, "if they're copies of each other, won't they just continue down the exact same path to the very end? How does That get us closer to executing two different commands in the same program?" To that excellent question I specify that the two processes are the exact copies of each other except for one minor thing (ok, there may be more differences between the two, but moving on). The difference is that they have different process ids, or PIDs for short. Let's look at the prototype for fork():
> pid_t fork(void);

the return value makes all the difference here. Check it out:
```
#include <stdio.h>
#include <unistd.h>

int main() {
	printf("before forking\n");
	pid_t pid = fork();
	if (pid == 0) {
		printf("This is the parent process (pid: 0)\n");
	} else {
		printf("This is the child process (pid: %d)\n", pid);
	}
	return(0);
}
```
```
> ./a.out
before forking
This is the child process (pid: 47418)
This is the parent process (pid: 0)
>
```
As you can see, the processes printed something different this time (if you run the program multiple times, you'll notice that the pid will keep changing, and maybe also the order of which process output prints out first - this is because both processes run simultaneously, and it's random which one outputs its contents first). And just we're able to make the two processes print different strings, we're also able to execute different commands!

## pipes, dup and dup2
So now that we are able to to execute two different commands, how do we feed the output of one command to another as input?

This is where pipes come in again!

We've already done piping in the CLI, but we didn't go into detail of what happens 'under the hood', so to say.

>int dup(int fildes);
>int dup2(int fildes, int fildes2);

dup() duplicates an existing object descriptor and returns its value to the calling process. In dup2(), the value of the new descriptor fildes2 is specified.

We aren't that interested in dup(), but dup2(). Here, look:
```
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(){
	int fd = open("example.txt", O_RDONLY); // This file already exists in this example
	dup2(fd, 1);

	printf("Hello, World!\n");
	return(0);
}
```
```
> ./a.out
# no output in the terminal
> cat example.txt
Hello, World!
>
```
As you can see, we redirected the output to a file from inside the program.

And that's about it. That's everything new that the project introduces.
