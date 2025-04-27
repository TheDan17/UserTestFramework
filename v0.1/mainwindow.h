#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "ui/testlistwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
private:
    Ui::MainWindow* ui;
    TestListWidget* currTest = nullptr;
    QList<QStringList> currTestInput;
    short isFilled = -1;

    void replaceTestList(QListWidget* newList);
    void fixTestInput();
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setDatasetList(QStringList data);
private slots:
    // actions
    void on_showTestResultDialog_triggered();
    void on_showDatasetAction_triggered();
    void on_requestDatasetUpdateAction_triggered();
    void on_showDatasetContentAction_triggered();
    // buttons
    void on_endTestButton_clicked();
    void on_startTestButton_clicked();

public slots:
    void getDatasetContentStr(QString str);
    void getNewTest(QList<QStringList> testRows);
    void getTestSummary(int all, int done, bool isPassed);
    void getTestResult(QList<QList<bool>> marks);
    void getTestAnswers(QList<QStringList> answers);

signals:
    void requestDatasetsList();
    void requestDatasetContentStr(QString str);

    void requestNewTest(QString dsName, QMap<QString, QString> params);
    void requestTestSummary(QList<QStringList> data);
    void requestTestResult(QList<QStringList> data);
    void requestTestAnswers();
};
#endif // MAINWINDOW_H
