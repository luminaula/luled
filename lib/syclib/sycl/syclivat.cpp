
#include "syclivat.h"

#include <sycl/sycl.hpp>


struct Syccliva::Data
{
	sycl::device device;
	sycl::queue queue;
	int* buffer;
};

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
	sycl::range local{ 32, 32 };

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

void mandelbro(uint32_t* fb, int width, int height, float zoom, std::pair<float, float> center)
{
	auto device = sycl::gpu_selector{}.select_device();

	const std::pair<float, float> pixelWidth = { 1.0f / width / zoom, 1.0f / height / zoom };

	const std::pair<float, float> topLeft = { center.first - pixelWidth.first * width / 2, center.second - pixelWidth.second * height / 2 };
	// create queue
	sycl::queue queue(device);

	// allocate device memory
	uint32_t* fb_ = sycl::malloc_device<uint32_t>(width * height, queue);

	// copy to device
	// queue.memcpy(fb_, fb, w * h * sizeof(uint32_t));

	// workgroup size
	sycl::range glob{ static_cast<unsigned long>(width), static_cast<unsigned long>(height) };
	sycl::range local{ 32, 32 };

	queue.wait();

	// submit kernel
	queue.submit([&](sycl::handler& h)
	{
		h.parallel_for(sycl::nd_range{glob, local}, [=](sycl::nd_item<2> it)
		{
			int x = it.get_global_id(0);
			int y = it.get_global_id(1);

			float x0 = (float)x * pixelWidth.first + topLeft.first;
			float y0 = (float)y * pixelWidth.second + topLeft.second;


			float x_ = 0.0f;
			float y_ = 0.0f;

			int i = 0;
			while(x_ * x_ + y_ * y_ < 2 * 2 && i < 1000)
			{
				float xtemp = x_ * x_ - y_ * y_ + x0;
				y_ = 2 * x_ * y_ + y0;
				x_ = xtemp;
				i++;
			}

			fb_[y * width + x] = i;
		});
	});
	queue.wait();

	// copy back to host
	queue.memcpy(fb, fb_, width * height * sizeof(uint32_t));

	sycl::free(fb_, queue);
}
