#!/bin/bash

rm -f validation_idle.txt
sudo stap idle.stp -o out -c './activate.sh; ./idle_test 10 25 25000 10'
cat validation_idle.txt
python3 idle.py out `awk '$1 ~ /^begin_ts/ {print $2}' out` `awk '$1 ~ /^end_ts/ {print $2}' out`
