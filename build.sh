#!/bin/zsh
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
    rm -f a.out
    echo "編譯源碼檔案: $1"
    g++ $1 -O3 -w -Wfatal-errors -Wall -Wshadow -fsanitize=undefined -DLOCAL
    # 先正常執行程式顯示輸出
    ./a.out < "${in}"

    # 使用外部 time 命令測量時間
    
    # read user sys real <<< "$times"
    # echo "執行結果："
    # echo "  使用者時間: ${user}s"
    # echo "  系統時間: ${sys}s"
    # echo "  總耗時: ${real}s"
else
    out="$3"
    rm -f a.out
    echo "編譯源碼檔案: $1"
    g++ $1 -O3 -w -Wfatal-errors -Wall -Wshadow -fsanitize=undefined -DLOCAL
    
    # 直接使用 BASH 的 time 內建命令，並設定時間格式
    TIMEFORMAT='%3U %3S %3R'
    times=$(bash -c "time (./a.out < \"${in}\" > \"${out}\")")
    
    # 分割讀取的時間值
    read user sys real <<< "$times"
    
    echo
    echo "執行結果："
    echo "  使用者時間: ${user}s"
    echo "  系統時間: ${sys}s"
    echo "  總耗時: ${real}s"
fi