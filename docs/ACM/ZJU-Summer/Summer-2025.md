
## ZJU Summer 2025 Contest 4 by Group A

- 提交通道：https://codeforces.com/group/MIyYz3rj9b/contest/620808

| # | Problem | Tag | Difficulty | Completion |
| :---: | :---: | :---: | :---: | :---: |
| A | Counting Stars | 构造 | 蓝 | $\checkmark$ |
| C | Reset the Circular Ring | 数学 | 橙 | $\checkmark$ |
| D | XOR Distance Sum | 点分治，01-Trie | 蓝 | $\checkmark$ |
| E | Highbit of XOR | 思维，01-Trie | 紫 | 没调出来 |

### A. Counting Stars

> 定义一款语言，仅由一种指令构成，`pattern:replacement` 表示找到当前串 $S$ 中最早出现的 `pattern`，并替换为 `replacement`。每次匹配完，该语言就从头开始重新执行，直至执行完最后一条指令。
>
> 如 `b:c a:b` 可以将 abc 串 $S$ 变为全 c 串；`a: b:` 可以将 bac 串 $S$ 中的 a、b 剔除，只留下 c。
>
> 现在我们要使用该语言，读入一个串 $S$，输出 $|S|$。


一个平凡模拟进位（逢十进一）的构造如下，注意需要特别处理数字 $0$ 的情况，但这题限制设置不太合理，在 $|S|=1$ 的时候步数会爆（刚好差 1），但整体所需的步数要比后者短很多，$|S|=1000$ 时不超过 1800 步。

```
c:a
b:a
#aaaaaaaaaaa:a#a
#aaaaaaaaaa:a#0
aaaaaaaaaa:#aaaaaaaaaa
aaaaaaaaa:9
aaaaaaaa:8
aaaaaaa:7
aaaaaa:6
aaaaa:5
aaaa:4
aaa:3
aa:2
a:1
#:
```

下面这种做法就更加自然，不过步数不超过 10000 步，毕竟是 O(答案) 的。

```
b:a
c:a
0a:1
1a:2
2a:3
3a:4
4a:5
5a:6
6a:7
7a:8
8a:9
9a:a0
a:1
```

### D. XOR Distance Sum

> 给定一棵 $n$ 个节点的树，对于每个节点 $i$，定义 $f(i)=\oplus_{j=1}^{n} \text{dist}(i,j)$，其中 $\text{dist}(i,j)$ 表示节点 $i$ 到节点 $j$ 的简单路径长度。计算 $f(1),f(2),\cdots,f(n)$。
> 
> $1\le n\le 10^5$。

比较经典的点分治题，每次计算跨越当前联通块重心的点对距离贡献，这里涉及 01-Trie，并需要支持全体 $+1$ 的操作，这可以通过在插入时，从低位往高位插进 01-Trie 树做到。

时间复杂度 $O(n\log^2n)$。

??? note "Code"
    ```cpp
    const int N = 100005;

    vector<int> adj[N];
    int ans[N], n;

    bool ban[N];
    int sz[N], maxs[N], tot_sz, rt;
    void getrt(int u, int fa) {
        sz[u] = 1, maxs[u] = 0;
        for (auto v : adj[u]) {
            if (v == fa || ban[v]) continue;
            getrt(v, u);
            sz[u] += sz[v];
            if (sz[v] > sz[maxs[u]]) maxs[u] = v;
        }
        if (max(sz[maxs[u]], tot_sz - sz[u]) * 2 <= tot_sz) rt = u;
    }

    namespace TREE {
    const int M = 18 * N;
    int ch[M][2], sz[M], val[M], rt, tot;
    void ins(int &u, int bit, int num) {
        if (!u) u = ++tot, ch[u][0] = ch[u][1] = 0, sz[u] = val[u] = 0;
        sz[u]++, val[u] ^= num >> bit;
        if (bit == 18) return;
        int which = num >> bit & 1;
        ins(ch[u][which], bit + 1, num);
    }
    void add1(int u, int bit) {
        if (!u) return;
        if (bit == 18) return;
        swap(ch[u][0], ch[u][1]);
        add1(ch[u][0], bit + 1);
        val[u] = ((val[ch[u][0]] ^ val[ch[u][1]]) << 1) | (sz[ch[u][1]] & 1 ? 1 : 0);
    }
    }

    vector<int> depth[N];
    void dfs1(int u, int fa, int dep) {
        depth[dep].push_back(u);
        TREE::ins(TREE::rt, 0, dep);
        for (auto v : adj[u]) {
            if (v == fa || ban[v]) continue;
            dfs1(v, u, dep + 1);
        }
    }

    void dfz(int u) {
        ban[u] = 1;
        // printf("dfz %d\n", u);

        // 剔除这部分贡献
        for (auto v : adj[u]) {
            if (ban[v]) continue;
            TREE::rt = TREE::tot = 0;
            dfs1(v, u, 1);
            for (int dep = 1; ; dep++) {
                if (depth[dep].empty()) break;
                TREE::add1(TREE::rt, 0);
                for (auto x : depth[dep]) {
                    // printf("del x = %d, val = %d\n", x, TREE::val[TREE::rt]);
                    ans[x] ^= TREE::val[TREE::rt];
                }
                depth[dep].clear();
            }
        }

        // 增加这部分贡献
        TREE::rt = TREE::tot = 0;
        depth[0].push_back(u);
        TREE::ins(TREE::rt, 0, 0);
        for (auto v : adj[u]) {
            if (ban[v]) continue;
            dfs1(v, u, 1);
        }
        for (int dep = 0; ; dep++) {
            if (depth[dep].empty()) break;
            if (dep) TREE::add1(TREE::rt, 0);
            for (auto x : depth[dep]) {
                // printf("ins x = %d, val = %d\n", x, TREE::val[TREE::rt]);
                ans[x] ^= TREE::val[TREE::rt];
            }
            depth[dep].clear();
        }
        
        int tmp_tot_sz = tot_sz;
        for (auto v : adj[u]) {
            if (ban[v]) continue;
            tot_sz = sz[v] < sz[u] ? sz[v] : tmp_tot_sz - sz[u];
            getrt(v, u), dfz(rt);
        }
    }

    int main() {
        n = IO::read();
        for (int i = 1; i < n; i++) {
            int u = IO::read(), v = IO::read();
            adj[u].push_back(v), adj[v].push_back(u);
        }
        tot_sz = n, getrt(1, 0), dfz(rt);
        for (int i = 1; i <= n; i++) {
            IO::print(ans[i], '\n');
        }
        return 0;
    }
    ```

