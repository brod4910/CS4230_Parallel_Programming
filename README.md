# CS 4230 Parallel Programming

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
```

As shown above, the first thing to do is to change from tcsh to bash and 
change directory into CS_4230

## Threading Building Blocks

Set up the ENVIRONMENT


```$ source dotcshrc```

```$ echo $TBB_HOME```

```
/home/vinuj/CS_4230/tbb
```

### DOWNLOAD

Download the necessary libraries


```$ make library=tbb download```

```
git clone https://github.com/01org/tbb.git
Cloning into 'tbb'...
remote: Counting objects: 9825, done.
remote: Total 9825 (delta 0), reused 0 (delta 0), pack-reused 9825
Receiving objects: 100% (9825/9825), 13.10 MiB | 14.61 MiB/s, done.
Resolving deltas: 100% (8046/8046), done.
```

### INSTALL

Install the necessary libraries

```$ make library=tbb install```

### WORKING DIRECTORY

```$ cd src_tbb/```

Develop your tbb based parallel code

### COMPILE IT

Build you application

```make SRC=tbb_hello_world compile```
 
### RUN IT

Execute you parallel application

```$ make SRC=tbb_hello_world run```

```
./tbb_hello_world.exe 
3.14159
```

## POSIX THREAD

### DOWNLOAD, INSTALL

Not necessary

### WORKING DIRECTORY

```$ cd CS_4230/```

```$ cd pthread/```

Develop your pthread based parallel code

### COMPILE

Your pthread code as SRC

```$ make SRC=pt_hello_world compile```

### EXECUTE

Your pthread code with THREAD

```$ make SRC=pt_hello_world THREADS=8 run```

```
./pt_hello_world.exe 8
Hello from thread 1 of 8
Hello from thread 6 of 8
Hello from the main thread
Hello from thread 2 of 8
Hello from thread 4 of 8
Hello from thread 5 of 8
Hello from thread 3 of 8
Hello from thread 7 of 8
Hello from thread 0 of 8
```

## THREAD SANITIZER

### DOWNLOAD, INSTALL

Not necessary on CADE

TODO: Add Pre-Requisites for Personal Machines

```cd CS_4230/tsan/```

### COMPILE

```$ make SRC=simple_race compile```

gcc-7.2 -o simple_race.exe -fsanitize=thread -static-libtsan simple_race.c

### RUN DATA RACE CHECKING

```$ make SRC=simple_race run```

```
./simple_race.exe 8
==================
WARNING: ThreadSanitizer: data race (pid=10755)
  Read of size 4 at 0x000001498888 by thread T2:
    #0 Thread2 <null> (simple_race.exe+0x00000048c3c8)

  Previous write of size 4 at 0x000001498888 by thread T1:
    #0 Thread1 <null> (simple_race.exe+0x00000048c38b)

  Location is global 'Global' of size 4 at 0x000001498888 (simple_race.exe+0x000001498888)

  Thread T2 (tid=10758, running) created by main thread at:
    #0 pthread_create ../../.././libsanitizer/tsan/tsan_interceptors.cc:900 (simple_race.exe+0x00000040c760)
    #1 main <null> (simple_race.exe+0x00000048c444)

  Thread T1 (tid=10757, finished) created by main thread at:
    #0 pthread_create ../../.././libsanitizer/tsan/tsan_interceptors.cc:900 (simple_race.exe+0x00000040c760)
    #1 main <null> (simple_race.exe+0x00000048c425)

SUMMARY: ThreadSanitizer: data race (/home/vinuj/CS_4230/tsan/simple_race.exe+0x48c3c8) in Thread2
==================
ThreadSanitizer: reported 1 warnings
```

## OPEN MP

### DOWNLOAD, INSTALL

Its already part of all major distributions,
Please contact TA's if you have any problems

### WORKING DIR

```cd CS_4230/omp/```

Develop your Open MP based code here.

### COMPILE

```$ make SRC=omp_hello_world compile```

```
gcc -g -Wall  -fopenmp -o omp_hello_world.exe omp_hello_world.c
```

### RUN

```make SRC=omp_hello_world run```

```
./omp_hello_world.exe 8
Hello from thread 0 of 8
Hello from thread 3 of 8
Hello from thread 1 of 8
Hello from thread 5 of 8
Hello from thread 4 of 8
Hello from thread 6 of 8
Hello from thread 2 of 8
Hello from thread 7 of 8
```

## TODO FOR TA's

- Show how to write a simple script in Python that produces a simple 
  scaling curve for an OpenMP Pi calculation, 
  and dumps answers to a graph 
  that is included in a simple webpage.




