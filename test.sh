#!/bin/bash

# Clean up
rm -rf test

# Create the test directory
mkdir test

# Prepare the test data
echo "Generating test data..."
mkdir test/dirA
mkdir test/dirB
mkdir test/dirOut
mkdir test/dirAssert
./build/TestFileGenerator $(pwd)/test/dirA $(pwd)/test/dirB $(pwd)/test/dirAssert 50000
sort -o test/dirAssert/a_only test/dirAssert/a_only
sort -o test/dirAssert/b_only test/dirAssert/b_only
sort -o test/dirAssert/common test/dirAssert/common

# Run the test
echo "Running the test..."
./build/FileSeparator $(pwd)/test/dirA $(pwd)/test/dirB $(pwd)/test/dirOut
sort -o test/dirOut/a_only test/dirOut/a_only
sort -o test/dirOut/b_only test/dirOut/b_only
sort -o test/dirOut/common test/dirOut/common

# Compare the output with the expected result
diff -r test/dirOut test/dirAssert
if [ $? -eq 0 ]; then
    echo "Test passed"
else
    echo "Test failed"
fi