# file-separator

This program categorizes files into a_only, b_only and common categories depending on their occurence (based on content) in directory A, or B or both.

It is C++17 compatible and uses cmake to define the build process. It depends on OpenSSL. The bash scripts were written and tested on Linux.

## Build

Run build.sh to generate the build artifacts.

## Test

Run test.sh to generate the test fixtures and run the tests.

## Clean

Optionally run clean.sh to delete the build and test folders. Note that the build and test scripts also perform their own cleanup as a preliminary step, such
that it is not necessary to run clean.sh in between build.sh or test.sh runs.

## Run

Run run.sh with unnamed parameters directoryA, directoryB and directoryOut (output directory) in order to run the program on custom data.