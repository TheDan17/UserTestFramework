#include "model.h"

using namespace std;

Model::Model() {
    this->datasets = make_unique<TestDatasetStore>();
    this->addCurrDirDSFiles();
    this->datasets->loadItems();

}
Model::~Model(){}

void Model::addCurrDirDSFiles(){
    string targetExtension = ".ds";
    vector<filesystem::path> matchedFiles;
    for (const auto& entry : filesystem::directory_iterator("."))
        if (entry.is_regular_file() && entry.path().extension() == targetExtension)
            matchedFiles.push_back(entry.path().filename());
    for (const auto& filename : matchedFiles)
        this->addDatasetPath(filename);
}

void Model::addDatasetPath(filesystem::path p){
    this->datasets->addItemPath(p);
}

// DATASETS
void Model::responseDatasetsList(){
    emit sendDatasetsList(datasets->getItemHeaders());
}
#include <sstream>
void Model::responseDatasetContentStr(wstring name){
    wstringstream stream;
    weak_ptr<TestDataset> dsPtr = this->datasets->getItemPtr(name);
    stream << dsPtr;
    emit sendDatasetContentStr(stream.str());
}

// BEFORE TEST
void Model::responseNewTestLot(wstring datasetName, map<wstring, wstring> params){
    weak_ptr<TestDataset> dsPtr = this->datasets->getItemPtr(datasetName);

    bool isRandomized, isAllAmount;
    int diffLevel, linesAmount;
    isRandomized = stoi(params.at(L"isRandomized"));
    isAllAmount = stoi(params.at(L"isAllAmount"));
    linesAmount = stoi(params.at(L"linesAmount"));
    diffLevel = stoi(params.at(L"difficultyLevel"));
    TestParams tParams;
    if (isAllAmount)
        tParams = {diffLevel, isRandomized, 0, TestParams::isAllAmount};
    else
        tParams = {diffLevel, isRandomized, 0, linesAmount};

    bool isFlow = stoi(params.at(L"isFlow"));
    if (isFlow)
        this->lotOfTests = factory->createTestsLot(dsPtr, move(tParams));
    else
        this->lotOfTests = vector<shared_ptr<Test>>{factory->createTest(dsPtr, move(tParams))};
    this->currentTestIndex = 0;
    this->responseSameTest();
}
void Model::responseNextTest() {
    currentTestIndex++;
    if (currentTestIndex == lotOfTests.size()) {
        currentTestIndex--;
        currentTest = nullptr;
    } else {
        currentTest = lotOfTests.at(currentTestIndex);
    }
    sendTestInternal();
}
void Model::responseSameTest() {
    if (currentTestIndex == lotOfTests.size())
        currentTest = nullptr;
    else
        currentTest = lotOfTests.at(currentTestIndex);
    sendTestInternal();
}
void Model::sendTestInternal() {
    if (currentTest)
        emit sendTest(currentTest->getStrData());
    else
        emit sendTest(vector<vector<wstring>>());
}

// AFTER TEST
void Model::responseTestSummary(vector<vector<wstring>> input){
    if (currentTest) {
        auto summary = currentTest->checkInput(input);
        emit sendTestSummary(summary.allLines, summary.doneLines, summary.isPassed);
    }
}
void Model::responseTestResult(vector<vector<wstring>> input){
    if (currentTest)
        emit sendTestResult(move(currentTest->defineInput(input)));
}
void Model::responseTestAnswers(){
    if (currentTest)
        emit sendTestAnswers(move(currentTest->getStrRaw()));
}
