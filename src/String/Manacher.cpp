// https://www.acwing.com/problem/content/description/141/
#include <bits/stdc++.h>
using namespace std;

constexpr int N = 2000010;

int n, m, Case;
char s[N], str[N];
int p[N];

int manacher() {
  int rt = 0, mid = 0;
  int res = 0;
  for(int i = 1; i <= m; i ++ ) {
    p[i] = i < rt ? min(p[2 * mid - i], rt - i) : 1;
    while(str[i + p[i]] == str[i - p[i]]) ++ p[i];
    if(i + p[i] > rt) {
      rt = i + p[i];
      mid = i;
    }
    res = max(res, p[i] - 1);
  }
  return res;
}

int main() {
  str[0] = '!', str[1] = '#';
  while(scanf("%s", s), s[0] != 'E') {
    n = strlen(s);
    for(int i = 0; i < n; i ++ ) {
      str[i * 2 + 2] = s[i];
      str[i * 2 + 3] = '#';
    }
    m = n * 2 + 1;
    str[m + 1] = '@';
    printf("Case %d: %d\n", ++ Case, manacher());
  }
  return 0;
}
