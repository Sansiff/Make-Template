// code by Sansi
// luogu p3835
#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 10;
int rt[N], cnt;
std::mt19937 rnd(233);
struct node{
	int l, r, val, key, size;
}tr[N * 50];
int new_node(int val){
	tr[++cnt].val = val;
	tr[cnt].key = rnd();
	tr[cnt].size = 1;
	return cnt;
}
void pushup(int u){
	tr[u].size = tr[tr[u].l].size + tr[tr[u].r].size + 1;
}
void split(int u, int val, int& x, int& y){
	if(!u){
		x = y = 0; return;
	}
	if(tr[u].val <= val){
		x = ++ cnt; tr[x] = tr[u];
		split(tr[x].r, val, tr[x].r, y);
		pushup(x);
	}
	else{
		y = ++ cnt; tr[y] = tr[u];
		split(tr[y].l, val, x, tr[y].l);
		pushup(y);
	}
}
int merge(int x, int y){
	if(!x || !y) return x + y;
	if(tr[x].key > tr[y].key){
		int p = ++ cnt; tr[p] = tr[x];
		tr[p].r = merge(tr[p].r, y);
		pushup(p); return p;
	}
	else{
		int p = ++ cnt; tr[p] = tr[y];
		tr[p].l = merge(x, tr[p].l);
		pushup(p); return p;
	}
}
void insert(int& root, int val){
	int x, y, z;
	split(root, val, x, y);
	z = new_node(val);
	root = merge(merge(x, z), y);
}
void Delete(int& root, int val){
	int x, y, z;
	split(root, val, x, z);
	split(x, val - 1, x, y);
	y = merge(tr[y].l, tr[y].r);
	root = merge(merge(x, y), z);
}
int Rank(int& root, int val){
	int x, y;
	split(root, val - 1, x, y);
	int res = tr[x].size + 1;
	root = merge(x, y);
	return res;
}
int K_th(int& root, int k){
	int u = root;
	while(u){
		if(tr[tr[u].l].size + 1 == k)
			break;
		else if(tr[tr[u].l].size >= k)
			u = tr[u].l;
		else{
			k -= tr[tr[u].l].size + 1;
			u = tr[u].r;
		}
	}
	return tr[u].val;
}
int pre(int& root, int val){
	int x, y, k, res;
	split(root, val - 1, x, y);
	if(!x) return -2147483647;
	k = tr[x].size;
	res = K_th(x, k);
	root = merge(x, y);
	return res;
}
int nex(int& root, int val){
	int x, y, res;
	split(root, val, x, y);
	if(!y) return 2147483647;
	else res = K_th(y, 1);
	root = merge(x, y);
	return res;
}
void solve(){
	int n; cin >> n;
    for(int i = 1; i <= n; i ++){
        int t, op, x; cin >> t >> op >> x;
      	rt[i] = rt[t];
        if(op == 1) insert(rt[i], x);
        if(op == 2) Delete(rt[i], x);
        if(op == 3) cout << Rank(rt[t], x) << '\n';
        if(op == 4) cout << K_th(rt[t], x) << '\n';
        if(op == 5) cout << pre(rt[t], x) << '\n';
        if(op == 6) cout << nex(rt[t], x) << '\n';
    }
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); 
    solve();
    return 0;
}