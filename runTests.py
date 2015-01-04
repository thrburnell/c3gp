#!/usr/bin/python

import os

print("Running tests...");

testsCommand = "mocha tests"
print(testsCommand)
os.system(testsCommand)

