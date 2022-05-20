/*---KD-Tree---*/
template<class T>
inline T sqr(T&x){return x*x;}
namespace KDT { 
    const int N = 1e5 + 10, M = N << 1;
#define lc ch[x][0]
#define rc ch[x][1]
  struct pnt {
    int x[2];
  }a[N];
  int opt;
  struct node { 
    int dis; 
    node(int a = 0) { 
      dis = a; 
    }
    inline bool operator <(const node& other)const { return dis > other.dis; } 
  };//??? 
  priority_queue<node>q;
  int ans;
  inline bool cmp(register pnt a, register pnt b) { return a.x[opt] < b.x[opt]; }
  inline int f(pnt a, pnt b) { return sqr(a.x[0] - b.x[0]) + sqr(a.x[1] - b.x[1]); }
  int ch[M][2], minn[M][2], maxn[M][2], cnt;
  pnt*d[M];
  inline void pushup(const int&x) {
    for (int i = 0; i < 2; ++i)
      maxn[x][i] = minn[x][i] = d[x]->x[i];
    if (lc)
      for (int i = 0; i < 2; ++i)
        maxn[x][i] = max(maxn[x][i], maxn[lc][i]), 
        minn[x][i] = min(minn[x][i], minn[lc][i]);
    if (rc)
      for (int i = 0; i < 2; ++i)
        maxn[x][i] = max(maxn[x][i], maxn[rc][i]), 
        minn[x][i] = min(minn[x][i], minn[rc][i]);
  }inline int build(int L, int R, int k) {
    if (L > R)return 0;
    int x = ++cnt; 
    opt = k;
    int mid = (L + R) >> 1;
    nth_element(a + L, a + mid, a + R + 1, cmp);
    d[x] = &a[mid];
    lc = build(L, mid - 1, k ^ 1), rc = build(mid + 1, R, k ^ 1);
    pushup(x);
  }inline int mindis(pnt&a, int b) {
    return sqr(max(a.x[0]-maxn[b][0],0)+max(minn[b][0]-a.x[0],0))+sqr(max(a.x[1]-maxn[b][1],0)+max(minn[b][1]-a.x[1],0));
  }inline int maxdis(pnt&a, int b) {//????
    return max(sqr(maxn[b][0] - a.x[0]), sqr(minn[b][0] - a.x[0])) + max(sqr(maxn[b][1] - a.x[1]), sqr(minn[b][1] - a.x[1]));
   }inline void kqueryMax(int x, pnt&O) {//k?????
     if(!x)return;
    int dl = -inf, dr = -inf;
   	if (lc)dl = maxdis(O, lc);
      if (rc)dr = maxdis(O, rc);
      if (d[x] != &O) {
        int dis = f(*d[x], O);
        if (q.top().dis < dis)
          q.pop(), q.push(dis);
      }
      if (dl > dr) { 
        if (q.top().dis < dl)kqueryMax(lc, O); 
        if (q.top().dis < dr)kqueryMax(rc, O); 
      }
      else { 
        if (q.top().dis < dr)kqueryMax(rc, O); 
        if (q.top().dis < dl)kqueryMax(lc, O); 
      }
   }inline void queryMin(int x, pnt&O) {//????
     if (!x)return;
     int dl = inf, dr = inf;
     if (lc)dl = mindis(O, lc);
     if (rc)dr = mindis(O, rc);
     if (d[x] != &O)//??????
        ans = min(ans, f(*d[x], O));
     if (dl < dr) {
       if (dl < ans)queryMin(lc, O);
       if (dr < ans)queryMin(rc, O);
     }
     else {
       if (dr < ans)queryMin(rc, O);
       if (dl < ans)queryMin(lc, O);
     }
   }inline void queryMax(int x, pnt& O) {//????
     if (!x)return;
     int dl = -inf, dr = -inf;
     if (lc)dl = maxdis(O, lc);
     if (rc)dr = maxdis(O, rc);
     if (d[x] != &O)//??????
        ans = max(ans, f(*d[x], O));
     if (dl > dr) {
       if (ans < dl)queryMax(lc, O);
       if (ans < dr)queryMax(rc, O);
     }
     else {
       if (ans < dr)queryMax(rc, O);
       if (ans < dl)queryMax(lc, O);
     }
  }
#undef lc
#undef rc 
}
