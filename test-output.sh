#!/bin/bash

generator=$1
tests=$2
m=$3

for((i = 0; i < tests; i++))
do
    $generator $i $m > input
    ./main < input > out1 2> /dev/null
    ./naive < input > out2
    if ! diff -q out1 out2
    then
        echo "$generator $i $m: failed"
        break
    fi
done
echo "$generator $m ok"
rm input out1 out2