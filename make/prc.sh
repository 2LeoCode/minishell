#!/bin/bash

suffix=$(cat Makefile | grep -h "\.SUFFIXES =" | awk '{print $3}')
srcd=$(cat Makefile | grep -h "SRCD =" | awk '{print $3}')

total=$(ls $srcd/*$suffix | wc -l | tr -d ' ')
count=$(($total - `cat file.count`))

printf "\r\033[2KCompiling [$((100 * $count / $total))%%]"
cat file.count > tmp.txt
rm -f file.count
echo $((`cat tmp.txt` - 1)) > file.count
rm -f tmp.txt
