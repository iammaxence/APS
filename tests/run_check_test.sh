#! /bin/bash


for i in `ls ./APS0/*.aps`
do
  echo $i " -> "
  echo  " resultat : "
  ./run_prolog_test.sh $i|swipl -s ../src/typage.pl -g main_stdin
  echo -e
done
