#!/bin/bash

rm -f validation_idle.txt
sudo stap idle.stp -o out -c './activate.sh; ./idle_test 10 25 25000 10'
cat validation_idle.txt
sort -s -n -k 1,1 out > out2
python3 idle.py out2 `awk '$1 ~ /^begin_ts/ {print $2}' out2` `awk '$1 ~ /^end_ts/ {print $2}' out2`
