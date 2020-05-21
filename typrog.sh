#! /bin/bash

make --directory=src

./prologTerm.sh $1|swipl -s ./src/typage.pl -g main_stdin
