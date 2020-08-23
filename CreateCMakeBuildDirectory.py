import sys
import os
from os import path

def main():

    configuration = "Debug"

    if len(sys.argv) > 1:

        if sys.argv[1] == "Release":

            configuration = "Release"

    directory = "Build" + configuration

    if path.exists(directory):

        userInput = input("The {0} directory already exists. Do you want to delete it or not, please? (y/n)\n".format(directory))

        if userInput.lower() == "y" or userInput.lower() == "yes":

            os.system('rm -rf {0}'.format(directory))

        else:

            sys.exit("The {0} directory will remain intact.\n".format(directory))

    os.system('mkdir {0}'.format(directory))

    os.chdir('{0}'.format(directory))

    codeCoverage = "ON"

    os.system('cmake ../ -DCMAKE_BUILD_TYPE={0} -DCODE_COVERAGE={1}'.format(configuration, codeCoverage))

if __name__== "__main__":
   main()
