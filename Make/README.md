# Undestanding
Makefiles are a simple way to organize code compilation.


## Basic of Makefile
~~~
The-Dish: Ingredients
  Recipes
~~~

### Sample 1
~~~
main: main.c sub.c
  gcc -o main main.c sub.c
~~~
The simplest makefile you could create would look something like ↑
### Sample 2
~~~
CC=gcc

main: main.c sub.c
  $(CC) -o main main.c sub.c
~~~
In order to be a bit more efficient by to use a **variable**, let's try the following ↑
### Sample 3
~~~
CC=gcc

main: main.o sub.o
  $(CC) -o main main.o sub.o
main.o: main.c
  $(CC) -c main.c
sub.o: sub.c
  $(CC) -c sub.c
~~~
Create separate object files and link at the end ↑
### Sample 4
```
CC            = gcc
CFLAGS        = -O4 -Wall
OBJS          = main.o sub.o
PROGRAM       = main
DEPS          = sub.h

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
  $(CC) $(OBJS) $(CFLAGS) -o $(PROGRAM)
main.o: main.c $(DEPS)
  $(CC) $(CFLAGS) -c main.c
sub.o: sub.c  $(DEPS)
  $(CC) $(CFLAGS) -c sub.c

clean:
      -rm *.o
```
Including a rule for cleaning up obj files if you type make clean. ↑
### Sample 5
```
CC            = gcc
CFLAGS        = -O4 -Wall
OBJS          = main.o sub.o
PROGRAM       = main
DEPS          = sub.h

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
  $(CC) $^ $(CFLAGS) -o $@
%.o: %.c $(DEPS)
  $(CC) $(CFLAGS) -c $<

clean:
      -rm *.o
```
Using automatic variables ↑

### References

[A Simple Makefile Tutorial](http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/)<br>
[Makefileの解説](http://omilab.naist.jp/~mukaigawa/misc/Makefile.html)<br>
