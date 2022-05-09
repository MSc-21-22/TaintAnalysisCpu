if [[ $# -eq 0 ]] ; then
    echo 'Analyzer should be provided as argument'
    exit 1
fi

analyzer="$(realpath $1)"
echo "$analyzer"

for i in {1..10}
do 
    .$analyzer -ba sampleprograms/medium-size-program.sc
done

for i in {1..10}
do 
    .$analyzer -ba sampleprograms/small-array-sample.sc
done

for i in {1..10}
do 
    .$analyzer -ba sampleprograms/taint-into-param-test.sc
done