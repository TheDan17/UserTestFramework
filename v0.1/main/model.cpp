#include "model.h"

Model::Model() {
    this->datasets = std::make_unique<TestDatasetStore>();
    this->addCurrDirDSFiles();
    this->datasets->loadItems();

}
Model::~Model(){}

void Model::addCurrDirDSFiles(){
    std::string targetExtension = ".ds";
    std::vector<std::filesystem::path> matchedFiles;
    for (const auto& entry : std::filesystem::directory_iterator("."))
        if (entry.is_regular_file() && entry.path().extension() == targetExtension)
            matchedFiles.push_back(entry.path().filename());
    for (const auto& filename : matchedFiles)
        this->addDatasetPath(filename);
}

void Model::addDatasetPath(std::filesystem::path p){
    this->datasets->addItemPath(p);
}

// datasets
void Model::responseDatasetsList(){
    emit sendDatasetsList(datasets->getItemHeaders());
}
#include <sstream>
void Model::responseDatasetContentStr(std::wstring name){
    std::wstringstream stream;
    std::weak_ptr<TestDataset> dsPtr = this->datasets->getItemPtr(name);
    stream << dsPtr;
    emit sendDatasetContentStr(stream.str());
}

// beforeTest
void Model::responseNewTest(std::wstring datasetName, std::map<std::wstring, std::wstring> params){
    std::weak_ptr<TestDataset> dsPtr = this->datasets->getItemPtr(datasetName);
    bool isRandomized, isAllAmount;
    int diffLevel, linesAmount;
    isRandomized = std::stoi(params.at(L"isRandomized"));
    isAllAmount = std::stoi(params.at(L"isAllAmount"));
    linesAmount = std::stoi(params.at(L"linesAmount"));
    diffLevel = std::stoi(params.at(L"difficultyLevel"));
    TestParams tParams;
    if (isAllAmount)
        tParams = {diffLevel, isRandomized, 0, TestParams::isAllAmount};
    else
        tParams = {diffLevel, isRandomized, 0, linesAmount};
    this->currentTest = this->factory->createTest(dsPtr, std::move(tParams));
    emit sendTest(currentTest->getStrData());
}

// afterTest
void Model::responseTestSummary(std::vector<std::vector<std::wstring>> input){
    if (!currentTest) return;
    auto summary = currentTest->checkInput(input);
    emit sendTestSummary(summary.allLines, summary.doneLines, summary.isPassed);
}
void Model::responseTestResult(std::vector<std::vector<std::wstring>> input){
    if (!currentTest) return;
    emit sendTestResult(std::move(currentTest->defineInput(input)));
}
void Model::responseTestAnswers(){
    if (!currentTest) return;
    emit sendTestAnswers(std::move(currentTest->getStrRaw()));
}
