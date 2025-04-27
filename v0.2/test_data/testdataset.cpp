#include "testdataset.h"

#include <fstream>
#include <locale>
#include <codecvt>

TestDataset::TestDataset(std::string datasetPath) {
    std::wifstream fileStream(datasetPath);
    std::wstring bufferString;
    fileStream.imbue(std::locale(fileStream.getloc(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>()));

    std::getline(fileStream, bufferString); this->name = bufferString;
    std::getline(fileStream, bufferString); this->type = bufferString;

    while(!fileStream.eof()){
        std::getline(fileStream, bufferString);
        if (!bufferString.empty()) {
            std::shared_ptr<TestData> elem = std::make_shared<TestData>(bufferString);
            if (elem->is_valid())
                this->addData(std::move(elem));
        }
    }
}

int TestDataset::getDataAmount(){
    return this->datas.size();
}

std::wstring TestDataset::getName(){
    return name;
}
void TestDataset::addData(std::shared_ptr<TestData> data){
    this->datas.push_back(std::move(data));
}

std::weak_ptr<TestData> TestDataset::getData(int index){
    return datas[index];
}

#include <QDebug>
std::wostream& operator<< (std::wostream& wout, const TestDataset& data){
    for (const std::shared_ptr<TestData>& item : data.datas)
        wout << item << std::endl;
    return wout;
}
std::wostream& operator<< (std::wostream& wout, const std::shared_ptr<TestDataset>& data){
    if (data)
        wout << *data;
    else
        wout << nullstr;
    return wout;
}
std::wostream& operator<< (std::wostream& wout, const std::weak_ptr<TestDataset>& data){
    if (!data.expired())
        wout << data.lock();
    else
        wout << nullstr;
    return wout;
}
