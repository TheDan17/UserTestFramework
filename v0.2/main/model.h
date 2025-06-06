#ifndef MODEL_H
#define MODEL_H

#include <map>
#include <memory>
#include <QObject>

#include "../test_core/testfactory.h"
#include "../test_data/testdatasetstore.h"

class Model : public QObject {
    Q_OBJECT
private:
    std::unique_ptr<TestDatasetStore> datasets;
    std::unique_ptr<TestFactory> factory;

    std::vector<std::shared_ptr<Test>> lotOfTests;
    std::shared_ptr<Test> currentTest;
    int currentTestIndex;

    void addCurrDirDSFiles(); // scan dataset files
    void sendTestInternal();
public:
    Model();
    ~Model();
    void addDatasetPath(std::filesystem::path p);
    void removeDatasetPath(std::filesystem::path p);
    void reloadDatasets();

// <- View
public slots:
    //void getDataset(wstring datasetName){}  - it's for unknown
    //void getDatasetPaths(){}  - it's for future functionality
    void responseDatasetsList();
    void responseDatasetContentStr(std::wstring dsName);

    void responseNewTestLot(std::wstring dsName, std::map<std::wstring, std::wstring> params);
    void responseNextTest();
    void responseSameTest();

    void responseTestSummary(std::vector<std::vector<std::wstring>> input);
    void responseTestResult(std::vector<std::vector<std::wstring>> input);
    void responseTestAnswers();

// -> View
signals:
    void sendDataset(std::vector<std::vector<std::wstring>> array);
    void sendDatasetPaths(std::vector<std::filesystem::path> array);
    void sendDatasetsList(std::vector<std::wstring> array);
    void sendDatasetContentStr(std::wstring str);

    void sendTest(std::vector<std::vector<std::wstring>> testStrings);
    void sendTestSummary(int allAmount, int doneAmount, bool isPassed);
    void sendTestResult(std::vector<std::vector<bool>> testMarks);
    void sendTestAnswers(std::vector<std::vector<std::wstring>> answers);
};

#endif // MODEL_H
