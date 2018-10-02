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

echo "ok"
