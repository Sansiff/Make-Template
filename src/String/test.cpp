#include <bits/stdc++.h>
using namespace std;
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
typedef long long i64;
typedef pair<int,int> PII;
const int mod = 1e9 + 7;
i64 ksm(i64 a, i64 b){i64 res = 1;while(b){if(b&1) res=res*a%mod,b--;a=a*a%mod,b>>=1;}return res;}
i64 gcd(i64 a, i64 b){return b?gcd(b,a%b):a;}

void solve(){

}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); 
    solve();
    return 0;
}