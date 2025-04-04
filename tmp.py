def solve():
    import sys
    sys.setrecursionlimit(10000)
    data = sys.stdin.read().split()
    if not data:
        return
    t = int(data[0])
    index = 1
    out_lines = []
    
    # 將正整數 n 轉換為四進位表示（以列表形式返回，從最高位到最低位）
    def to_base4(n):
        if n == 0:
            return [0]
        digits = []
        while n:
            digits.append(n % 4)
            n //= 4
        return digits[::-1]
    
    from functools import lru_cache
    # 在 [0, N] 中計算滿足四進位各位數和等於 target 的數的個數
    def count_base4_sum(N, target):
        if N < 0:
            return 0
        digits = to_base4(N)
        L = len(digits)
        # 若 target 超過 L 位數能達到的最大和（3L），則不可能有解
        if target > 3 * L:
            return 0
        
        @lru_cache(maxsize=None)
        def dp(pos, s, tight):
            # pos：當前處理到第 pos 位（0-indexed）
            # s：目前累加的各位數和
            # tight：是否受上界約束
            if pos == L:
                return 1 if s == target else 0
            limit = digits[pos] if tight else 3
            total = 0
            for d in range(limit + 1):
                ns = s + d
                if ns > target:
                    continue
                ntight = tight and (d == limit)
                total += dp(pos + 1, ns, ntight)
            return total
        
        return dp(0, 0, True)
    
    from math import ceil, floor
    for _ in range(t):
        l = int(data[index]); index += 1
        r = int(data[index]); index += 1
        k = int(data[index]); index += 1
        
        # 將 x = (4y - k)/3 萃取出 y 的區間
        Ly = (3 * l + k + 3 - 1) // 4  # 等價於 ceil((3*l+k)/4)
        Ry = (3 * r + k) // 4           # 等價於 floor((3*r+k)/4)
        
        # 若區間不存在，則答案為 0
        if Ly > Ry:
            out_lines.append("0")
            continue
        
        # 根據 Ry 的四進位位數長度剪枝：若 k 超過可能最大和，直接返回 0
        d_Ry = len(to_base4(Ry))
        if k > 3 * d_Ry:
            out_lines.append("0")
            continue
        
        # 答案為在 [0, Ry] 中符合條件的數減去在 [0, Ly-1] 中符合條件的數
        ans = count_base4_sum(Ry, k) - count_base4_sum(Ly - 1, k)
        out_lines.append(str(ans))
    sys.stdout.write("\n".join(out_lines))
    
if __name__ == '__main__':
    solve()
