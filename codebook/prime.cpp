// 埃式篩改
// 求n以內的所有質數
/*
埃式筛法：“埃拉托斯特尼筛法，简称埃氏筛或爱氏筛，是一种由希腊数学家埃拉托斯特尼所提出的一种简单检定素数的算法。要得到自然数n以内的全部素数，必须把不大于根号n的所有素数的倍数剔除，剩下的就是素数。”

算法复杂度：O(nloglogn)，可以看成线性的
*/
int p;  
int prime[maxn];  
bool is_prime[maxn];  
  
int prime(int n)  
{  
    p = 0;  
    for (int i = 0; i <= n; ++i) is_prime[i] = true;  
    is_prime[0] = is_prime[1] = false;  
    for (int i = 2; i*i <= n; ++i)   
        if (is_prime[i])   
            for (int j = i*i; j <= n; j += i)   
                is_prime[j] = false;  
    for (int i = 0; i <= n; ++i)   
        if (is_prime[i])  
            prime[p++] = i;  
    return p;  
}  
