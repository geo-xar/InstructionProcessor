from os import chdir
from os import path
from os import system
from sys import exit
from sys import platform
import argparse

class CmdLineArgParser:
    def is_valid_configuration(self, configuration):
        config = str(configuration).lower()
        if config == 'release' or config == 'debug':
            return config[0].upper() + config[1:]
        else:
            raise argparse.ArgumentTypeError(f"Invalid configuration: {configuration}")

    def parse(self):
        self.parser = argparse.ArgumentParser(description='Command Line Argument Parser')
        self.parser.add_argument('--configuration', type=self.is_valid_configuration, required=False, default='Debug', help='Build configuration i.e. Debug or Release')
        self.parser.add_argument('--compiler', type=str, required=False, default='g++', help='Default compiler in Linux is GCC and in Windows is MSVC. Please specify your desired compiler i.e. Clang')
        self.parser.add_argument('--no-build', dest='build', action='store_false', help='Do not build code after generating build directory')
        self.parser.set_defaults(build=True)
        self.args = self.parser.parse_args()

    def get_config(self):
        return self.args.configuration

    def get_compiler(self):
        return self.args.compiler

    def do_build(self):
        return self.args.build

def main():
    cmdLineArgParser = CmdLineArgParser()
    cmdLineArgParser.parse()

    build_directory = 'Build' + cmdLineArgParser.get_config()
    build_directory_exists = False

    if path.exists(build_directory):
        build_directory_exists = True

        user_input = str(input(f"The {build_directory} directory already exists. Do you wish to:\n1.Delete it and generate it from scratch\n2.Do nothing\nPlease choose between 1 and 2\n"))

        while (user_input != '1' and user_input != '2'):
            user_input = str(input(f"The {build_directory} directory already exists. Do you wish to:\n1.Delete it and generate it from scratch\n2.Do nothing\nPlease choose between 1 and 2\n"))

        if user_input == '1':
            if platform == 'linux' or platform == 'linux2':
                system(f"rm -rf {build_directory}")
            elif platform == 'win32':
                system(f"rmdir /s /q {build_directory}")

            build_directory_exists = False

        else:
            exit(f"The {build_directory} directory will remain intact.\n")

    if not build_directory_exists:
        system(f"mkdir {build_directory}")

    chdir(f"{build_directory}")

    cmakeCommand = f"cmake ../ -DCMAKE_BUILD_TYPE={cmdLineArgParser.get_config()}"

    if cmdLineArgParser.get_config() == 'Debug':
	    cmakeCommand = cmakeCommand + ' -DCODE_COVERAGE=ON'

    if cmdLineArgParser.get_compiler().lower() == 'clang':
        if platform == 'linux' or platform == 'linux2':
            cmakeCommand = cmakeCommand + ' -DCMAKE_CXX_COMPILER=clang++'
        elif platform == 'win32':
            cmakeCommand = cmakeCommand + ' -T ClangCL'

    if platform == 'win32':
        cmakeCommand = cmakeCommand + ' -A x64'

    # Execute CMake command to generate build directory
    system(cmakeCommand)

    # Build code if it is requested (requested by default)
    if cmdLineArgParser.do_build():
        buildResult = system('cmake --build .')
        if (buildResult):
            exit(f"Build failed, error code: {buildResult}")


if __name__ == "__main__":
    main()
