#include "test.h"

std::vector<std::vector<std::wstring>> Test::getStrData(){
    std::vector<std::vector<std::wstring>> dataArr;
    for (auto& line : lines)
        dataArr.push_back(line->getStrData());
    return std::move(dataArr);
}

std::vector<std::vector<std::wstring>> Test::getStrRaw(){
    std::vector<std::vector<std::wstring>> dataArr;
    for (auto& line : lines)
        dataArr.push_back(line->getRawData());
    return std::move(dataArr);
}

#include <cmath>
TestSummary Test::checkInput(std::vector<std::vector<std::wstring>> input){
    double all = this->lines.size();
    int done = 0; bool lineTrue;
    for (int i = 0; i < all; i++){
        lineTrue = true;
        auto& inputLineStr = input[i];
        auto& testLine = lines[i];
        std::vector<std::wstring> testLineStr = testLine->getRawData();
        for (int j = 0; j < 4; j++){
            if (testLineStr[j] != inputLineStr[j])
                lineTrue = false;
        }
        if (lineTrue)
            done++;
    }
    double checkPercent = std::floor(done/all*100.0);
    bool isPassed;
    if (checkPercent >= minPassPercent)
        isPassed = true;
    else
        isPassed = false;
    return {done, all, isPassed};
}

std::vector<std::vector<bool>> Test::defineInput(std::vector<std::vector<std::wstring>> input){
    double all = this->lines.size();
    std::vector<std::vector<bool>> reg;
    for (int i = 0; i < all; i++){
        auto regLine = std::vector<bool>(4);
        auto& inputLineStr = input[i];
        auto& testLine = lines[i]; auto testLineStr = testLine->getRawData();
        for (int j = 0; j < 4; j++)
            regLine[j] = (testLineStr[j] == inputLineStr[j]);
        reg.push_back(std::move(regLine));
    }
    return std::move(reg);
}
