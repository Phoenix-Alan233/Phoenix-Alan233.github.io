#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int N = 100005;

bool is_square(ll x) {
    ll y = (ll)(sqrt(x) + 1e-6);
    return y * y == x;
}

int a[N], n, m;

struct SMT {
    #define ls (u << 1)
    #define rs (u << 1 | 1)

    ll seg_max[N << 2], seg_min[N << 2], seg_sum[N << 2];
    ll tag_add[N << 2];

    void pushup(int u) {
        seg_max[u] = max(seg_max[ls], seg_max[rs]);
        seg_min[u] = min(seg_min[ls], seg_min[rs]);
        seg_sum[u] = seg_sum[ls] + seg_sum[rs];
    }

    void pushtag(int u, int l, int r, ll num) {
        tag_add[u] += num;
        seg_max[u] += num, seg_min[u] += num;
        seg_sum[u] += (r - l + 1) * num;
    }

    void pushdown(int u, int l, int r) {
        if (tag_add[u]) {
            int mid = l + r >> 1;
            pushtag(ls, l, mid, tag_add[u]);
            pushtag(rs, mid + 1, r, tag_add[u]);
            tag_add[u] = 0;
        }
    }

    void build(int u, int l, int r) {
        tag_add[u] = 0;
        if (l == r) {
            seg_max[u] = seg_min[u] = seg_sum[u] = a[l];
            return;
        }
        int mid = l + r >> 1;
        build(ls, l, mid), build(rs, mid + 1, r);
        pushup(u);
    }

    void ADD(int u, int l, int r, int ql, int qr, int num) {
        if (ql <= l && r <= qr) {
            pushtag(u, l, r, num);
            return;
        }
        pushdown(u, l, r);
        int mid = l + r >> 1;
        if (ql <= mid) ADD(ls, l, mid, ql, qr, num);
        if (qr > mid) ADD(rs, mid + 1, r, ql, qr, num);
        pushup(u);
    }

    void SQRT(int u, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) {
            if (seg_min[u] == seg_max[u]) {
                ll new_val = sqrt(seg_min[u]);
                pushtag(u, l, r, new_val - seg_min[u]);
                return;
            }
            if (seg_min[u] + 1 == seg_max[u] && is_square(seg_max[u])) {
                ll new_val = sqrt(seg_max[u]);
                pushtag(u, l, r, new_val - seg_max[u]);
                return;
            }
        }
        pushdown(u, l, r);
        int mid = l + r >> 1;
        if (ql <= mid) SQRT(ls, l, mid, ql, qr);
        if (qr > mid) SQRT(rs, mid + 1, r, ql, qr);
        pushup(u);
    }

    ll query(int u, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return seg_sum[u];
        pushdown(u, l, r);
        int mid = l + r >> 1;
        ll res = 0;
        if (ql <= mid) res += query(ls, l, mid, ql, qr);
        if (qr > mid) res += query(rs, mid + 1, r, ql, qr);
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
            smt.ADD(1, 1, n, l, r, x);
        } else if (opt == 2) {
            smt.SQRT(1, 1, n, l, r);
        } else {
            cout << smt.query(1, 1, n, l, r) << '\n';
        }
    }
    return 0;
}