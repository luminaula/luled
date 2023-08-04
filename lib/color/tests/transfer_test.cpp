#include <cstdlib>
#include <iostream>

#include "color.h"
#include "color_vec.h"
#include "color_matrix.h"
#include "color_transfer.h"

using namespace luled::color;

#define CHECK(fun, a, b) 	\
if(!check(fun(a), b)) 		\
{ 							\
	std::cerr << "Error in " << #fun << " at " << __FILE__ << ":" << __LINE__ << std::endl; \
	return EXIT_FAILURE;	\
}

bool check(float a, float b, float epsilon = 0.001f)
{
	if(std::abs(a - b) > epsilon)
	{
		std::cerr << "Expected: " << b << " Got: " << a << std::endl;
		return false;
	}
	return true;
}

bool check(Vec3F a, float b, float epsilon = 0.001f)
{
	for(auto i = 0; i < 3; i++)
	{
		if(std::abs(a[i] - b) > epsilon)
		{
			std::cerr << "Expected: " << b << " Got: " << a << std::endl;
			return false;
		}
	}
	return true;
}

int main(int argc, char** argv)
{

	CHECK(srgbEotfInverse, 0.18, 0.4613561);
	CHECK(srgbEotf, 0.4613561, 0.18);

	CHECK(bt709Oetf, 0.18, 0.4090077)
	CHECK(bt709OetfInverse, 0.4090077, 0.18);

	CHECK(bt1886Eotf, 0.409007728864150, 0.1169918);
	CHECK(bt1886EotfInverse, 0.1169918, 0.409007728864150);

	CHECK(hlgGamma, 0.0, 1.2);
	CHECK(hlgGamma, 2000.0, 1.3264325);
	CHECK(hlgGamma, 4000.0, 1.4528651);

	CHECK(hlgOetf, 0.18 / 12.0, 0.2121320);
	CHECK(hlgOetfInverse, 0.212132034355964, 0.0149999);

	CHECK(hlgOotf, Vec3F(0.1, 0.1, 0.1), 63.0957344);
	CHECK(hlgOotfInverse, Vec3F(63.095734448019336, 63.095734448019336, 63.095734448019336), 0.1);

	CHECK(hlgEotf, Vec3F(0.212132034355964, 0.212132034355964, 0.212132034355964), 6.4760398);
	CHECK(hlgEotfInverse, Vec3F(6.4760398, 6.4760398, 6.4760398), 0.212132034355964);

	return EXIT_SUCCESS;
}