#!/bin/sh

inputFile=$1
outputFile="${1%.*}.out"      # extract the name of the file without extension and adding extension .out
#cmd=`mpicc $inputFile -o $outputFile`
cmd="gcc $inputFile -o $outputFile -lpthread"     # running code using MPI
echo "------------------------------------------------------------------"
echo "Command executed: $cmd"
echo "------------------------------------------------------------------"
$cmd
echo "Compilation successful. Check at $outputFile"
echo "------------------------------------------------------------------"
