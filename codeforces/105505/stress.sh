P=g
make ${P} ${P}2 gen || exit 1
for ((i = 1; ; i++)) do
	./gen $i > min
	./${P} < min > mout
	./${P}2 < min > mout2
	if (! cmp -s mout mout2) then
		echo "--> entrada:"
		cat min
		echo "--> saida1:"
		cat mout
		echo "--> saida2:"
		cat mout2
		break;
	fi
	echo $i
done
