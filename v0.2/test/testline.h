#ifndef TESTLINE_H
#define TESTLINE_H

#include "../test_data/testdata.h"

#include <vector>
#include <memory>

class TestLine {
private:
    std::shared_ptr<TestData> origData;
    std::vector<int> hideDataIndexes;
public:
    TestLine(std::shared_ptr<TestData> o, std::vector<int> i);
    std::vector<std::wstring> getStrData();
    std::vector<std::wstring> getRawData();
};

#endif // TESTLINE_H
