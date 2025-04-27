#include "testline.h"

TestLine::TestLine(std::shared_ptr<TestData> o, std::vector<int> i)
    : origData(std::move(o)), hideDataIndexes(i) {}

std::vector<std::wstring> TestLine::getStrData(){
    std::vector<std::wstring> origDataArr = this->getRawData();
    for (auto& index : hideDataIndexes)
        origDataArr[index] = L"";
    return std::move(origDataArr);
}

std::vector<std::wstring> TestLine::getRawData(){
    std::vector<std::wstring> origDataArr;
    origDataArr.push_back(origData->rusWord);
    origDataArr.push_back(origData->engFirstForm);
    origDataArr.push_back(origData->engSecondForm);
    origDataArr.push_back(origData->engThirdForm);
    return std::move(origDataArr);
}
