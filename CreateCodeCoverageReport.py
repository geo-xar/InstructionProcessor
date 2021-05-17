import sys
import os
from os import path


def main():

    directory = "BuildDebug"

    if not path.exists(directory):

        sys.exit("The {0} directory doesn't exist. No code coverage will be calculated. Bye!.\n".format(directory))

    os.chdir('{0}'.format(directory))

    os.system('export GCOV_PREFIX=""')

    print('Executing the InstructionProcessorTest executable...')
    os.system('./tst/InstructionProcessorTest')

    print('Generating coverage results...')
    os.system('lcov -t "CoverageResults" -o CoverageResults.info -c -d tst/CMakeFiles/InstructionProcessorTest.dir/')

    print('Excluding external files from the code coverage results...')
    os.system('lcov --remove CoverageResults.info "*catch*" -o CoverageResults.info')
    os.system('lcov --remove CoverageResults.info "/usr/include/c++*" -o CoverageResults.info')

    print('Generating code coverage report HTML...')
    os.system('genhtml -o CoverageResults CoverageResults.info')


if __name__ == "__main__":

    main()
