#!/bin/bash

METRICA="L3 L2CACHE ENERGY FLOPS_DP"
TAMS=(64 100 128 200 256 512 600 900 1024 2000 2048 3000 4000 5000) # 6000 10000)

echo "performance" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor

file="results"

if [ -f "$file" ] ; then
	rm "$file"
fi

make purge
make

for i in ${TAMS[@]}
do
	echo "Tamanho $i, tempo"
	echo "Tamanho $i, tempo" >> results
	./matmult ${i} >> results
done

for k in $METRICA
do
	for i in ${TAMS[@]}
	do
		echo "Tamanho $i, $k"
		echo "Tamanho $i, $k" >> results
		likwid-perfctr -C 3 -g ${k} -m ./matmult ${i} | grep -i "L3 bandwidth\|miss \RATIO\|Energy \[J\]\| MFLOP/s" | grep -v "Runtime\|GBytes\|rate" | awk {'print $1, $5, $6'} | sed 's/|//g' >> results
	done
done

echo "powersave" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor
