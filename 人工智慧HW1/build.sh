#!/usr/bin/bash
clear

# 檢查是否提供檔案名稱參數
if [ $# -eq 0 ]; then
    echo "請提供源碼檔案名稱"
    echo "用法: ./build.sh <filename.cpp>"
    exit 1
fi

# 獲取從命令行參數傳入的檔案名稱
name=$1
rm a.out output.out
echo "編譯源碼檔案: $name"
g++ $name -O3 -w -Wfatal-errors -Wall -Wshadow -fsanitize=undefined -DLOCAL
./a.out < 1.in
