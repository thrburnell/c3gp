#!/usr/bin/python

import os
import fnmatch

# Prints and executes the input shell command.
def printAndExec(command):
    print(command)
    os.system(command)

printAndExec("g++ tube_network_generator.cpp --std=c++0x")
printAndExec("./a.out")
printAndExec("rm ./a.out")
print("...all done.")
