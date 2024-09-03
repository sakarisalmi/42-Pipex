# 42-Pipex
Use important programming concepts - redirection, piping and forking - to create a program in which the results of one command are fed into to another one. The idea of the project is to basically mimic what happens in a terminal like bash or zsh when you redirect or pipe stuff.

## Preamble
This is an awesome project. It isn't that big, but it taught me some very important concepts in programming that I hadn't know about before. But when I learned them, it felt like a whole new dimension had opened up before me - and I'm sure any person who's reading this can relate to this feeling. Great stuff.

But before going into the project itself, we should quickly recap what redirection and piping actually do in the shell.

### Redirection
Redirection is exactly what it sounds like: you're redirecting the input or output of a program to something else than what they usually are.

without redirection:
```
> echo "Hello, World!\n"
Hello, World!
>
```
The output got printed to standard output, in this case, the terminal.

Now with redirection:
```
> echo "Hello, World!\n" > results.txt
>     # added this empty line to show that nothing got printed out on the terminal
> cat results.txt
Hello, World!
>
```
The echo command's output got redirected to a file (we didn't need to use the touch command because the redirection will automatically create a file if one doesn't already exists). Be careful with redirecting to any existing files, though, because using '>' will overwrite the data in it (use '>>' to append to the end of the file).

To redirect the input to a command, use '<' instead.
```
> cat example.txt
one
two
three
> grep "two" < example.txt
two
>
```
Using '<<' will create a here_doc, which will take in input from the standard input until EOF (end of file) by either pressing ctrl-D or writing 'EOF'.

Redirections are typically used with files, but any input/output (I/O) resource will do. There is also a lot more to redirections than what was explained here, and I do recommend looking it up, but let's keep it short, ok?

### Piping
Whereas redirection is typically used with files and such, piping is used to chain programs and commands to each other, where the previous commands output is redirected as input to the next command. The symbol used for piping is '|'.
```
> echo "one\ntwo\nthree" | grep "two"
two
>
```
You can chain as many commands together as you want, and yes, that means you can do some pretty powerful stuff. Of course, you can always use redirections and piping together.
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

Ok, Now that we know what we're trying to replicate with the program, let's get into the project!

## The Project
So we know how redirection and piping work in the CLI, how do you do the same in a C-program? How do you link two two programs together in C? Wait a second, how do you even run a program _inside_ your program, let alone two?

Let's start with that first.
### execve and forking
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

Ok, One question clears just to be replaced by two new ones: how are we supposed to execute two commands in our program, and what is the point of replacing your original program 



## The concepts
### redirection
I hope it doesn't come as a shock that redirection is exactly what sounds like: you change the input or output flow of a process to something different. While we haven't yet redirected in earlier 42-projects, we've already done some _directing_: as you might recall, in ft_printf we use the unistd-libraries write() function. You can use write() to in a very simple program:
```
#include <unistd.h>

int main(){
char string[] = "Hello, World!\n";
write(1, string, strlen(string));
return(0);
}
```
The first parameter of write() is the most pertinent for us here; it is the file descriptor of where you want to write to. In programs that are running on UNIX, the tree first file descriptors are always reserved to certain inputs/outputs: 0 is for STDIN, 1 is for STDOUT and 2 is for STDERR (you can change these to something else, if you so please). Let's say that we have compiled the above program into an executable called a.out. Now, let's execute it in the terminal:
```
>./a.out
Hello, World!
>
```
Yay. But nothing special as we've seen this before.

But what if you don't want the output of program to be printed out into the terminal?

That's where the redirection comes in!

If you're at all familiar with doing stuff in a Linux-terminal, you most likely seen these strange symbols: '>' and '<'. What could they be? (ok, this coy act is dumb: if you've seen these, you've most likely used them and in that case this whole not-so-clever introduction is pointless, but moving on). Well, you can do something like this in the terminal:
```
>touch example.txt
>./a.out > example.txt
>
```
'touch' is for creating a file (it isn't even necessary as the second line would create the file anyway, but it is good to show stuff properly, ok?), but that isn't so what interests us. What interests us is that there was no "Hello, World!" printed into terminal. Where did the text go? Yeah, you guessed it:
```
> cat example.txt
Hello, World!
>
```
The output of the program was _redirected_ to the file instead of the terminal. '>' and '<' are _overwrite redirections_ with which you can . Using '>' will redirect anything that would get normally get directed to STDIN will instead get redirected to the file you put after it. It is especially is useful when you want to store the output of a program for later use.

the input redirection is a bit trickier to explain:
```
> cat example.txt
Hello, World!
> cat < example.txt
Hello, World!
```
You can see that both of the commands print out the same result. The difference between them is that the one above reads the file, but the one below reads _the file's contents as an input stream_. It's a bit strange, but in the command below cat doesn't 'know' that it is reading a file - it's just gets the file's contents fed to it.

### Piping
Piping is 
