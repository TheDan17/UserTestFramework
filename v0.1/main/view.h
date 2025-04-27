#ifndef VIEW_H
#define VIEW_H

#include <QObject>
#include <QString>
#include <QList>
#include <QFileInfo>

#include "../mainwindow.h"
#include "../ui/testlistwidget.h"

class View : public QObject {
    Q_OBJECT
private:
    TestListWidget* currTest = nullptr;
public:
    MainWindow* w;
    View();
    void requestUpdate(){emit requestDatasetsList();}
public slots:
    void closeTestButtonPressed(){}
// from Model
public slots:
    void getDataset(QList<QStringList> array){}
    void getDatasetPaths(QList<QFileInfo> array){}
    void getDatasetsList(QStringList array);
\
    void getTest(QList<QStringList> array){}
    void getTestSummary(int allAmount, int doneAmount, bool isPassed){}
    void getTestAnswered(QList<QStringList> array){}
    void getTestResult(QList<QList<bool>> array){}
// from MainWindow
public slots:
    void responseDatasetsList(){emit requestDatasetsList();}
// to Model
signals:
    void requestDatasetsList();
    void requestNewTest();
    void requestCheckTest(QList<QStringList> data);
    void requestDetailedCheckTest(QList<QStringList> data);
};

#endif // VIEW_H
