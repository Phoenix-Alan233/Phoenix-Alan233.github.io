#include <bits/stdc++.h>
using namespace std;

const int N = 500005;

int a[N], n, m;

struct SMT {
    #define ls (u << 1)
    #define rs (u << 1 | 1)

    int seg_and[N << 2], seg_or[N << 2], seg_min[N << 2];
    int tag_cov[N << 2];

    void pushup(int u) {
        seg_and[u] = seg_and[ls] & seg_and[rs];
        seg_or[u] = seg_or[ls] | seg_or[rs];
        seg_min[u] = min(seg_min[ls], seg_min[rs]);
    }

    void pushtag(int u, int num) {
        tag_cov[u] = num;
        seg_and[u] = seg_or[u] = seg_min[u] = num; 
    }

    void pushdown(int u) {
        if (tag_cov[u] != -1) {
            pushtag(ls, tag_cov[u]);
            pushtag(rs, tag_cov[u]);
            tag_cov[u] = -1;
        }
    }

    void build(int u, int l, int r) {
        tag_cov[u] = -1;
        if (l == r) {
            seg_and[u] = seg_or[u] = seg_min[u] = a[l];
            return;
        }
        int mid = l + r >> 1;
        build(ls, l, mid), build(rs, mid + 1, r);
        pushup(u);
    }

    // 区间 [ql, qr] & num
    void AND(int u, int l, int r, int ql, int qr, int num) {
        if ((seg_or[u] & num) == seg_or[u]) return;
        if (ql <= l && r <= qr && 
            (seg_and[u] & num) == (seg_or[u] & num)) {
            pushtag(u, seg_and[u] & num);
            return;
        }
        pushdown(u);
        int mid = l + r >> 1;
        if (ql <= mid) AND(ls, l, mid, ql, qr, num);
        if (qr > mid) AND(rs, mid + 1, r, ql, qr, num);
        pushup(u);
    }

    // 区间 [ql, qr] | num
    void OR(int u, int l, int r, int ql, int qr, int num) {
        if ((seg_and[u] | num) == seg_and[u]) return;
        if (ql <= l && r <= qr && 
            (seg_and[u] | num) == (seg_or[u] | num)) {
            pushtag(u, seg_and[u] | num);
            return;
        }
        pushdown(u);
        int mid = l + r >> 1;
        if (ql <= mid) OR(ls, l, mid, ql, qr, num);
        if (qr > mid) OR(rs, mid + 1, r, ql, qr, num);
        pushup(u);
    }

    // 查询 [ql, qr] min
    int query(int u, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) {
            return seg_min[u];
        }
        pushdown(u);
        int res = INT_MAX;
        int mid = l + r >> 1;
        if (ql <= mid) res = query(ls, l, mid, ql, qr);
        if (qr > mid) res = min(res, query(rs, mid + 1, r, ql, qr));
        return res;
    }
} smt;

int main() {
    ios::sync_with_stdio(false), cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    smt.build(1, 1, n);

    while (m--) {
        int opt, l, r; cin >> opt >> l >> r;
        if (opt == 1) {
            int x; cin >> x;
            smt.AND(1, 1, n, l, r, x);
        } else if (opt == 2) {
            int x; cin >> x;
            smt.OR(1, 1, n, l, r, x);
        } else {
            cout << smt.query(1, 1, n, l, r) << '\n';
        }
    }
    return 0;
}