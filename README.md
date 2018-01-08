# CS 4230 Parallel Programming

If you have setup Automation as described [here](https://sites.google.com/view/cs4230spring2018/parallel-hardware)

They typing cade in you terminal will do the following

## CADE Login

$ cade
Last login: Sun Jan  7 22:01:32 2018 from school.uconnect.utah.edu

#################################################
#               Welcome to CADE                 #
#                                               #
#            No Scheduled Downtime              #
#################################################

$ bash
$ cd CS_4230/

## Threading Building Blocks

$ source dotcshrc 
$ echo $TBB_HOME 
/home/vinuj/CS_4230/tbb

### DOWNLOAD

$ make library=tbb download
git clone https://github.com/01org/tbb.git
Cloning into 'tbb'...
remote: Counting objects: 9825, done.
remote: Total 9825 (delta 0), reused 0 (delta 0), pack-reused 9825
Receiving objects: 100% (9825/9825), 13.10 MiB | 14.61 MiB/s, done.
Resolving deltas: 100% (8046/8046), done.

### INSTALL

$ make library=tbb install

### YOUR TBB BASED PARALLEL CODE

$ cd src_tbb/


### COMPILE IT

make SRC=tbb_hello_world compile
 
### RUN IT

$ make SRC=tbb_hello_world run
./tbb_hello_world.exe 
3.14159

