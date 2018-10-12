#!/bin/bash

#Colin Rabe and Elizabeth Stevens

path=$1;

directories=$(find $path -type d | wc -l);
files=$(find $path -type f | wc -l);

printf "There were $directories directories. \n"
printf "There were $files regular files. \n"
