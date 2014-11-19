#!/usr/bin/python
import os;

# Prints and executes the input shell command.
def printAndExec(command):
    print(command)
    os.system(command)

# Installs rapidjson library.
def installRapidJSON():
    mkdirCommand = "mkdir -p src/lib/rapidjson"
    printAndExec(mkdirCommand)
    
    copyCommand = "cp -r bower_components/rapidjson/include/rapidjson/ src/lib"
    printAndExec(copyCommand)

# Installs and sets up googletest library.
def installGoogleTest():
    mkdirCommand = "mkdir -p test"
    printAndExec(mkdirCommand)

    gTestDir = "bower_components/googletest/"
    makeCommand = "g++ -isystem " + gTestDir + "include -I" + gTestDir + \
    " -pthread -c " + gTestDir + "src/gtest-all.cc"
    printAndExec(makeCommand)

    archiveCommand = "ar -rv test/libgtest.a gtest-all.o && rm gtest-all.o"
    printAndExec(archiveCommand)
    
    copyCommand = "cp -r bower_components/googletest/include/gtest/ src/lib"
    printAndExec(copyCommand)

bowerCommand = "bower install"
printAndExec(bowerCommand)

# Build and copy relevant libraries.
# Might not be scalable in the long run.
installRapidJSON()
installGoogleTest()

buildCommand = "scons"
printAndExec(buildCommand)
