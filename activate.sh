#!/bin/bash

NCPUS=40
for (( c=0; c<$NCPUS; c++ ))
do
  taskset -c $c echo $c
done
