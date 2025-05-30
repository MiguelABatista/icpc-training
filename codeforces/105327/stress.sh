P=i
make ${P} ${P}2 gen || exit 1
for ((i = 1; ; i++)) do
	./gen $i > in_
	./${P} < in_ > out_
	./${P}2 < in_ > out2
	if (! cmp -s out_ out2) then
		echo "--> entrada:"
		cat in_
		echo "--> saida1:"
		cat out_
		echo "--> saida2:"
		cat out2
		break;
	fi
	echo $i
done
