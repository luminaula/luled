import os

from conan import ConanFile
from conan.tools.cmake import CMake


class LuLedRecipe(ConanFile):
    name = "lu-led"
    version = "0.1.0"
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps"
    author = "Lumi"
    
    
    default_options = {
        'sdl*:pulse':'False',
        'opencv*:with_ffpmeg':False,
        'opencv*:shared':True,
        'opencv*:fPIC':True,
        'opencv*:neon':False,
        'opencv*:parallel':False,
        'opencv*:with_eigen':False,
        'opencv*:with_opencl':False,
        'opencv*:with_cuda':False,
        'opencv*:with_cublas':False,
        'opencv*:with_cufft':False,
        'opencv*:with_cudnn':False,
        'opencv*:dnn_cuda':False,
        'opencv*:nonfree':False,
        'opencv*:with_flatbuffers':False,
        'opencv*:with_protobuf':False,
        'opencv*:with_vulkan':True,
        'opencv*:with_gtk':False,
        'opencv*:with_qt':False,
        'opencv*:with_wayland':False,
        'opencv*:with_avif':False,
        'opencv*:with_jpeg':False,
        'opencv*:with_png':False,
        'opencv*:with_tiff':False,
        'opencv*:with_jpeg2000':False,
        'opencv*:with_openexr':False,
        'opencv*:with_webp':False,
        'opencv*:with_gdal':False,
        'opencv*:with_gdcm':False,
        'opencv*:with_imgcodec_hdr':False,
        'opencv*:with_imgcodec_pfm':False,
        'opencv*:with_imgcodec_pxm':False,
        'opencv*:with_imgcodec_sunraster':False,
        'opencv*:with_msmf':False,
        'opencv*:with_msmf_dxva':False,
        'opencv*:with_quirc':False,
        'opencv*:with_v4l':False,
        'opencv*:with_tesseract':False,
        'ffmpeg*:with_vulkan':True,
        'ffmpeg*:shared':True,
        'ffmpeg*:with_ssl':False,
        'ffmpeg*:with_pulse':False,
        'ffmpeg*:with_libx264':False,
        'ffmpeg*:with_libx265':False,
        'ffmpeg*:with_libvpx':False,
        'ffmpeg*:with_libfdk_aac':False,
        'ffmpeg*:with_opus':False,
        'ffmpeg*:postproc':False,
        'ffmpeg*:enable_hardware_accelerators':'vulkan',
        'glad*:shared':True,
        'glad*:spec':'gl',
        'glad*:gl_version':'4.6',
        'glad*:gl_profile':'core',
        'vulkan-loader*:with_wsi_xcb':False,
        'vulkan-loader*:with_wsi_xlib':False,
        'vulkan-loader*:with_wsi_wayland':False,
        'vulkan-loader*:with_wsi_directfb':False,
    }

    def requirements(self):
        self.requires('opencv/4.8.1')
        self.requires('spirv-tools/1.3.268.0', force=True)
        self.requires('spirv-headers/1.3.268.0', force=True)
        self.requires('nv-codec-headers/12.0.16.0')
        self.requires('sdl/2.28.5')
        self.requires('glfw/3.3.8')
        self.requires('vk-bootstrap/0.7')
        self.requires('libxml2/2.12.3', override=True)

        # self.requires('vulkan-validationlayers/1.3.239.0', force=True)
        self.requires('vulkan-headers/1.3.268.0', force=True)
        self.requires('vulkan-loader/1.3.268.0', force=True)
        self.requires('vulkan-memory-allocator/cci.20231120')
        self.requires('ffmpeg/6.1', force=True)
        self.requires('glad/0.1.36')
        
    
    def layout(self):
        # We make the assumption that if the compiler is msvc the
        # CMake generator is multi-config
        multi = True if self.settings.get_safe("compiler") == "msvc" else False
        if multi:
            self.folders.generators = os.path.join("build", "generators")
            self.folders.build = "build"
        else:
            self.folders.generators = os.path.join("build", str(self.settings.build_type), "generators")
            self.folders.build = os.path.join("build", str(self.settings.build_type))

    def build_requirements(self):
        self.tool_requires('cmake/3.27.7')
        
    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
        cmake.install()
        
    def imports(self):
        self.copy("*.dll", dst="bin", src="bin")
        self.copy("*.dylib*", dst="bin", src="lib")
        self.copy("*.so*", dst="bin", src="lib")
        self.copy("license*", dst="licenses", folder=True, ignore_case=True)