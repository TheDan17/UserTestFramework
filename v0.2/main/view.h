#ifndef VIEW_H
#define VIEW_H

#include <QObject>
#include <QString>
#include <QList>
#include <QFileInfo>

#include "../mainwindow.h"
#include "../ui/testflowdialog.h"
#include "../ui/testquizdialog.h"

class View : public QObject {
    Q_OBJECT
public:
    MainWindow* w;
    TestFlowDialog* testFlowDiag;
    TestQuizDialog* testQuizDiag;

    View();
    ~View();
    void requestUpdate(){emit requestDatasetsList();}

// from MainWindow
private slots:
    void responseDatasetsList(){emit requestDatasetsList();}
    void responseStartQuizTest(QString n, QMap<QString, QString> p);
    void responseStartFlowTest(QString n, QMap<QString, QString> p);

// from Model
public slots:
    void getDataset(QList<QStringList> array){}
    void getDatasetPaths(QList<QFileInfo> array){}
    void getDatasetsList(QStringList array);

    void getTest(QList<QStringList> array){emit sendTest(array);}

    void getTestResult(QList<QList<bool>> array){emit sendTestResult(array);}
    void getTestSummary(int allAmount, int doneAmount, bool isPassed){emit sendTestSummary(allAmount, doneAmount, isPassed);}
    void getTestAnswers(QList<QStringList> array){emit sendTestAnswers(array);}
signals:
    void sendTest(QList<QStringList> array);
    void sendTestResult(QList<QList<bool>> array);
    void sendTestSummary(int allAmount, int doneAmount, bool isPassed);
    void sendTestAnswers(QList<QStringList> array);

// to Model
public slots:
    void responseNewTestLot(QString DSName, QMap<QString, QString> testParams) {emit requestNewTestLot(DSName, testParams);}
    void responseSameTest(){emit requestSameTest();}
    void responseNextTest(){emit requestNextTest();}
    void responseTestResult(QList<QStringList> input) {emit requestTestResult(input);}
    void responseTestAnswers(){emit requestTestAnswers();}
signals:
    void requestDatasetsList();
    void requestCheckTest(QList<QStringList> data);
    void requestDetailedCheckTest(QList<QStringList> data);

    void requestNewTestLot(QString DSName, QMap<QString, QString> testParams);
    void requestSameTest();
    void requestNextTest();
    void requestTestResult(QList<QStringList> input);
    void requestTestAnswers();
};

#endif // VIEW_H
