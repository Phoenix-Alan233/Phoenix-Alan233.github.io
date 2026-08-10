# Primitive $2^k$-th root of unity in a finite field $F_m$

!!! warning
    It was written by Alan233 on 2024/07/25.

## Introduction

When we apply the Fast Fourier Transform to polynomials of degree less than $2^k$ in modular arithmetic (usually assuming $m\in \text{Prime}$), we have to find $\omega$ —— a primitive $2^k$-th root of unity.

We already know that when $m\in \text{Prime}$, there exists a primitive root $g$, and one possible value of $\omega$ is $g^{\frac{m-1}{2^k}}\pmod m$.

But in the general case (that is, $m,k\in \mathbb Z^+$), how can we find a proper $\omega$, or determine that it doesn't exist?

I looked through many papers and finally came up with an elegant algorithm.

## Part 1: Carmichael Function λ(m)

We define the Carmichael function $\lambda(m)$ as $\text{lcm}(\text{ord}_m(a))$ over all $a$ coprime with $m$ (equivalently, the smallest positive integer $x$ such that $a^x\equiv 1\pmod m$ for every such $a$).

**Observation 1.** $\lambda(m)\ |\ \varphi(m)$, where $\varphi(m)$ is Euler's totient function.

**Observation 2.** For any $d\ |\ \lambda(m)$, there must exist some $a$ coprime with $m$ such that $\text{ord}_m(a)=d$.

**Proof 2.** By the properties of abelian groups, there exists $a$ coprime with $m$ such that $\text{ord}_m(a)=\lambda(m)$.

Let $a' = a^{\lambda(m)/d}\pmod m$; then $\text{ord}_m(a')=d$ must hold.

**Observation 3.** By the unique factorization theorem, write $m=\prod\limits_{i=1}p_i^{q_i}$; then $\lambda(m)=\text{lcm}(\lambda(p_i^{q_i}))$.

Now let's analyze $\lambda(p^q)$. Define $m'=p^q$.