## ZJU Summer 2025 Contest 5 by Group C

- 提交通道：https://codeforces.com/group/MIyYz3rj9b/contest/621587

| # | Problem | Tag | Difficulty | Completion |
| :---: | :---: | :---: | :---: | :---: |
| A | Explosion | 数学 | 绿 | $\checkmark$ |
| B | Games | 贪心 | 蓝 | $\checkmark$ |
| C | City | 整体二分，莫比乌斯反演 | 紫 | $\checkmark$ |
| F | $\pi$-mon Polygon 2 | 计算几何 | 蓝 | $\checkmark$ |

### C. City

> 给定一个长为 $n$ 的序列 $A$，对于 $i=1,2,\cdots,n$ 分别求出最大的 $A_j$，满足 $\gcd(A_i,A_j)=1$。
>
> $2\le n\le 3\times 10^5$，$1\le a_i\le 3\times 10^5$。

考虑整体二分，记所有可能的答案为 $\text{b}$，设当前需要查询 $\text{ask}$ 下标集合内的答案，并且已知答案在 $\text{b}[l..r]$ 中，那么我们要判断的无非就是：

- 取 $\text{mid}=\lfloor \frac{l+r}{2}\rfloor$，对 $\text{ask}$ 中每个下标对应的数 $x$，判断 $\sum\limits_{i=mid+1}^{r} [\gcd(b_i,x)=1]$ 是否大于 0。

对于该式子的快速计算，可以用莫比乌斯反演，得到：

$$
\begin{aligned}
\sum\limits_{i=mid+1}^{r} [\gcd(b_i,x)=1]&=\sum\limits_{i=mid+1}^{r} \sum_{g|b_i,g|x} \mu(g) \\
&=\sum\limits_{g|x} \mu(g) \sum\limits_{i=mid+1}^{r} [g|b_i]
\end{aligned}
$$

我们只用考虑 $\mu(g)\neq 0$ 的位置，这一共有 $2^{\omega(A)}$ 个，在该数据范围下 $\omega(A)\le 6$；对于后半部分，我们可以在整体二分的时候预处理。

总时间复杂度 $O(n2^{\omega(A)}\log n)$。

??? note "Code"
    ```cpp
    const int N = 300005;

    vector<int> inz[N];
    vector<int> candidate;
    int a[N], ans[N], n;

    void init(int n) {
        static bool vis[N];
        for (int i = 2; i <= n; i++) {
            if (!vis[i]) {
                inz[i].push_back(i);
                for (int j = i + i; j <= n; j += i) {
                    inz[j].push_back(i);
                    vis[j] = 1;
                }
            }
        }
    }

    int bucket[N];
    void dfs1(vector<int> &inz, int ind, int num, int coef) {
        if (ind == inz.size()) {
            bucket[num] += coef;
            return;
        }
        dfs1(inz, ind + 1, num, coef);
        dfs1(inz, ind + 1, num * inz[ind], coef);
    }

    int cnt;
    void dfs2(vector<int> &inz, int ind, int num, int mu) {
        if (ind == inz.size()) {
            cnt += mu * bucket[num];
            return;
        }
        dfs2(inz, ind + 1, num, mu);
        dfs2(inz, ind + 1, num * inz[ind], -mu);
    }

    // 查询 ask (下标集合) 的答案，且答案是 candidate[L..R] 中的某一个 
    void solve(int L, int R, vector<int> ask) {
        if (ask.empty()) return;
        if (L == R) {
            for (auto ind : ask) {
                ans[ind] = candidate[L];
            }
            return;
        }
        // printf("solve [%d, %d], ask = ", L, R);
        // for (auto it : ask) printf("%d ", it);
        // printf("\n");
        int mid = (L + R) / 2;
        for (int i = mid + 1; i <= R; i++) {
            dfs1(inz[candidate[i]], 0, 1, 1);
        }
        vector<int> askL, askR;
        for (auto it : ask) {
            cnt = 0;
            dfs2(inz[a[it]], 0, 1, 1);
            if (cnt > 0) askR.push_back(it);
            else askL.push_back(it);
        }
        for (int i = mid + 1; i <= R; i++) {
            dfs1(inz[candidate[i]], 0, 1, -1);
        }
        solve(L, mid, askL);
        solve(mid + 1, R, askR);
    }

    int main() {
        n = IO::read();

        init(300000);
        for (int i = 0; i < n; i++) {
            a[i] = IO::read();
            candidate.push_back(a[i]);
        }
        sort(candidate.begin(), candidate.end());
        candidate.erase(unique(candidate.begin(), candidate.end()), candidate.end());
        
        vector<int> ask;
        for (int i = 0; i < n; i++) {
            ask.push_back(i);
        }
        solve(0, candidate.size() - 1, ask);

        for (int i = 0; i < n; i++) {
            IO::print(ans[i]);
            IO::pc(" \n"[i == n - 1]);
        }
        return 0;
    }
    ```
