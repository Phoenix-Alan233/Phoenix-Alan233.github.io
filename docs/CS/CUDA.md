# CUDA 编程

!!! tip "备注"
    本文记录 CUDA 编程的学习，主要是 CUDA C++ 的开发，并将 https://leetgpu.com/ 作为题库进行练习，所以本文更像是一份题解（


!!! note "参考资料"
    - NVIDIA，[CUDA Programming Guide](https://docs.nvidia.com/cuda/cuda-programming-guide/index.html)


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