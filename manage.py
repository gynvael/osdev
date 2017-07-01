#!/usr/bin/python
from __future__ import print_function
import shutil
import traceback
import sys
import os
from scripts import build, run


def main():

    # Add missing directories if needed
    for directory in ("tmp", "bin",):
        if not os.path.exists(directory):
            os.makedirs(directory)

    # Parse console arguments
    if len(sys.argv) == 2:
        os.chdir("tmp/")
        if sys.argv[1] == "build":
            build()
        elif sys.argv[1] == "run":
            run()
        elif sys.argv[1] == "test":
            build()
            run()
        elif sys.argv[1] == "clean":
            os.chdir("..")
            shutil.rmtree("tmp")
            print("Cleaned ./tmp directory.")
        elif sys.argv[1] == "help":
            print("Usage:")
            print("  build\t- Build project")
            print("  run\t- Run project")
            print("  test\t- Build and run project")
            print("  clean\t- Clean temporary directory\n")
        else:
            print("Invalid argument: " + sys.argv[1])
            sys.exit(1)
    else:
        print("Missing arguments. Use 'help' to display usage.")
        sys.exit(1)

if __name__ == "__main__":
    main()
