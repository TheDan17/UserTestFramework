#ifndef TESTFACTORY_H
#define TESTFACTORY_H

#include "../test/test.h"
#include "../test/testparams.h"
#include "../test_data/testdataset.h"

class TestFactory {
public:
    TestFactory();
    std::unique_ptr<Test> createTest(std::weak_ptr<TestDataset> data, TestParams params);
};

#endif // TESTFACTORY_H
