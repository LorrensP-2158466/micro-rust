#!/usr/bin/env fish

# Iterate over each file in the testfiles directory
for file in testfiles/*
    echo "Testing file: $file"
    ./build/mr "$file"
    echo 
end