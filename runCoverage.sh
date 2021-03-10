#!/bin/bash

make clean-tests
make coverage -j8
mkdir -p coverage

echo ""
echo "Running ./covTanks to create gco files"
./platform -coverage

echo ""
echo "Creating gcno files"
#find . -type f -name '*.gcno' -exec gcov {} +

lcov --no-external --capture --initial --directory src --output-file coverage/platform_base.info
find . -type f -name '*.gcda' -exec rm {} +

echo ""
echo "Running gprof for timing"
gprof ./platform > coverage/gprofresults.txt

echo "Creating test files"
make tests PROFILE="-pg -fprofile-arcs -ftest-coverage" -j8

echo "Running Unit Test files"
./testUnitAll

echo ""
echo "Creating gcno files"
#find . -type f -name '*.gcno' -exec gcov {} +

lcov --no-external --capture --directory . --output-file coverage/platform_unit.info
find . -type f -name '*.gcda' -exec rm {} +

echo ""
echo "Running Functional Test files"
./testFunctionalAll

echo ""
echo "Ceating gcno files"
#find . -type f -name '*.gcno' -exec gcov {} +

lcov --no-external --capture --directory . --output-file coverage/platform_functional.info

echo ""
echo "Creating HTML report with lcov"
#lcov --no-external --directory src/ --capture --output-file coverage/coverage.info
lcov --no-external --add-tracefile coverage/platform_base.info \
        --add-tracefile coverage/platform_unit.info \
        --add-tracefile coverage/platform_functional.info \
        --output-file coverage/coverage.info

echo ""
echo "Cleaning up after, coverage files in coverage/ folder"
find . -type f -name '*.gc*' -exec rm {} +

echo ""
echo "Create a fancy web page"
lcov --summary coverage/coverage.info;
genhtml coverage/coverage.info --output-directory coverage -quiet;
