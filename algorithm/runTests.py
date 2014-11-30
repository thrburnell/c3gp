#!/usr/bin/python

import os
import fnmatch

# Prints and executes the input shell command.
def printAndExec(command):
    print(command)
    os.system(command)

print("Building testsuite...")

# Clean up old test data, if present.
for root, dirs, filenames in os.walk('test'):
    for filename in filenames:
        if filename != "libgtest.a":
            os.system("rm test/" + filename)

printAndExec("scons")

testnames = []

# Find all executables in the test folder - these are the unit tests
for root, dirs, filenames in os.walk('test'):
    for filename in filenames:
        if os.access(os.path.join(root, filename), os.X_OK):
            testnames.append(filename)

# Execute the tests. The gtest_output is used by Jenkins to neatly format
# the test output.
print("Running tests...")
for testname in testnames:
    printAndExec("test/" + testname + " --gtest_output=\"xml:test/" +
                 testname + "_results.xml\"")

print("...tests complete.")

# Destroy all the tests.
print("Cleaning up test artifacts...")
for root, dirs, filenames in os.walk('test'):
    for filename in filenames:
        if filename != "libgtest.a" and not \
           fnmatch.fnmatch(filename, "*.xml"):
            os.system("rm test/" + filename)

print("...cleanup complete.")

