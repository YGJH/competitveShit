def rule110_evolve(initial: str, N: int) -> int:
    # initial: 16 位 '0'/'1'，边界之外均假设为 0
    # N < 2^60，但若 N 非常大，这里方法会超时或内存爆炸！
    
    # 先把所有为 '1' 的位置存到一个集合里
    live = set(i for i, ch in enumerate(initial) if ch == '1')
    
    # 预先准备一个查表 dict，从三元组到新状态
    rc = {
        (1,1,1): 0, (1,1,0): 1, (1,0,1): 1, (1,0,0): 0,
        (0,1,1): 1, (0,1,0): 1, (0,0,1): 1, (0,0,0): 0,
    }
    
    # 模拟 N 步
    for _ in range(N):
        candidates = set()
        for i in live:
            candidates |= {i-1, i, i+1}
        next_live = set()
        for i in candidates:
            pattern = (1 if (i-1 in live) else 0,
                       1 if (i   in live) else 0,
                       1 if (i+1 in live) else 0)
            if rc[pattern] == 1:
                next_live.add(i)
        live = next_live
    
    return len(live)

# 测试样例
st = input()
n = int(input())
print(rule110_evolve(st, n))  # 输出 11
