#! /bin/bash

make --directory=src

./src/as < $1 -e
