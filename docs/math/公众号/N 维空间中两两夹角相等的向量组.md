# N 维空间中两两夹角相等的向量组

!!! warning "温馨提醒"
    本文写于 2022.10.15 21:00，并同步投稿于个人公众号。

    近期在整理时有细微调整（包括标题，改得更加具体）。

<div style="text-align: center; font-size: 1.5em; font-weight: bold; margin: 1em 0;">
N 维空间中两两夹角相等的向量组
</div>

<div style="text-align: center; font-size: 1.1em; margin: 1em 0;">
杭州二中 小 Z
</div>

## 问题引入

上课的时候，老师讲到一道题：

> 空间中四个不共线的单位向量两两夹角均为 $\theta$，求 $\cos \theta$ 的值。

我很自然地想到正四面体，从它体心出发的四根向量便符合条件，此时 $\cos \theta=-\frac 13$。

但是，我并不明白为何答案唯一，然而我更在乎的是：如果变成 $n$ 个单位向量，那答案又如何呢？

我追问了老师，结果发现我小丑了：$n$ 从 $5$ 开始就不存在了。

我很不服。对此，我进行了深入的探究。

## 引理

> **引理** 在 $N$ 维欧式空间中，两两互成钝角的非零向量至多 $N+1$ 个。

**证明** 反证法，假设至少有 $N+2$ 个，记其中 $N+2$ 个为 $\vec {a_1},\cdots,\vec {a_{N+2}}$，不妨设它们为单位向量。

在 $\mathbb R^N$ 下，最多有 $N$ 个线性无关的向量。故必存在不全为零的系数 $k_1,\cdots,k_{N+1}$ 满足 $\sum\limits_{i=1}^{N+1}k_i\vec{a_i}=0$。

因此 $\sum\limits_{i=1}^{N+1}k_i(\vec{a_i}\cdot \vec{a_{N+2}})=0$，由于 $\cos\langle \vec{a_i},\vec{a_{N+2}}\rangle <0$，因此必定存在 $k>0$ 和 $k<0$。

不妨将这些 $\vec{a_i}$ 按照 $k_i$ 的正负性重新排列，使得 $k_1\sim k_p>0$，$k_{p+1}\sim k_q<0$，$k_{q+1}\sim k_N=0$。

设 $\vec S=\sum\limits_{i=1}^{p}k_i\vec{a_i}=-\sum\limits_{i=p+1}^qk_i\vec{a_i}$，则

$$
\vec S^2=-\sum\limits_{i=1}^{p}\sum\limits_{j=p+1}^q k_ik_j(\vec{a_i}\cdot \vec{a_j})<0
$$

而显然 $\vec S^2\ge 0$，矛盾。

（这也说明 $k_i$ 必须均 $\ge 0$ 或均 $\le 0$ 才可行）

接下来给出一组 $N+1$ 个向量的构造：

$$
\begin{aligned}
\vec{a_k}&=(1,2^1,2^2,\cdots,2^{k-2},-2^{k-1},0,\cdots,0), & &1\le k\le N \\
\vec{a_{N+1}}&=(1,2^1,2^2,\cdots,2^N), & &k=N+1
\end{aligned}
$$

（约定 $k=1$ 时前面的项为空，即 $\vec{a_1}=(-1,0,\cdots,0)$）

容易验证 $\vec {a_i}\cdot \vec {a_j}<0\ (1\le i< j\le N+1)$。

## 主要命题

> **命题** 在 $N$ 维欧式空间中，不共线且两两夹角相等的向量至多 $N+1$ 个，且 $\cos \theta=-\frac{1}{N}$。

### 锐角的情形

设有 $n$ 个向量，我们先说明它们线性无关。

设一组系数 $k_1,\cdots,k_n$ 满足 $\sum\limits_{i=1}^{n}k_i\vec{a_i}=0$，设 $\lambda=\cos \theta$，则

$$
\left(\begin{matrix}1 & \lambda & \cdots & \lambda \\ \lambda & 1 & \cdots & \lambda \\ \vdots & \vdots & \ddots & \vdots \\ \lambda & \lambda & \cdots & 1\end{matrix}\right)\left(\begin{matrix}k_1 \\ k_2 \\ \cdots \\ k_n\end{matrix}\right)=0
$$

令左边的矩阵为 $D(\lambda)$，则 $\det (D(\lambda))=(1-\lambda)^{n-1}(1+(n-1)\lambda)>0$，因此 $k_i=0$，即线性无关。

紧接着，我们说明 $n\le N$。由于 $D(\lambda)$ 是正定实对称矩阵，故存在 $n$ 阶实对称矩阵 $P$，使得 $D(\lambda)=PP^T$，取 $\mathbb R^N$ 的一组基底 $\vec{e_1},\cdots,\vec{e_N}$，则：

$$
\left(\begin{matrix}\vec {a_1} \\ \vec{a_2} \\ \cdots \\ \vec{a_n}\end{matrix}\right)=P\left(\begin{matrix}\vec {e_1} \\ \vec{e_2} \\ \cdots \\ \vec{e_n}\end{matrix}\right)
$$

由于 $\operatorname{rank}(P)\le n$ 且 $\{\vec{a_1},\cdots,\vec{a_n}\}$ 线性无关，因此 $n\le N$。

### 钝角的情形

由**引理**知答案至多 $N+1$，这里给出一组构造：

$$
(\vec{a_i})_j=\begin{cases}-\dfrac{1+\sqrt{\frac{1}{N+1}}}{N}, & i\neq j \\[6pt]
1-\dfrac{1+\sqrt{\frac{1}{N+1}}}{N}, & i=j\end{cases}
$$

容易验证 $|\vec a_i|=1$，且 $\cos\langle \vec{a_i},\vec{a_j}\rangle =-\frac{1}{N}\ (1\le i<j\le N+1)$。

最后证明 $\cos \theta$ 唯一。取 $\mathbb R^N$ 的一组基底 $\vec{e_1},\cdots,\vec{e_N}$，则存在 $P\in \mathbb R^{(N+1)\times N}$ 满足：

$$
\left(\begin{matrix}\vec {a_1} \\ \vec{a_2} \\ \cdots \\ \vec{a_{N+1}}\end{matrix}\right)=P\left(\begin{matrix}\vec {e_1} \\ \vec{e_2} \\ \cdots \\ \vec{e_N}\end{matrix}\right)
$$

于是

$$
P P^T=\left(\begin{matrix}1 & \lambda & \cdots & \lambda \\ \lambda & 1 & \cdots & \lambda \\ \vdots & \vdots & \ddots & \vdots \\ \lambda & \lambda & \cdots & 1\end{matrix}\right)
$$

分析知 $\det(PP^T)=(1-\lambda)^N(1+N\lambda)=0$，而 $\lambda\in (-1,0)$，因此 $\lambda=-\frac{1}{N}$。
