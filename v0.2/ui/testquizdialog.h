#ifndef TESTQUIZDIALOG_H
#define TESTQUIZDIALOG_H

#include <QDialog>

#include "../ui/testlistwidget.h"

namespace Ui { class TestQuizDialog; }

class TestQuizDialog : public QDialog {
    Q_OBJECT
private:
    Ui::TestQuizDialog *ui;
    TestListWidget* currTest = nullptr;
    QList<QStringList> currTestInput;

    void replaceTestList(QListWidget* newList);
    void fixTestInput();
public:
    explicit TestQuizDialog(QWidget *parent = nullptr);
    ~TestQuizDialog();
    void setTestReq(QPair<QString, QMap<QString, QString>> testReq);

private slots:
    void on_endTestButton_clicked();

public slots:
    void getNewTest(QList<QStringList> testRows);
    void getTestSummary(int all, int done, bool isPassed);
    void getTestResult(QList<QList<bool>> marks);
    void getTestAnswers(QList<QStringList> answers);

signals:
    void requestNewTest(QString dsName, QMap<QString, QString> params);
    void requestTestSummary(QList<QStringList> data);
    void requestTestResult(QList<QStringList> data);
    void requestTestAnswers();
};

#endif // TESTQUIZDIALOG_H
