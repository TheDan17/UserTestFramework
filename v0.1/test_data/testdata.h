#ifndef TESTDATA_H
#define TESTDATA_H

#include <string>
#include <memory>

extern std::wstring nullstr;

struct TestDataBox {
    std::wstring r;
    std::wstring ef;
    std::wstring es;
    std::wstring et;
    bool isValid;
};

class TestData {
    friend std::wostream& operator<< (std::wostream& wout, const TestData& data);
private:
    void move_data (TestDataBox data);
    bool isValid;
public:
    std::wstring rusWord;
    std::wstring engFirstForm;
    std::wstring engSecondForm;
    std::wstring engThirdForm;

    TestData(std::wstring r, std::wstring ef, std::wstring es, std::wstring et);
    TestData(std::wstring rawData);
    TestData(TestDataBox data);

    bool is_valid();
};

std::wostream& operator<< (std::wostream &wout, const TestData& data);
std::wostream& operator<< (std::wostream& wout, const std::shared_ptr<TestData> data);

#endif // TESTDATA_H
