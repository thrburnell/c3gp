#!/usr/bin/python
import os;

bowerCommand = "bower install"
print(bowerCommand)
os.system(bowerCommand)

mkdirCommand = "mkdir -p src/lib/rapidjson"
print(mkdirCommand)
os.system(mkdirCommand)

copyCommand = "cp -r bower_components/rapidjson/include/rapidjson/ src/lib"
print(copyCommand)
os.system(copyCommand)

buildCommand = "scons"
print(buildCommand)
os.system(buildCommand)
