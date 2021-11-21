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

        self.parser.add_argument('--compiler', type=str, required=False, default='GCC', help='Default compiler in Linux is GCC and in Windows is MSVC. Please specify your desired compiler i.e. Clang')

        self.args = self.parser.parse_args()


    def get_config(self):

        return self.args.configuration


    def get_compiler(self):

        return self.args.compiler


def main():

    cmdLineArgParser = CmdLineArgParser()

    cmdLineArgParser.parse()

    build_directory = "Build" + cmdLineArgParser.get_config()

    build_directory_exists = False

    if path.exists(build_directory):

        user_input = input("The {0} directory already exists. Do you wish to:\n1.Build the already existing project\n2.Delete it and build from scratch\n3.Do nothing\nPlease choose between 1, 2 and 3\n".format(build_directory))

        while not (user_input == "1" or user_input == "2" or user_input == "3"):

            user_input = input("The {0} directory already exists. Do you wish to:\n1.Build the already existing project\n2.Delete it and build from scratch\n3.Do nothing\nPlease choose between 1, 2 and 3\n".format(build_directory))

        if user_input == "1":

            build_directory_exists = True

        elif user_input == "2":

            if platform == "linux" or platform == "linux2":

                system('rm -rf {0}'.format(build_directory))

            elif platform == "win32":

                system('rmdir /s /q {0}'.format(build_directory))

        else:

            sys.exit("The {0} directory will remain intact.\n".format(build_directory))

    if not build_directory_exists:

        system('mkdir {0}'.format(build_directory))

    chdir('{0}'.format(build_directory))

    if not build_directory_exists:

        code_coverage = "ON"

        if cmdLineArgParser.get_config() == "Release":

            code_coverage = "OFF"

        if cmdLineArgParser.get_compiler().lower() == 'clang':

            system('cmake ../ -DCMAKE_BUILD_TYPE={0} -DCODE_COVERAGE={1} -DCMAKE_CXX_COMPILER={2}'.format(cmdLineArgParser.get_config(), code_coverage, 'clang++'))

        else:

            system('cmake ../ -DCMAKE_BUILD_TYPE={0} -DCODE_COVERAGE={1}'.format(cmdLineArgParser.get_config(), code_coverage))

    if platform == "linux" or platform == "linux2":

        system('make -j4')


if __name__ == "__main__":

    main()
