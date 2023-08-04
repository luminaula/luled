#include <vector>
#include <memory>

namespace luled::image
{

struct Image
{
	int width,height,channels;
	std::unique_ptr<uint8_t[]> data;
};

}