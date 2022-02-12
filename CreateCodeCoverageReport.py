import sys
import os
from os import system
from os import path
import argparse
from sys import platform

class CmdLineArgParser:
    def parse(self):
        self.parser = argparse.ArgumentParser(description='Command Line Argument Parser')
        self.parser.add_argument('--dir', type=str, required=False, default='BuildDebug', help='Default build directory is BuildDebug. Please specify an alternative dir if you wish i.e. Debug')
        self.args = self.parser.parse_args()

    def get_dir(self):
        return self.args.dir

def main():
    if platform == 'win32':
        sys.exit("Code coverage generation is limited to Linux OS. No code coverage will be calculated. Bye!")

    cmdLineArgParser = CmdLineArgParser()
    cmdLineArgParser.parse()

    buildDir = cmdLineArgParser.get_dir()
    if not path.exists(buildDir):
        sys.exit(f"The {buildDir} directory doesn't exist. No code coverage will be calculated. Bye!.\n")

    os.chdir(f"{buildDir}")

    coverage_directory = 'CoverageResults'
    if path.exists(f"{coverage_directory}"):
        if platform == 'linux' or platform == 'linux2':
            system(f"rm -rf {coverage_directory}")
        elif platform == 'win32':
            system(f"rmdir /s /q {coverage_directory}")

    os.system('export GCOV_PREFIX=""')

    print('Executing the InstructionProcessorTest executable...')
    os.system('./tst/InstructionProcessorTest')

    coverageTool = 'lcov'

    print('Generating coverage results...')
    os.system(coverageTool + f" -t {coverage_directory} -o CoverageResults.info -c -d tst/CMakeFiles/InstructionProcessorTest.dir/")

    print('Excluding external files from the code coverage results...')
    os.system(coverageTool + ' --remove CoverageResults.info "*catch*" -o CoverageResults.info')
    os.system(coverageTool + ' --remove CoverageResults.info "/usr/include/c++*" -o CoverageResults.info')

    print('Generating code coverage report HTML...')
    os.system('genhtml -o CoverageResults CoverageResults.info')

if __name__ == "__main__":

    main()

