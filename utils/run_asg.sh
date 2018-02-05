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

