for i in {1..10}
do 
    ./build-release/analyzer -d f 1 -bam sampleprograms/multiplefunc.sc
done

for i in {1..10}
do 
    ./build-release/analyzer -d f 5 -bam sampleprograms/multiplefunc.sc
done

for j in {10..100..10}
do
    for i in {1..10}
    do 
        ./build-release/analyzer -d f $j -bam sampleprograms/multiplefunc.sc
    done
done

for j in {150..500..50}
do
    for i in {1..10}
    do 
        ./build-release/analyzer -d f $j -bam sampleprograms/multiplefunc.sc
    done
done

for j in {600..1500..100}
do
    for i in {1..10}
    do 
        ./build-release/analyzer -d f $j -bam sampleprograms/multiplefunc.sc
    done
done

for j in {2000..10000..1000}
do
    for i in {1..10}
    do 
        ./build-release/analyzer -d f $j -bam sampleprograms/multiplefunc.sc
    done
done