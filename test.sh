#!/bin/sh

gcc -std=c11 -O0 -g3 -Wall main.c -o main

fail() {
    echo $1
    exit 1
}

runtest(){
    ./main "$1"
    res=$?
    [ $res -eq $2 ] || fail "[ERROR] \"$1\": expect $2 but got $res"
}

runtest "0" 0
runtest "1" 1
runtest "42" 42
runtest "1+42" 43
runtest "23+42" 65
runtest "1+2+4" 7
runtest "1+2+4+10" 17
runtest "1*2+3" 5
runtest "1+2-3+5" 5
runtest "13/3+4" 8

echo "ok"
