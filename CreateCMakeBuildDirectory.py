import sys
from os import chdir
from os import path
from os import system
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

        self.args = self.parser.parse_args()


    def get_config(self):

        return self.args.configuration


def main():

    cmdLineArgParser = CmdLineArgParser()

    cmdLineArgParser.parse()

    directory = "Build" + cmdLineArgParser.get_config()

    if path.exists(directory):

        user_input = input("The {0} directory already exists. Do you want to delete it or not, please? (y/n)\n".format(directory))

        if user_input.lower() == "y" or user_input.lower() == "yes":

            system('rm -rf {0}'.format(directory))

        else:

            sys.exit("The {0} directory will remain intact.\n".format(directory))

    system('mkdir {0}'.format(directory))

    chdir('{0}'.format(directory))

    code_coverage = "ON"

    if cmdLineArgParser.get_config() == "Release":

        code_coverage = "OFF"

    system('cmake ../ -DCMAKE_BUILD_TYPE={0} -DCODE_COVERAGE={1}'.format(cmdLineArgParser.get_config(), code_coverage))

    system('make -j4')


if __name__ == "__main__":

    main()
