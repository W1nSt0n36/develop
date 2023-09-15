#!/bin/bash
a=0
b=0
while read arg
do
	a=$(($a+1))
	b=$(($b+$arg))
done
sred=$(($b / $a))
echo $sred
echo $a
