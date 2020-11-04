from conans import ConanFile, CMake


class ProgressoConan(ConanFile):
    name = "progresso"
    version = "0.1"
    license = "MIT"
    author = "Jeff DeWall"
    url = "https://gitlab.com/sr.jilarious/progresso"
    description = "A C++ command line progress bar with style."
    topics = ("C++17", "progress", "tui", "cli")
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False]}
    default_options = {"shared": False}
    generators = "cmake"
    exports_sources = "progresso/*"

    def build(self):
        cmake = CMake(self)
        cmake.configure(source_folder="progresso")
        cmake.build()

        # Explicit way:
        # self.run('cmake %s/hello %s'
        #          % (self.source_folder, cmake.command_line))
        # self.run("cmake --build . %s" % cmake.build_config)

    def package(self):
        self.copy("*.h", dst="include", src="src")
        self.copy("*.lib", dst="lib", keep_path=False)
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.dylib*", dst="lib", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ["progresso"]
