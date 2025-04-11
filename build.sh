#!/usr/bin/bash
clear

# 檢查是否提供檔案名稱參數
if [ $# -eq 0 ]; then
    echo "請提供源碼檔案名稱"
    echo "用法: ./build.sh <filename.cpp>"
    exit 1
fi

# 獲取從命令行參數傳入的檔案名稱
if [ -z "$2" ]; then
    in="in"
else
    in="$2"
fi

if [ -z "$3" ]; then
    rm a.out
    echo "編譯源碼檔案: $1"
    g++ $1 -O3 -w -Wfatal-errors -Wall -Wshadow -fsanitize=undefined -DLOCAL
    # execTime = $( {time ./a.out < ${in} } )
    # echo "${execTime}"
    ./a.out < "${in}"
else
    out="$3"
    rm a.out
    echo "編譯源碼檔案: $1"
    g++ $1 -O3 -w -Wfatal-errors -Wall -Wshadow -fsanitize=undefined -DLOCAL
    execTime=$( { time ./a.out < "${in}" > "${out}"; } 2>&1 )
    echo "${execTime}"
fi

