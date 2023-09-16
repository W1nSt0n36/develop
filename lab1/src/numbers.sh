#!/bin/bash

for i in {1..150}; do
  random_number=$(od -An -N2 -i /dev/random)
  echo "$random_number" >> numbers.txt
done
