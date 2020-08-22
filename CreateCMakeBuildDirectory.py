import sys
import os
from os import path

def main():

    configuration = "Debug"

    if len(sys.argv) > 0:
        if str(sys.argv)[0] == "Release":
            configuration = "Release"

    directory = "Build" + configuration
    if path.exists(directory):
        os.system('rm -rf {0}'.format(directory))
    os.system('mkdir {0}'.format(directory))
    os.chdir('{0}'.format(directory))
    os.system('cmake ../ -DCMAKE_BUILD_TYPE={0}'.format(configuration))

if __name__== "__main__":
   main()
