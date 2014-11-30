Algorithm
========

Install
-------

Just run the install.py script. This should:
* Get all the dependencies using bower
* Copy all the dependencies from bower_components into src/lib
* Run an initial SConstruct command

If you are not changing the C++ code, you should be good to go


Build
-----

run scons in the algorithm folder

The main artifact is going to be in the ./build folder

Testing
-------

### Running ALL tests ###
Execute runTests.py in the algorithm folder. Note that you *must* first
have run install.py at some point (in order to pull down and install the
GoogleTest libraries).

Output will be printed to the console; you can also examine the test output
more closely as XML output will be placed in the test folder.

Note that when pushing to Jenkins, all tests will automatically be run.

### Running specific tests ###
Execute scons in the algorithm folder. Then navigate to the test folder and
run the relevant test executable. Output will be printed to the console.

Libraries
---------

C++ Json
https://github.com/vivkin/gason/
