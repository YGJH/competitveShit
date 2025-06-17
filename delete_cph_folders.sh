#!/usr/bin/bash

# 顯示要刪除的資料夾（預覽模式）
# 檢查是否提供檔案名稱參數
if [ $# -eq 0 ]; then
    echo "請提供源碼檔案名稱"
    echo "用法: ./delete....sh <filename>"
    exit 1
fi

echo "以下是將被刪除的 $1 資料夾："
find . -type d -name $1 -print

# 確認是否繼續
read -p "是否確認刪除以上資料夾？(y/n): " confirm

if [ "$confirm" = "y" ] || [ "$confirm" = "Y" ]; then
    # 刪除所有 .cph 資料夾
    find . -type d -name $1 -exec rm -rf {} \; 2>/dev/null || echo "部分資料夾可能需要更高權限"
    echo "所有 $1 資料夾已刪除！"
else
    echo "操作已取消，未刪除任何資料夾。"
fi
