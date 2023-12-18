
#include "syclivat.h"

#include <sycl/sycl.hpp>


struct SycclivaImpl
{
	sycl::device device;
	sycl::queue queue;
	uint32_t* buffer;
	int width;
	int height;
};



void* initSyccs()
{
	SycclivaImpl* syccliva = new SycclivaImpl();

	syccliva->device = sycl::device(sycl::gpu_selector_v);//sycl::gpu_selector{}.select_device();
	syccliva->queue = sycl::queue(syccliva->device);
	return (void*)syccliva;
}




void sgemmSycl(float* A, float* B, float* C, int N, int M, int K)
{

	auto device = sycl::device(sycl::gpu_selector_v);

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

void mandelbro(void* syccliva_void, uint32_t* fb, const int width, const int height, const MandelReal zoom, const std::pair<MandelReal, MandelReal> center)
{
	auto* syccliva = static_cast<SycclivaImpl*>(syccliva_void);

	//const std::pair<MandelReal, MandelReal> pixelWidth_ = { 1.0f / width / zoom, 1.0f / height / zoom };
	const MandelReal pixelWidth = 1.0f / width / zoom;
	const MandelReal pixelHeight = 1.0f / height / zoom;

	//const std::pair<MandelReal, MandelReal> topLeft = { center.first - pixelWidth * width / 2, center.second - pixelHeight * height / 2 };
	const MandelReal x00 = center.first - pixelWidth * width / 2;
	const MandelReal y00 = center.second - pixelHeight * height / 2;

	// allocate device memory
	if(width * height != syccliva->width * syccliva->height)
	{
		if(syccliva->buffer != nullptr)
			sycl::free(syccliva->buffer, syccliva->queue);
		syccliva->buffer = sycl::malloc_device<uint32_t>(width * height, syccliva->queue);
		syccliva->width = width;
		syccliva->height = height;
		syccliva->queue.wait();
	}
	uint32_t* fb_ = syccliva->buffer;

	// workgroup size
	sycl::range glob{ static_cast<unsigned long>(width), static_cast<unsigned long>(height) };
	sycl::range local{ 16, 4 };

	/*[local] = float 	= double
		2 ,8  = 142
		2 ,16 = 184
		2 ,32 = 187
		4 ,8  = 192
		4 ,16 = 194
		4 ,32 = 189
		8 ,4  = 194
		8 ,8  = 196
		8 ,16 = 186
		8 ,32 = 188
		16,1  = 144
		16,2  = 195
		16,4  = 198		= 18
		16,8  = 197
		16,16 = 194
		16,32 = 180
		32,1  = 193
		32,2  = 196
		32,4  = 195
		32,8  = 193
		32,16 = 189
		32,32 = 181
		64,1  = 193
		64,2  = 195
		64,4  = 196
		64,8  = 196
		64,16 = 188
		128,1 = 190
		128,2 = 190
		128,4 = 195
		128,8 = 190
		256,1 = 190
		256,2 = 193
		256,4 = 190
		512,1 = 189
		512,2 = 190
	*/
	
	// submit kernel
	syccliva->queue.submit([&](sycl::handler& h)
	{
		h.parallel_for(sycl::nd_range{glob, local}, [=](sycl::nd_item<2> it)
		{
			const size_t x = it.get_global_id(0);
			const size_t y = it.get_global_id(1);

			const MandelReal x0 = (MandelReal)x * pixelWidth + x00;
			const MandelReal y0 = (MandelReal)y * pixelHeight + y00;

			MandelReal x_ = 0.0f;
			MandelReal y_ = 0.0f;

			uint32_t i = 0;
			while(x_ * x_ + y_ * y_ < 2 * 2 && i < 1000)
			{
				MandelReal xtemp = x_ * x_ - y_ * y_ + x0;
				y_ = 2 * x_ * y_ + y0;
				x_ = xtemp;
				i++;
			}

			fb_[y * width + x] = i;
		});
	});

	// wait for previous memcpy to finish
	syccliva->queue.wait();
	// copy back to host
	syccliva->queue.memcpy(fb, fb_, width * height * sizeof(uint32_t));
}
