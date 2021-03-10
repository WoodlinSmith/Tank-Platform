#!/bin/bash

echo tournament_1v1/*.round > temp.txt
rm outcomes

cat temp.txt | sed "s/ /\n/g" > temp_2.txt
rm temp.txt

empty_size=0
actual_size=$(wc -c < "temp_2.txt")

until [ "$actual_size" -eq "$empty_size" ]; do
    TEXT=$(head -n 1 temp_2.txt)
#    echo $actual_size
    cp $TEXT ./config.txt
    ./platform
    tail -n +2 temp_2.txt > temp_2.txt
    actual_size=$(wc -c < "temp_2.txt")
done

rm temp_2.txt



