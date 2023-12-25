import os

from conan import ConanFile


class LuLedRecipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps"
    
    default_options = {
        'ffmpeg*:with_vulkan':True,
        'ffmpeg*:shared':True,
        'ffmpeg*:with_ssl':False,
        'ffmpeg*:with_libx264':False,
        'ffmpeg*:with_libx265':False,
        'ffmpeg*:postproc':False,
        'ffmpeg*:libfdk_aac':False,
        'ffmpeg*:enable_hardware_accelerators':'vulkan'
    }

    def requirements(self):
        self.requires('spirv-tools/1.3.268.0')
        self.requires('nv-codec-headers/12.0.16.0')
        self.requires('sdl/2.28.5')
        self.requires('glfw/3.3.8')
        self.requires('ffmpeg/6.1')
        self.requires('openssl/3.2.0')
        self.requires('vulkan-headers/1.3.268.0', override=True)
        self.requires('vulkan-loader/1.3.268.0', override=True)

    def build_requirements(self):
        self.tool_requires("cmake/3.27.7")

    def layout(self):
        multi = True if self.settings.get_safe("compiler") == "msvc" else False
        if multi:
            self.folders.generators = os.path.join("build", "generators")
            self.folders.build = "build"
        else:
            self.folders.generators = os.path.join("build", str(self.settings.build_type), "generators")
            self.folders.build = os.path.join("build", str(self.settings.build_type))

    def build(self):
        cmake = self._configure_cmake()
        cmake.build()