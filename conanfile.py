import os

from conan import ConanFile
from conan.tools.cmake import CMake


class LuLedRecipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps"
    
    default_options = {
        'ffmpeg*:with_vulkan':True,
        'ffmpeg*:shared':True,
        'ffmpeg*:with_ssl':False,
        'ffmpeg*:with_libx264':False,
        'ffmpeg*:with_libx265':False,
        'ffmpeg*:with_libvpx':False,
        'ffmpeg*:with_opus':False,
        'ffmpeg*:postproc':False,
        'ffmpeg*:libfdk_aac':False,
        'ffmpeg*:enable_hardware_accelerators':'vulkan',
        'glad*:spec':'gl',
        'glad*:gl_version':'4.6',
        'glad*:gl_profile':'core',
    }

    def requirements(self):
        self.requires('spirv-tools/1.3.268.0')
        self.requires('nv-codec-headers/12.0.16.0')
        self.requires('sdl/2.28.5')
        self.requires('glfw/3.3.8')
        self.requires('ffmpeg/6.1')
        self.requires('openssl/3.2.0')
        self.requires('glad/0.1.36')
        
        self.requires('vulkan-headers/1.3.268.0', override=True)
        self.requires('vulkan-loader/1.3.268.0', override=True)

    def build_requirements(self):
        self.tool_requires("cmake/3.27.7")
        
    def imports(self):
        self.copy("*.dll", dst="bin", src="bin")
        self.copy("*.dylib*", dst="bin", src="lib")
        self.copy("*.so*", dst="bin", src="lib")