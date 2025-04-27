#ifndef TESTDATASET_H
#define TESTDATASET_H

#include "../test_data/testdata.h"

#include <string>
#include <vector>
#include <memory>
#include <iostream>

class TestDataset {
    friend std::wostream& operator<< (std::wostream& wout, const TestDataset& data);
private:
    std::wstring name;
    std::wstring type;
    std::vector<std::shared_ptr<TestData>> datas;
public:
    TestDataset(std::string datasetPath);
    int getDataAmount();
    std::wstring getName();

    void reload(){}
    void save(){}

    void addData(std::shared_ptr<TestData> data);
    void removeData(int index);
    std::weak_ptr<TestData> getData(int index);
};

std::wostream& operator<< (std::wostream& wout, const TestDataset& data);
std::wostream& operator<< (std::wostream& wout, const std::shared_ptr<TestDataset>& data);
std::wostream& operator<< (std::wostream& wout, const std::weak_ptr<TestDataset>& data);

#endif // TESTDATASET_H
