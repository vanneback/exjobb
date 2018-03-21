#!/bin/bash
#replaces spaces with comma, multiple spaces will be one comma
FILE1=$1
TEMP="output/temp.csv"
tr -s " " < $FILE1 > $TEMP
tr " " , < $TEMP > $FILE1
tr -s , < $FILE1 > $TEMP
cp $TEMP $FILE1
rm $TEMP 
