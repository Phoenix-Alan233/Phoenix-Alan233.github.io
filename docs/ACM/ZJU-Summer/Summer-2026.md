## ZJU Summer 2026 Contest 1 by Group C

- 提交通道：https://codeforces.com/gym/702737
  
| # | Problem | Tag | Difficulty | Completion |
| :---: | :---: | :---: | :---: | :---: |
| B | Crack RSA | 高精度，数论 | 黑 | $\checkmark$ |
| C | Disjoint LIS and LDS | 线段树，哈希 | 蓝 | $\checkmark$ |
| E | Cross | 贪心 | 绿 | $\checkmark$ |

## ZJU Summer 2026 Contest 2 by Group A

- 提交通道：https://codeforces.com/gym/702920

| # | Problem | Tag | Difficulty | Completion |
| :---: | :---: | :---: | :---: | :---: |
| B | Lyndonization | 构造 | 绿 | $\checkmark$ |
| C | Cool P #1 | 线性基 | 蓝 | $\checkmark$ |
| F | Subtree Capacity | 贪心，扫描线，线段树，树链剖分 | 紫 | $\checkmark$ |

## ZJU Summer 2026 Contest 3 by Group B

- 提交通道：https://codeforces.com/gym/703113

| # | Problem | Tag | Difficulty | Completion |
| :---: | :---: | :---: | :---: | :---: |
| C | Hard Performance Measurement (A+B) | 构造 | 绿 | $\checkmark$ |
| D | ez-version | 01-bfs | 绿 | $\checkmark$ |
| E | Does It Divide? | 数学，线性筛 | 蓝 | $\checkmark$ |

## ZJU Summer 2026 Contest 6 by Group A

- 提交通道：https://codeforces.com/gym/704280 
  
| # | Problem | Tag | Difficulty | Completion |
| :---: | :---: | :---: | :---: | :---: |
| A | Odd Cycle or 3-Coloring | 构造 | 紫 | $\checkmark$ |
| C | Sunbath | 构造，数学，二分 | 蓝 | $\checkmark$ |
| D | Cover the Paths | 贪心，树状数组 | 青 | $\checkmark$ |
| E | Dominant Sequence | 构造 | 黄 | $\checkmark$ |

### A. Odd Cycle or 3-Coloring 

> 给定一个 $n$ 个点 $m$ 条边的无向连通图，我们称一个环是 safely removable 的当且仅当删除环上所有边后，该图仍连通。
>
> 现在你可以选择做以下两个任务：
>
> - task 1：将图上每个点三染色，使得每条边两端点的颜色不同；
>
> - task 2：找出一个**奇环** 满足它是 safely removable 的。
>
> 可以证明这两个任务至少有一个是可达成的，$1\le n\le 10^5$，$1\le m\le 2\cdot 10^5$。

我们先考虑**四染色**，抠出原图的一棵 dfs 树，只考虑剩下的返祖边，如果这些边出现了奇环，那么 task 2 做完了；接下来我们考虑是**二分图**的情形，此时原本 dfs 树、返祖边构成的二分图都可以黑白染色，两个 0/1 bit 压缩成一个 2-bit 数即可实现四染色。

但至此我们思考可以怎么节省一个颜色，可以在生成树的选取下功夫。我们希望非树边的类型比较独特，比如不存在“黑黑边”（这里的“黑”是指生成树上的染色），这样生成树上的黑色记为 1，白色依非树边的二分图染色划分为 2/3。考虑这样一个生成树的构造方案：把一个点染黑，把它的邻居同时全染白；再找一个与白点相邻、尚未访问的点染黑，把它未访问的邻居全染白，如此进行即可。

### C. Sunbath

> 这是一道**交互题**。有一张 $n$ 个点的竞赛图，但你不知道具体长啥样。每次你可以询问两个不交的非空点集 $A,B$，交互器会返回有多少条边从 $A$ 指向 $B$。
>
> 现在你需要花不超过 $2n+150$ 次询问，找到一个点集 $K$，满足 $|K|\le \lceil \log_2 n\rceil+1$，且对于任何 $v\notin K$，存在某个 $u\in K$ 使得 $(u,v)$ 是图中的有向边。
>
> $1\le n\le 2000$。

交互题多半是二分，而且看到 $|K|$ 的限制更加确信。记 $S=\{1,2,\cdots,n\}$，我们时刻考虑 $S$ 的导出子图，由抽屉原理存在某个点的出度 $\ge \frac{|S|-1}{2}$，取它放入 $K$，就能让 $S'$ 大小砍半，进而在 $\log n$ 次内结束。

那么怎么找到这样的点呢？我们可以二分点集 $S$，先将其等分成左右两半 $S_L,S_R$，然后查询 $S_L,S_R$，这样我们就知道 $S_L\to S_R$ 的边数，反过来是可以算出来的，比谁多就往哪儿递归，最后剩余一个点，就是我们想要的点 $P$，显然这样就是对的。

接着挨个询问 $S$ 中的点 $x$，查询 $\{P\}\to \{x\}$ 是否为 1，留下为 0 的作为新的 $S'$，然后递归做子问题即可。

总询问次数 $2n+(\log n)^2$。
