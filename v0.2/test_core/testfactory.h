#ifndef TESTFACTORY_H
#define TESTFACTORY_H

#include "../test/test.h"
#include "../test/testparams.h"
#include "../test_data/testdataset.h"

class TestFactory {
private:
    std::pair<std::vector<int>, std::vector<std::weak_ptr<TestData>>> createTestContent(std::weak_ptr<TestDataset> data, TestParams params);
public:
    TestFactory();
    std::shared_ptr<Test> createTest(std::weak_ptr<TestDataset> data, TestParams params);
    std::vector<std::shared_ptr<Test>> createTestsLot(std::weak_ptr<TestDataset>, TestParams params);
};

#endif // TESTFACTORY_H
