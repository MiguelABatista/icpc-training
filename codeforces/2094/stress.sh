P=f
make ${P} ${P}2 gen || exit 1
for ((i = 1; ; i++)) do
	./gen $i > in_
	./${P} < in_ > out_
	./${P}2 < out_ > out_2
	if (! cmp -s gaba out_2) then
		echo "--> entrada:"
		cat in_
		echo "--> saida1:"
		cat out_
		break;
	fi
	echo $i
done
