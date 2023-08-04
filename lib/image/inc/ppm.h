#pragma once

#include <memory>
#include <filesystem>

#include "image.h"

namespace luled::image
{

Image readPpm(const std::filesystem::path &p);


} // namespace luled::image