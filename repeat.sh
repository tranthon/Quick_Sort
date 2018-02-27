#!/bin/bash

COUNTER=0
while [  $COUNTER -lt 1000 ]; do
  ./a.out 100 result_quicksort_100.txt
  ./a.out 1000 result_quicksort_1000.txt
  ./a.out 10000 result_quicksort_10000.txt
  ./a.out 100000 result_quicksort_100000.txt
  let COUNTER=COUNTER+1
done
