# CUDA 编程

!!! tip "备注"
    本文记录 CUDA 编程的学习，主要是 CUDA C++ 的开发，并将 https://leetgpu.com/ 作为题库进行练习，所以本文更像是一份题解（


!!! note "参考资料"
    - NVIDIA，[CUDA Programming Guide](https://docs.nvidia.com/cuda/cuda-programming-guide/index.html)

| 关键字 | 含义 |
| :---: | :---: |
| `__device__` | GPU 内部调用的函数 |
| `__global__` | 核函数（Kernel） |
| `<<<blocksPerGrid, threadsPerBlock>>>` | 启动核函数，声明开多少个 block、thread |
| `cudaMalloc`、`cudaMemcpy` | 在 GPU 显存上分配空间、拷贝数据 |

### Vector Addition

非常经典的向量加法：

```cpp
#include <cuda_runtime.h>

__global__ void vector_add(const float* A, const float* B, float* C, int N) {
    int pos = blockIdx.x * blockDim.x + threadIdx.x;
    if (pos < N)
        C[pos] = A[pos] + B[pos];
}

// A, B, C are device pointers (i.e. pointers to memory on the GPU)
extern "C" void solve(const float* A, const float* B, float* C, int N) {
    int threadsPerBlock = 256;
    int blocksPerGrid = (N + threadsPerBlock - 1) / threadsPerBlock;

    vector_add<<<blocksPerGrid, threadsPerBlock>>>(A, B, C, N);
    cudaDeviceSynchronize();
}
```

### Matrix Multiplication

现在还只是最粗糙的版本，据说可以加上“共享内存 Tiling + 向量化 + 线程粗化”优化。

```cpp
#include <cuda_runtime.h>

__global__ void matrix_multiplication_kernel(const float* A, const float* B, float* C, int M, int N, int K) {
    int i = blockIdx.y * blockDim.y + threadIdx.y;
    int j = blockIdx.x * blockDim.x + threadIdx.x;

    if (i < M && j < K) {
        float result = 0;
        for (int t = 0; t < N; t++)
            result += A[i * N + t] * B[t * K + j];
        C[i * K + j] = result;
    }
}

// A, B, C are device pointers (i.e. pointers to memory on the GPU)
extern "C" void solve(const float* A, const float* B, float* C, int M, int N, int K) {
    dim3 threadsPerBlock(16, 16);
    dim3 blocksPerGrid((K + threadsPerBlock.x - 1) / threadsPerBlock.x,
                       (M + threadsPerBlock.y - 1) / threadsPerBlock.y);

    matrix_multiplication_kernel<<<blocksPerGrid, threadsPerBlock>>>(A, B, C, M, N, K);
    cudaDeviceSynchronize();
}
```