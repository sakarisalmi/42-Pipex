# 42-Pipex
Use important programming concepts - redirection, piping and forking - to create a program in which the results of one command are fed into to another one.

## Preamble
This is an awesome project. It isn't that big, but it taught me some very important concepts in programming that I hadn't know about before. But when I learned them, it felt like a whole new dimension had opened up before me - and I'm sure any person who's reading this can relate to this feeling. Great stuff.

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
