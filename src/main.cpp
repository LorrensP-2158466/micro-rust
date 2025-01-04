
#include "driver/mr_driver.hpp"
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

using namespace mr;

int main(int argc, char** argv) {
    driver::MRDriver driver{argc, argv};
    return driver.start();
}
