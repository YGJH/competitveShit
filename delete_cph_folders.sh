#!/usr/bin/bash

# 顯示要刪除的資料夾（預覽模式）
echo "以下是將被刪除的 .cph 資料夾："
find . -type d -name ".cph" -print

# 確認是否繼續
read -p "是否確認刪除以上資料夾？(y/n): " confirm

if [ "$confirm" = "y" ] || [ "$confirm" = "Y" ]; then
    # 刪除所有 .cph 資料夾
    find . -type d -name ".cph" -exec rm -rf {} \; 2>/dev/null || echo "部分資料夾可能需要更高權限"
    echo "所有 .cph 資料夾已刪除！"
else
    echo "操作已取消，未刪除任何資料夾。"
fi
