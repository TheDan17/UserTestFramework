#ifndef TEST_H
#define TEST_H

#include "testline.h"

#include <vector>
#include <memory>

struct TestSummary{
    int doneLines;
    int allLines;
    bool isPassed;
};

class Test {
private:
    short minPassPercent = 100;
public:
    std::vector<std::unique_ptr<TestLine>> lines;

    Test(std::vector<std::unique_ptr<TestLine>> testElems) : lines(std::move(testElems)) {}
    std::vector<std::vector<std::wstring>> getStrData();
    std::vector<std::vector<std::wstring>> getStrRaw();
    TestSummary checkInput(std::vector<std::vector<std::wstring>> input);
    std::vector<std::vector<bool>> defineInput(std::vector<std::vector<std::wstring>> input);
};

#endif // TEST_H
