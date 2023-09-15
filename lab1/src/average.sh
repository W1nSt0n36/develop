#!/bin/bash

count=0
number=0
while read arg
do
	count=$(($count+1))
	number=$(($number+$arg))
done
dev=$(($number / $count))
echo $dev
echo $count
