P=d
make ${P} ${P}2 gen || exit 1
for ((i = 1; ; i++)) do
    ./gen $i > in_
    ./${P} < in_ > out_
    ./${P}2 < in_ > out2_
    if (! cmp -s out_ out2_) then
        echo "--> entradas:"
        cat in_
        echo "--> saida1:"
        cat out_
        echo "--> saida2:"
        cat out2_
        break;
    fi
    echo $i
done
