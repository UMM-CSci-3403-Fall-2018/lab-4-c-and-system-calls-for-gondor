#!/bin/bash

#Colin Rabe and Elizabeth Stevens

#This script recursively travels through the path
#it is given as an argument and counts how many
#files and directories it comes across. It then
#prints its findings to the console.

path=$1;

directories=$(find $path -type d | wc -l);
files=$(find $path -type f | wc -l);

printf "There were $directories directories. \n"
printf "There were $files regular files. \n"
