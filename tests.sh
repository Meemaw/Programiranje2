#!/bin/bash -e

for i in {0..10}
do
	(cd Assigment$i && make test)
done