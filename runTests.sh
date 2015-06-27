ID=$1
NUMINPUTS=$(ls tests/ | grep input | wc -l)


echo "=== TESTING: ==="
for (( i=1; i<=$NUMINPUTS; i++ ))
do
	./$ID < ./tests/input-$i > result-$i
	if diff -w -B result-$i ./tests/output-$i ; then echo "$i - correct" ; fi
done

