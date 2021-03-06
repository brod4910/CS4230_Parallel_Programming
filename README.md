# CS 4230 Parallel Programming

## Fork

There is a button on this page that says `Fork`
Please fork this repository and add your work into that.
Just forking is not enough, Please follow instructions in [here](https://about.gitlab.com/2016/12/01/how-to-keep-your-fork-up-to-date-with-its-origin/)
to keep up to date with the CS_4230 Class Repository.

## Upstream

* To add the class repository as one of your remote upstreams, 
* to pull and sync with it as updates are published, just follow these simple steps.

```git remote add upstream_name https://username@gitlab.com/vinutah/CS_4230.git```

* Replace upstream_name with whatever name you want to use for Vinu's repo and replace username with your gitlab username.
* Once that is done, you can pull from that repository by typing:

```git pull upstream_name master```

Again replace upstream_name with whatever name you chose.

* And that's it, ```git``` will ask you to create a new commit for the merge, 
* either using vi or vim. 
* On the keyboard type :wq and then press enter to save and quit the commit message.

* Do keep in mind however when you push to your own remote repo you will need to 
* know the name of it so git knows which one to use. It is probably called origin.

``git push origin master``

* In these cases, ```master``` is the branch that you are attempting to push/pull to/from. 
* It might be optional but I keep it there for verbosity.

* Lastly, you can view the remote repos by typing:

```git remote -v```

## Grading

The graders will ideally like to do only the following to compile and run you submission for the grading.
Please ensure that the make commands you use or any python or other scripts that you might
have developed are addeded into your grade.sh

```
$ source dotcshrc 
$ ./utils/grade.sh <1/2/3/4/5..>
```

A utils directory is added containing a base, sample grade script



## Important Links

* [Class Webpage](tinyurl.com/teach4230s18)
* [Class Syllabus](tinyurl.com/cs4230-syllabus-s18)
* [Class Students](tinyurl.com/cs4230-students-s18)


If you have setup Automation as described [here](https://sites.google.com/view/cs4230spring2018/parallel-hardware)

They typing ```cade``` in you terminal will do the following

## Supported Operating Systems

This code in this class repository is tested only on Linux machines.
Currently we do not support any pro.pri.e.tary , closed source, slow
and buggy operating systems like Microsoft Windows or 
expensive and unconfigurable operating systems like Apple macOS.

If you unfortunately only use such machines, for reasons that are 
most likely flawed, you need to login to a machine that runs Linux.
for example, you could login into the following.

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

`$ cd CS_4230/`

`$ source dotcshrc`

`$ cd src/openmp/`

`$ cd hello_world/`

`$ make SRC=hello_world PARLIB=openmp`

### Run

`$ ./hello_world.exe 5
argc = 2
Hello from thread 0 of 5
Hello from thread 2 of 5
Hello from thread 4 of 5
Hello from thread 3 of 5
Hello from thread 1 of 5
`

## TBB

`
$ cd lib
$ git clone https://github.com/01org/tbb.git
$ cd tbb
$ unalias make (ignore if dotcshrc not sourced, no harm even if executed)
$ make
$ ln -s build/linux_intel64_gcc_cc<version>_libc<version>_kernel<version>_release/ lib
`
### Run

`
cd ~/CS_4230/src/tbb/
source ~/CS_4230/dotcshrc
make SRC=primes3_w_vec PARLIB=tbb CC=g++
`




