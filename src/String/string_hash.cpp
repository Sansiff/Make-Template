#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#ifdef LOCAL
#include <debugger>
#else
#define debug(...) 42
#endif
template <typename T> void chkmax(T &x, T y) { x = x >= y ? x : y; }
template <typename T> void chkmin(T &x, T y) { x = x <= y ? x : y; }
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
constexpr int N = 1000001;
using ull = unsigned long long;
using HH = pair<unsigned long long, unsigned long long> ;
string s; 
HH base, Hash[N + 1]; 
constexpr HH mod = {1000000009, 1000000007};
HH operator*(const HH &a, const HH &b) {
  return {(a.first * b.first) % mod.first,
    (a.second*b.second)%mod.second};
}
HH operator+(const HH &a, const HH &b) {
  return {(a.first + b.first) % mod.first, 
    (a.second + b.second) % mod.second};
}
HH operator-(const HH &a, const HH &b) {
  return {(a.first - b.first + mod.first) % mod.first, 
    (a.second - b.second + mod.second) % mod.second
  };
//return{((a.first%mod.first)+mod.first-(b.first%mod.first))%mod.first,
//  ((a.second%mod.second)+mod.second-(b.second%mod.second))%mod.second};
}
HH operator*(const HH &a, const ull &b) {
  return {(a.first * b) % mod.first, (a.second * b) % mod.second};
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  base = {rnd() % mod.first, rnd() % mod.second};
  Hash[0] = {1, 1};
  for(int i = 1; i <= N; i ++ ) Hash[i] = Hash[i - 1] * base ;
  int n, q; cin >> n >> q >> s;
  
  vector<HH> a(n + 1), b(n + 1);
  a[0] = b[0] = {1, 1};
  for(int i = 1; i <= n; i ++ ) {
    a[i] = a[i - 1] * base + a[0] *  (s[i - 1] - 'a' + 1) ;
  }
  reverse(s.begin(), s.end());
 
  for(int i = 1; i <= n; i ++ ) {
    b[i] = b[i - 1] * base + b[0] *  (s[i - 1] - 'a' + 1);
  }
  auto get1 = [&] (int l, int r) {
    return a[r] - (a[l - 1] * Hash[r - l + 1]);
  };
 
  auto get2 = [&] (int l, int r) {
    return b[r] - (b[l - 1] * Hash[r - l + 1]);
  };
  while(q -- ) {
    int l, r; cin >> l >> r;
    int x = r - l + 1;
    bool flag = (get1(l, r) == get2(n - l - x + 2, n - l + 1));
    if(flag) cout << "Budada\n";
    else{
      if(x & 1) cout << "Putata\n";
      else cout << "Budada\n";
    }
  }
  return 0;
}