#include "testfactory.h"

TestFactory::TestFactory() {}

#include <algorithm>
#include <random>
std::pair<std::vector<int>, std::vector<std::weak_ptr<TestData>>> TestFactory::createTestContent(std::weak_ptr<TestDataset> data, TestParams params){
    std::shared_ptr<TestDataset> dataset = data.lock();
    // INDEXES FOR ALL LINES
    std::vector<int> dataHideIndexes {};
    switch (params.difficultyLevel){
    case 1: // 1 - 0 - 1 - 1
        dataHideIndexes.push_back(1);
        break;
    case 2: // 1 - 1 - 0 - 1
        dataHideIndexes.push_back(2);
        break;
    case 3: // 1 - 1 - 1 - 0
        dataHideIndexes.push_back(3);
        break;
    case 4: // 1 - 1 - 0 - 0
        dataHideIndexes.push_back(2);
        dataHideIndexes.push_back(3);
        break;
    case 5: // 1 - 0 - 0 - 0
        dataHideIndexes.push_back(1);
        dataHideIndexes.push_back(2);
        dataHideIndexes.push_back(3);
        break;
    case 6: // 0 - 0 - 0 - 1
        dataHideIndexes.push_back(0);
        dataHideIndexes.push_back(1);
        dataHideIndexes.push_back(2);
        break;
    }
    // TEST DATA CONTENT
    std::vector<std::weak_ptr<TestData>> dataContent;
    for (int i = 0; i < dataset->getDataAmount(); i++)
        dataContent.push_back(dataset->getData(i));
    int amount;
    if (params.isAllAmount)
        amount = dataset->getDataAmount();
    else
        amount = params.testLinesAmount;

    std::random_device device;
    std::default_random_engine generator(device());
    std::vector<std::weak_ptr<TestData>> testContent;
    for (int i = 0; i < amount; i++){
        std::uniform_int_distribution<int> range(0, dataContent.size()-1);
        int dataIndex = range(generator);
        testContent.push_back(dataContent[dataIndex]);
        dataContent.erase(dataContent.begin() + dataIndex);
    }
    return {std::move(dataHideIndexes), std::move(testContent)};
}

std::shared_ptr<Test> TestFactory::createTest(std::weak_ptr<TestDataset> dataset, TestParams params){
    auto testContentPair = createTestContent(dataset, std::move(params));
    auto dataHideIndexes = testContentPair.first;
    auto testContent = testContentPair.second;
    std::vector<std::unique_ptr<TestLine>> testLines;
    std::shared_ptr<TestData> bufferData;
    for (auto& dataWeakPtr : testContent){
        bufferData = dataWeakPtr.lock();
        testLines.push_back(std::make_unique<TestLine>(bufferData, dataHideIndexes));
    }
    return std::move(std::make_shared<Test>(std::move(testLines)));
}

std::vector<std::shared_ptr<Test>> TestFactory::createTestsLot(std::weak_ptr<TestDataset> dataset, TestParams params){
    auto testContentPair = createTestContent(dataset, std::move(params));
    auto dataHideIndexes = testContentPair.first;
    auto testContent = testContentPair.second;
    std::vector<std::shared_ptr<Test>> testArr;
    std::shared_ptr<TestData> bufferData;
    for (auto& dataPtr : testContent){
        bufferData = dataPtr.lock();
        testArr.push_back(std::make_shared<Test>(std::make_unique<TestLine>(bufferData, dataHideIndexes)));
    }
    return std::move(testArr);
}
