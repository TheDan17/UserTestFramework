#include "controller.h"

// datasets
void Controller::getDatasetContentStr(std::wstring str){
    emit sendDatasetContentStr(QString::fromStdWString(str));
}
void Controller::getDatasetsList(std::vector<std::wstring> array){
    QStringList list;
    for (auto& str : array)
        list.append(QString::fromStdWString(str));
    emit sendDatasetsList(std::move(list));
}

// beforeTest
void Controller::responseNewTest(QString dsName, QMap<QString, QString> params){
    std::wstring newName = dsName.toStdWString();
    std::map<std::wstring, std::wstring> newParams;
    for (const auto& key : params.keys()){
        newParams[key.toStdWString()] = params[key].toStdWString();
    }
    emit requestNewTest(newName, newParams);
}
void Controller::getTest(std::vector<std::vector<std::wstring>> array){
    QList<QStringList> testList;
    for (const auto& row : array){
        QStringList rowList;
        for (const auto& col : row)
            rowList.append(QString::fromStdWString(col));
        testList.append(rowList);
    }
    emit sendTest(std::move(testList));
}

// afterTest
void Controller::getTestResult(std::vector<std::vector<bool>> array){
    QList<QList<bool>> newArray;
    for (const auto& row : array){
        QList<bool> newRow;
        for (const auto& col : row)
            newRow.append(col);
        newArray.append(newRow);
    }
    emit sendTestResult(newArray);
}
void Controller::getTestAnswers(std::vector<std::vector<std::wstring>> array){
    QList<QStringList> newArray;
    for (const auto& row : array){
        QStringList newRow;
        for (const auto& col : row)
            newRow.append(QString::fromStdWString(col));
        newArray.append(newRow);
    }
    emit sendTestAnswers(newArray);
}
void Controller::responseTestSummary(QList<QStringList> data){
    std::vector<std::vector<std::wstring>> newData;
    for (auto& row : data){
        std::vector<std::wstring> newRow;
        for (auto& col : row)
            newRow.push_back(col.toStdWString());
        newData.push_back(newRow);
    }
    emit requestTestSummary(newData);
}
void Controller::responseTestResult(QList<QStringList> data){
    std::vector<std::vector<std::wstring>> newData;
    for (auto& row : data){
        std::vector<std::wstring> newRow;
        for (auto& col : row)
            newRow.push_back(col.toStdWString());
        newData.push_back(newRow);
    }
    emit requestTestResult(newData);
}

