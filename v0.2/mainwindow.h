#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "ui/testlistwidget.h"

namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow {
    Q_OBJECT
private:
    Ui::MainWindow* ui;
    QMap<QString, QString> getParams(bool isFlow);
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
    void on_startTestButton_clicked();
    void on_startFlowButton_clicked();

public slots:
    void getDatasetContentStr(QString str);

signals:
    void requestDatasetsList();
    void requestDatasetContentStr(QString str);

    void requestStartFlowTest(QString name, QMap<QString, QString> params);
    void requestStartQuizTest(QString name, QMap<QString, QString> params);

};
#endif // MAINWINDOW_H