- If $m'=2,\ 4,$ or $p^q\ (p\ge 3)$, it is well known that a primitive root $g$ exists, so $\lambda(m')=\varphi(m')$;
- Otherwise (i.e., $p=2$ and $q\ge 3$), it is easy to show that $\lambda(m')=2^{q-2}$.

## Part 2: Construction

From the three observations above, we know that **$\omega$ exists if and only if $2^k\ |\ \lambda(m)$**.

If $\omega$ exists, we can find some $p^q$ satisfying $2^k\ |\ \lambda(p^q)$. By the primitive root theorem, there are $\varphi(\lambda(p^q))$ values of $a$ such that $\text{ord}_{p^q}(a)=\lambda(p^q)$, so we can pick one at random — the success probability is $\frac{\varphi(\lambda(p^q))}{p^q}$ — and check whether it is valid.

The next problem: given $\begin{cases}x\equiv \omega\pmod {p^q} \\ x\equiv 1\pmod {m/p^q}\end{cases}$, we need to compute $x$. This can be solved using the extended Euclidean algorithm.

## Part 3: Complexity

First, we factorize $m$ using the Pollard-Rho algorithm in $\mathcal O(m^{1/4})$.

Then, we find $p,q$ and factorize $\lambda(p^q)$ in $\mathcal O(m^{1/4})$, and the randomized algorithm runs in $\mathcal O(\omega(m)\cdot \log m)$.

Finally, merging the two congruences takes $\mathcal O(\log m)$.

In summary, the total complexity is $\mathcal O(m^{1/4}+\omega(m)\cdot \log m)$.

## Part 4: Implementation (199 lines, 4.1 KB)

```cpp
// Author: PhoenixRebirth
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ld long double

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
ll m, tmpm, omega, mod1, mod2;
int k;

ll spow(ll a, int b) {
    ll res = 1;
    while (b--) res *= a;
    return res;
}

// https://yhx-12243.github.io/OI-transit/templates.html
inline ll MulMod(ll a, ll b, ll m) {
    ll t = (a * b - (ll)((ld)a * b / m) * m) % m;
    return t + (t >> 63 & m);
}

// https://www.luogu.com.cn/problem/solution/P4718
vector<ll> pr;
namespace Pollard_Rho {
#define lll __int128
inline ll gcd(ll a,ll b)
{
    if(b==0)
        return a;
    return gcd(b,a%b);
}

inline ll qp(ll x,ll p,ll mod)
{
    ll ans=1;
    while(p)
    {
        if(p&1)
            ans=(lll)ans*x%mod;
        x=(lll)x*x%mod;
        p>>=1;
    }
    return ans;
}

inline bool mr(ll x,ll b)
{
    ll k=x-1;
    while(k)
    {
        ll cur=qp(b,k,x);
        if(cur!=1 && cur!=x-1)
            return false;
        if((k&1)==1 || cur==x-1)
            return true;
        k>>=1;
    }
    return true;
}

inline bool prime(ll x)
{
    if(x==46856248255981ll || x<2)
        return false;
    if(x==2 || x==3 || x==7 || x==61 || x==24251)
        return true;
    return mr(x,2)&&mr(x,61);
}

inline ll f(ll x,ll c,ll n)
{
    return ((lll)x*x+c)%n;
}

inline ll PR(ll x)
{
    ll s=0,t=0,c=1ll*rand()%(x-1)+1;
    int stp=0,goal=1;
    ll val=1;
    for(goal=1;;goal<<=1,s=t,val=1)
    {
        for(stp=1;stp<=goal;++stp)
        {
            t=f(t,c,x);
            val=(lll)val*abs(t-s)%x;
            if((stp%127)==0)
            {
                ll d=gcd(val,x);
                if(d>1)
                    return d;
            }
        }
        ll d=gcd(val,x);
        if(d>1)
            return d;
    }
}

inline void fac(ll x)
{
    if(x<2)
        return;
    if(prime(x))
    {
        pr.push_back(x);
        return;
    }
    ll p=x;
    while(p>=x)
        p=PR(x);
    while((x%p)==0)
        x/=p;
    fac(x),fac(p);
}
}

ll qpow(ll a, ll b, ll mod) {
    ll res = 1;
    while (b) {
        if (b & 1) res = MulMod(res, a, mod);
        a = MulMod(a, a, mod);
        b >>= 1;
    }
    return res;
}
void solve(ll p, ll lambda) {
    pr.clear(), Pollard_Rho::fac(lambda);
    // ord_p(g) = lambda
    while (1) {
        ll g = rng() % p;
        if (qpow(g, lambda, p) != 1) continue;
        bool flag = 1;
        for (auto it: pr) {
            if (qpow(g, lambda / it, p) == 1) {
                flag = 0;
                break;
            }
        }
        if (flag) {
            omega = qpow(g, lambda / (1 << k), p);
            mod1 = p;
            break;
        }
    }
}

void exgcd(ll a, ll b, ll &x, ll &y) {
    if (!b) {
        x = 1, y = 0;
        return ;
    }
    exgcd(b, a % b, y, x);
    y -= (a / b) * x;
}

int main() {
    cin >> m >> k;
    tmpm = m;
    if (tmpm % 2 == 0) {
        int t = 0;
        while (tmpm % 2 == 0) tmpm /= 2, t++;
        if (t - 1 - (t >= 3) >= k) {
            solve(spow(2, t), spow(2, t - 1 - (t >= 3)));
            goto end;
        }
    }

    pr.clear(), Pollard_Rho::fac(tmpm);
    for (auto i: pr) {
        int t = 0;
        while (tmpm % i == 0) tmpm /= i, t++;
        if ((i - 1) % (1 << k) == 0) {
            solve(spow(i, t), (i - 1) * spow(i, t - 1));
            goto end;
        }
    }
    puts("-1");
    return 0;
    end: {
        /*
        x \equiv omega (mod mod1)
        x \equiv 1 (mod mod2)
        */
        mod2 = m / mod1;
        if (mod2 != 1) {
            ll x, y;
            exgcd(mod1, mod2, x, y);
            x = (x % mod2 + mod2) % mod2;
            x = MulMod(x, omega - 1, mod2);
            omega += mod1 * (mod2 - x);
        }
        omega %= m;
        printf("%lld\n", omega);
        return 0;
    };
    return 0;
}
```