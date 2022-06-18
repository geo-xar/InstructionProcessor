# Copyright 2022 by Georgios Charitos.
# All rights reserved.

import os
from os import path
from os import system
from os import chdir
from sys import exit
from sys import platform

def code_coverage_on_linux(build_directory):
    """
    Generate code coverage on Linux using LCOV tool.
    :param build_directory
    """
    if not path.exists(build_directory):
        exit('BuildDebug directory does not exist, please execute "python CreateCMakeBuildDirectory.py" first')

    os.chdir(f"{build_directory}")

    coverage_directory = 'CoverageResults'
    if path.exists(f"{coverage_directory}"):
        system(f"rm -rf {coverage_directory}")

    os.system('export GCOV_PREFIX=""')

    print('Executing the InstructionProcessorTest executable...')
    os.system('./tst/bin/InstructionProcessorTest')

    coverage_tool = 'lcov'

    print('Generating coverage results...')
    os.system(coverage_tool + f" -t {coverage_directory} -o CoverageResults.info -c -d tst/CMakeFiles/InstructionProcessorTest.dir/")

    print('Excluding external files from the code coverage results...')
    os.system(coverage_tool + ' --remove CoverageResults.info "*catch*" -o CoverageResults.info')
    os.system(coverage_tool + ' --remove CoverageResults.info "/usr/include/c++*" -o CoverageResults.info')

    print('Generating code coverage report HTML...')
    os.system('genhtml -o CoverageResults CoverageResults.info')

def code_coverage_on_windows(build_directory):
    """
    Generate code coverage on Windows using OpenCppCoverage tool.
    :param build_directory
    """
    if not path.exists(build_directory):
        exit('BuildDebug directory does not exist, please execute "python CreateCMakeBuildDirectory.py" first')

    command = r'OpenCppCoverage.exe --sources=InstructionProcessor\src --excluded_line_regex \s*[{}]*\s* -- BuildDebug\tst\bin\InstructionProcessorTest.exe'
    system(command)


def main():
    """The main application that generates code coverage on Windows."""

    build_directory = 'BuildDebug'

    if platform == 'linux' or platform == 'linux2':
        code_coverage_on_linux(build_directory)
    else: # Windows
        code_coverage_on_windows(build_directory)


if __name__ == "__main__":
    main()
