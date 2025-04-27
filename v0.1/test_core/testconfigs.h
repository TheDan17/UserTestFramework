#ifndef TESTCONFIGS_H
#define TESTCONFIGS_H

#include <vector>

#include "../test/testparams.h"

class TestConfigs {
public:
    std::vector<TestParams*> configsData;
    TestConfigs();
};

#endif // TESTCONFIGS_H
