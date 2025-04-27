#ifndef TESTFLOWDIALOG_H
#define TESTFLOWDIALOG_H

#include <QDialog>
#include <QKeyEvent>

namespace Ui { class TestFlowDialog; }

enum FlowStatus { NOTHING, CHECKED_RIGHT, CHECKED_WRONG, END, WAITING };
enum ElemType { FLINE_EDIT, FLABEL };

class TestFlowDialog : public QDialog {
    Q_OBJECT
private:
    // UI
    Ui::TestFlowDialog *ui;
    QList<QLayout*> currentLayouts;
    QList<QPair<QWidget*, enum ElemType>> currentElems;

    // DATA
    enum FlowStatus currentStatus;
    int rightScore, wrongScore, allScore;
    QList<QStringList> capturedInput;

    // FUNCTIONALITY
    void addScore(int plus, bool isRight);
    void updateMetrics();
    void captureTestInput();
    void catchedEnterKey();
    void clearTestElems();

    // STATUS APPEARANCES
    void makeStarting();
    void makeRightChecked();
    void makeWrongChecked();
    void makeFinished();

protected:
    void keyPressEvent(QKeyEvent* keyEvent);

public:
    TestFlowDialog(QWidget *parent = nullptr);
    ~TestFlowDialog();
    void makeTestReq(QPair<QString, QMap<QString, QString>> testReq);

signals:
    void requestNewTestLot(QString n, QMap<QString, QString> p);
    void requestSameTest();
    void requestNextTest();
    void requestTestResult(QList<QStringList> input);
    void requestTestAnswers();

public slots:
    void getTest(QList<QStringList> data);
    void getTestResult(QList<QList<bool>> marks);
    void getTestAnswers(QList<QStringList> answers);
};

#endif // TESTFLOWDIALOG_H
