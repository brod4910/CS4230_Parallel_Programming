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

### YOUR TBB BASED PARALLEL CODE

Write you parallel application

```$ cd src_tbb/```

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

### No need to download or install

```$ cd CS_4230/```

```$ cd pthread/```

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

## OPEN MP

### DOWNLOAD, INSTALL

Its build it

### COMPILE



### RUN












































