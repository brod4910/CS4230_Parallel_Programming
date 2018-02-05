#!/bin/bash
set -e
# Bash Script to help Grading
# Usage: ./utils/run-asg.sh number
#-------------------------------------------------------------------------

if [ $# -lt 1 ]
then
  echo "Usage: $0 asg-number"
  exit 1
fi

# TODO add env check , exit if  source dotcshrc not done

if [ $1 -eq 1 ] ; then
    # This is of the from
    # cd src/<asg number>
    
    cd src/pthreads/
    
    # This is of the from 
    # cd <question-1>
    cd NonLocality/
    
    # These are the supplied make commands in the respective
    # readme files of each question provided to you
    make SRC=badLoc
    make SRC=goodLoc
    
    # If you develop any run scripts add them here
    time ./badLoc.exe
    time ./goodLoc.exe
    
    # Go back home, when needed.
    cd $CS_4230_HOME/
fi


# TODO 
if [ $1 -eq 2 ] ; then
echo  "You Complete the commands for asg-2"
fi    

# TODO 
# Develop for asg-2

# TODO 
# Develop for asg-3

# TODO 
# Develop for asg-4


# TODO 
# Develop for asg-5















