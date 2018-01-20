# CS 4230 Parallel Programming

## Clone Recursive

`git clone --recursive git@gitlab.com:vinutah/CS_4230.git`

## Important Links

* [Class Webpage](tinyurl.com/teach4230s18)
* [Class Syllabus](tinyurl.com/cs4230-syllabus-s18)
* [Class Students](tinyurl.com/cs4230-students-s18)


If you have setup Automation as described [here](https://sites.google.com/view/cs4230spring2018/parallel-hardware)

They typing ```cade``` in you terminal will do the following

## CADE Login

```$ cade```

```
Last login: Sun Jan  7 22:01:32 2018 from school.uconnect.utah.edu

#################################################
#               Welcome to CADE                 #
#                                               #
#            No Scheduled Downtime              #
#################################################

$ bash
$ cd CS_4230/
$ source dotcshrc
```

As shown above, the first thing to do is to change from tcsh to bash and
change directory into CS_4230

## CS_4230 Setup

Please note that we expect you to be in `$HOME` on your machine
when you are setting up the CS_4230.

We are expecting that the class repository be checked out in `$HOME` directory.
because dotcshrc expects CS_4230 directory to be at `$HOME`.

Please note that every terminal that you compile the sources provided
in CS_4230 uses environment variables, so please ensure that
you are in `bash` and have executed `source dotcshrc`


## Compiling

`make SRC=<filename>`

Please not that you need not provide the .c as the extension, we figure
that out ourselves.

## Open MP

### Compile
`$ cd CS_4230/src/openmp/`
`$ cd hello_world/`
`$ make SRC=hello_world PARLIB=openmp`

### Run

`
$ ./hello_world.exe 5
argc = 2
Hello from thread 0 of 5
Hello from thread 2 of 5
Hello from thread 4 of 5
Hello from thread 3 of 5
Hello from thread 1 of 5
`
