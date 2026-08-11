# Chapter 5. 优化算法

!!! 参考文献
    - 动手学深度学习
        - [72 优化算法](https://www.bilibili.com/video/BV1bP4y1p7Gq)


优化问题的一般形式是 minimize $f(\textbf{x})$，subject to $\textbf{x} \in C$，其中：

- 目标函数 $f: \mathbb{R}^n \to \mathbb{R}$
- 限制集合 $C=\{ \textbf{x}\ |\ h_1(\textbf{x})=0,\cdots,h_m(\textbf{x})=0,g_1(\textbf{x})\le 0,\cdots,g_r(\textbf{x})\le 0 \}$
    - 当然如果 $C=\mathbb{R}^n$，那就是不受限

通常来说，$f$ 不是线性泛函，而且 $\textbf{x}$ 中的参数量很大，很难得到全局最小 $\textbf{x}^*$，只能求局部最小 $\textbf{x}^*$，一般使用**迭代优化算法**来求解。

如果 $f$ 是凸函数，且 $C$ 也是凸的，这就是凸优化问题，此时局部最小一定是全局最小。这看上去非常拽，但显然哪有这种好事，机器学习中 $f$ 只有两类最基本的 case 是凸的——线性回归以及 Softmax 回归，其余基本都非凸。

## 随机梯度下降 SGD

先谈**梯度下降**，它是最简单的迭代求解算法。首先选取起始点 $\textbf{x}_0$，接着对于 $t=1,2,\cdots,T$，令 $\textbf{x}_t=\textbf{x}_{t-1}-\eta \cdot \nabla f(\textbf{x}_{t-1})$，这里 $\eta$ 是学习率（一个超参数）。

~~但同样理想很美满，现实很骨感。~~

当有 $n$ 个样本时，计算 $f(\textbf{x})=\frac{1}{n} \sum\limits_{i=0}^{n-1} \ell_i(\textbf{x})$ 的梯度太昂贵，所以我们就**随机挑一个样本代替整体**，它的数学道理就是 $\mathbb{E}(\nabla \ell_{t_i}(\textbf{x}))=\mathbb{E}(\nabla f(\textbf{x}))$。

具体而言，**随机梯度下降**会在时间 $t$，随机选择样本 $t_i$ 来近似 $f(\textbf{x})$，$\textbf{x}_t=\textbf{x}_{t-1}-\eta \nabla \ell_{t_i}(\textbf{x}_{t-1})$。

## 小批量随机梯度下降 Mini-Batch SGD

SGD 虽然提高了计算效率，降低了计算开销，但是它由于每次只选择一个样本，随机性比较大，下降的过程可能会非常曲折；而且计算单样本的梯度难以完全利用硬件资源。于是就有了**小批量随机梯度下降**，我们在实际应用中也会采用这个方法。

**小批量随机梯度下降**在时间 $t$ 随机挑选 $b$ 个样本，记作子集 $I_t$，$|I_t|=b$，那么 $\textbf{x}_t=\textbf{x}_{t-1}-\frac{\eta}{b} \sum\limits_{i\in I_t} \nabla \ell_i(\textbf{x}_{t-1})$。


## 动量法 Momentum

考虑对 Mini-Batch SGD 进一步优化。我们之前都只聚焦于当前的权重（即 $\textbf{x}_{t-1}$），而忽略了过去，现在设计一个手段融合所有时刻 $<t$ 的权重进去，这就有了**动量法**。

**动量法**使用平滑过的梯度，对权重进行更新：

- $\textbf{g}_t=\frac{1}{b} \sum\limits_{i\in I_t} \nabla \ell_i(\textbf{x}_{t-1})$
- $\textbf{v}_t=\beta \textbf{v}_{t-1} + \textbf{g}_t$
- $\textbf{x}_t=\textbf{x}_{t-1}-\eta \textbf{v}_t$

这里的 $\textbf{v}_t$ 相当于**梯度平滑**，数值上 $\textbf{v}_t=\textbf{g}_t+\beta \textbf{g}_{t-1}+\beta^2 \textbf{g}_{t-2}+\cdots$，通常取超参数 $\beta\in \{0.5,0.9,0.95,0.99\}$。

## Adam

其实 SGD 加上 Momentum 效果已经非常好了，这里 Adam 优化的效果不见得更好，但是它对学习率没那么敏感，用起来比较省事，不太用花时间去调参。

- 记录 $\textbf{v}_t=\beta_1 \textbf{v}_{t-1}+(1-\beta_1)\textbf{g}_t$，这里通常取 $\beta_1=0.9$；
- 展开 $\textbf{v}_t=(1-\beta_1)(\textbf{g}_t+\beta_1\textbf{g}_{t-1}+\beta_1^2 \textbf{g}_{t-2}+\cdots)$，我们希望 $\textbf{g}_{*}$ 前的系数和是 $1$（相当于加权平均），但目前是 $(1-\beta_1)\cdot (1+\beta_1+\beta_1^2+\cdots)=1-\beta_1^t$；
- 我们做修正 $\hat{\textbf{v}}_t=\frac{\textbf{v}_t}{1-\beta_1^t}$，配平系数。

- 类似记录 $\textbf{s}_t=\beta_2 \textbf{s}_{t-1}+(1-\beta_2)\textbf{g}_t^2$，这里通常取 $\beta_2=0.999$，做修正 $\hat{\textbf{s}}_t=\frac{\textbf{s}_t}{1-\beta_2^t}$。

- 接着计算调整后的梯度 $\textbf{g}_t=\frac{\hat{\textbf{v}_t}}{\sqrt{\hat{\textbf{s}_t}}+\varepsilon}$，这里类似归一化，将梯度的 scale 拉平。

- 最后更新 $\textbf{x}_t=\textbf{x}_{t-1}-\eta \textbf{g}_t$。

肉眼可见对梯度做了各种平滑操作，且对梯度的各个维度值做了重新调整，看着就 NB。