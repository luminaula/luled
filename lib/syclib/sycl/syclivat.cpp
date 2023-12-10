
#include "syclivat.h"

#include <sycl/sycl.hpp>

void sgemmSycl(float* A, float* B, float* C, int N, int M, int K)
{

	auto device = sycl::gpu_selector{}.select_device();

	// create queue
	sycl::queue queue(device);

	// allocate device memory
	float* A_ = sycl::malloc_device<float>(N * K, queue);
	float* B_ = sycl::malloc_device<float>(K * M, queue);
	float* C_ = sycl::malloc_device<float>(N * M, queue);

	// copy to device
	queue.memcpy(A_, A, N * K * sizeof(float));
	queue.memcpy(B_, B, K * M * sizeof(float));

	// workgroup size
	sycl::range glob{ static_cast<unsigned long>(N), static_cast<unsigned long>(M) };
	sycl::range local{ 1, 1 };

	queue.wait();

	// submit kernel
	queue.submit([&](sycl::handler& h)
	{
		h.parallel_for(sycl::nd_range{glob, local}, [=](sycl::nd_item<2> it)
		{
			int i = it.get_global_id(0);
			int j = it.get_global_id(1);

			float sum = 0.0;
			for(int k = 0; k < K; k++)
			{
				sum += A_[i * K + k] * B_[k * M + j];
			}
			C_[i * M + j] = sum;
		});
	});
	queue.wait();

	// copy back to host
	queue.memcpy(C, C_, N * M * sizeof(float));
	queue.wait();

	sycl::free(A_, queue);
	sycl::free(B_, queue);
	sycl::free(C_, queue);

}

void sycli()
{
	float A[2 * 3] = { 1, 2, 3, 4, 5, 6 };
	float B[3 * 4] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 ,10 ,11 ,12 };
	float C[2 * 4] = { 0 };

	sgemmSycl(A, B, C, 2, 4, 3);
}