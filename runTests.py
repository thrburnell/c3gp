#!/usr/bin/python

import os

print("Running tests...");

testsCommand = "jasmine-node tests"
print(testsCommand)
os.system(testsCommand)
