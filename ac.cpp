#include<iostream>
#include<cstring>
#include<set>
#include<map>
#include<functional>
#include<vector>
#include<queue>
#include<math.h>
#include<algorithm>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define lson u<<1
#define rson u<<1|1
#define IOS ios::sync_with_stdio(0);cin.tie(nullptr)
const int N=5e4+10; 
struct node{
    int l,r;
    int sum;
    int tag;    
}tr[N<<2];
void pushup(int u){
    tr[u].sum=tr[lson].sum+tr[rson].sum;
}
void build(int l,int r,int u=1){
    tr[u].l=l,tr[u].r=r;
    tr[u].sum=0;tr[u].tag=-1;
    if(l==r) return;
    int mid=l+r>>1;
    build(l,mid,lson);
    build(mid+1,r,rson);
}
void pushdown(int u){
    if(tr[u].tag==-1) return;
    tr[lson].sum=(tr[lson].r-tr[lson].l+1)*tr[u].tag;
    tr[rson].sum=(tr[rson].r-tr[rson].l+1)*tr[u].tag;
    tr[lson].tag=tr[rson].tag=tr[u].tag;
    tr[u].tag=-1;
}
void update(int l,int r,int x,int u=1){
    if(tr[u].l>=l && tr[u].r<=r){
        tr[u].tag=x;
        tr[u].sum=(tr[u].r-tr[u].l+1)*x;
        return;
    }
    pushdown(u);
    int mid=tr[u].l+tr[u].r>>1;
    if(mid>=l) update(l,r,x,lson);
    if(mid+1<=r) update(l,r,x,rson);
    pushup(u);
}
int query(int l,int r,int u=1){
    if(tr[u].l>=l && tr[u].r<=r){
        return tr[u].sum;
    }
    pushdown(u);
    int mid=tr[u].l+tr[u].r>>1;
    int res=0;
    if(mid>=l) res+=query(l,r,lson);
    if(mid+1<=r) res+=query(l,r,rson);
    return res;
}
int findlast(int l,int r,int y){
    if(l==r) return r;
    int mid=l+r>>1;
    int tsum=query(l,mid);
    if(mid-l+1-tsum>=y){
        return findlast(l,mid,y);
    }
    else{
        return findlast(mid+1,r,y-(mid-l+1-tsum));  
    }
}
int n,m;
void solve(){
    cin>>n>>m;
    build(1,n);
    while(m--){
        int opt,x,y;
        cin>>opt>>x>>y;
        if(opt==1){
            x++;
            int p=-1;
            int sum=query(x,n);
            if(sum==n-x+1){
                cout<<"Can not put any one."<<'\n';
            }
            else if(sum>=n-x+1-y){
                int s=findlast(x,n,1);
                int e=findlast(x,n,n-x+1-sum);
                update(s,e,1);
                s--;e--;
                cout<<s<<" "<<e<<'\n';
            }
            else{
                int s,e;
                s=findlast(x,n,1);
                e=findlast(s,n,y);
                update(s,e,1);
                s--;e--;
                cout<<s<<' '<<e<<'\n';
            }
        }
        else{
            x++;y++;
            cout<<query(x,y)<<'\n';
            update(x,y,0);
        }
    }
    cout<<'\n';
}

int main(){
    IOS;
    int t;
    cin>>t;
    while(t--)solve();
}
