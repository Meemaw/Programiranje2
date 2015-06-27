ID=$1
NUMINPUTS=$(ls tests/ | grep input | wc -l)


echo "=== TESTING: ==="
for i in $(seq 1 $NUMINPUTS);
do
	./$ID < ./tests/input-$i > result-$i
	if diff -w -B result-$i ./tests/output-$i ; then echo "$i - correct"; else exit 1; fi
done

