#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QString>
#include <QVector>
#include <QFileInfo>

#include "model.h"

class Controller : public QObject {
    Q_OBJECT
    Model* model;
public:
    Controller(Model* model) : model(model) {}

// Model -> View
public slots:
    void getDataset(std::vector<std::vector<std::wstring>> array){}
    void getDatasetPaths(std::vector<std::filesystem::path> array){}
    void getDatasetsList(std::vector<std::wstring> array);
    void getDatasetContentStr(std::wstring str);
    void getTest(std::vector<std::vector<std::wstring>> array);
    void getTestResult(std::vector<std::vector<bool>> array);
    void getTestAnswers(std::vector<std::vector<std::wstring>> array);
signals:
    void sendDataset(QList<QStringList> data);
    void sendDatasetPaths(QList<QFileInfo> paths);
    void sendDatasetsList(QStringList names);
    void sendDatasetContentStr(QString str);
    void sendTest(QList<QStringList> data);
    void sendTestSummary(int allAmount, int doneAmount, bool isPassed);
    void sendTestResult(QList<QList<bool>> marks);
    void sendTestAnswers(QList<QStringList> rightData);

// View -> Model
public slots:
    void responseDatasetContentStr(QString name){emit requestDatasetContentStr(name.toStdWString());}
    void responseDatasetsList(){emit requestDatasetsList();}
    void responseNewTest(QString dsName, QMap<QString, QString> params);
    void responseTestSummary(QList<QStringList> data);
    void responseTestResult(QList<QStringList> data);
signals:
    void requestDatasetContentStr(std::wstring name);
    void requestDatasetsList();
    void requestNewTest(std::wstring dsName, std::map<std::wstring, std::wstring> params);
    void requestTestSummary(std::vector<std::vector<std::wstring>> data);
    void requestTestResult(std::vector<std::vector<std::wstring>> data);
};

#endif // CONTROLLER_H
