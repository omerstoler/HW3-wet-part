#!/bin/bash

FILES=(small.txt mid.txt big.txt)
for file in ${FILES[@]}; do
  for (( i = 1; i <= 100; i++ )); do
    ./GameOfLife $file 100 $i N N
    echo finished iteration $i
  done
 echo finished file $file
done
