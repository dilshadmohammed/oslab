#!/bin/bash

read -p "Enter a number: " n

n1=0
n2=1
if ((n >= 1)); then
    echo -n "$n1 "
fi
if ((n >= 2)); then
    echo -n "$n2 "
fi

for ((i = 3; i <= n; i++))
do
    n3=$((n1 + n2))
    echo -n "$n3 "
    n1=$n2
    n2=$n3
done
