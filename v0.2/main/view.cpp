#include "view.h"

View::View() {
    this->w = new MainWindow;
    w->setWindowTitle("TestingWords v0.2");
    w->setWindowIcon(QIcon("TestingWords.ico"));
    w->show();
    QObject::connect(w, &MainWindow::requestDatasetsList,
                     this, &View::responseDatasetsList);

    this->testFlowDiag = new TestFlowDialog();
    QObject::connect(w, &MainWindow::requestStartFlowTest, this, &View::responseStartFlowTest);
    this->testQuizDiag = new TestQuizDialog();
    QObject::connect(w, &MainWindow::requestStartQuizTest, this, &View::responseStartQuizTest);

    QObject::connect(testFlowDiag, &TestFlowDialog::requestNewTestLot, this, &View::responseNewTestLot);
    QObject::connect(this, &View::sendTest, testFlowDiag, &TestFlowDialog::getTest);

    QObject::connect(testFlowDiag, &TestFlowDialog::requestSameTest, this, &View::responseSameTest);
    QObject::connect(testFlowDiag, &TestFlowDialog::requestNextTest, this, &View::responseNextTest);

    QObject::connect(testFlowDiag, &TestFlowDialog::requestTestResult, this, &View::responseTestResult);
    QObject::connect(this, &View::sendTestResult, testFlowDiag, &TestFlowDialog::getTestResult);

    QObject::connect(testFlowDiag, &TestFlowDialog::requestTestAnswers, this, &View::responseTestAnswers);
    QObject::connect(this, &View::sendTestAnswers, testFlowDiag, &TestFlowDialog::getTestAnswers);
}
View::~View() {
    delete testFlowDiag;
    delete testQuizDiag;
}

void View::responseStartQuizTest(QString n, QMap<QString, QString> p){
    this->testQuizDiag->setTestReq({n, p});
    this->testQuizDiag->exec();
}
void View::responseStartFlowTest(QString n, QMap<QString, QString> p){
    this->testFlowDiag->makeTestReq({n, p});
    this->testFlowDiag->exec();
    this->testFlowDiag->hide();
}

#include <QMessageBox>
void showDatasetsList(QStringList array){
    QString titleStr("Получен список датасетов"), buttonStr("Okay, I guess");
    QString msgStr("Всего датасетов: " + QString::number(array.size()) + "\n");
    for (int i = 0; i < array.size(); i++)
        msgStr += (QString::number(i+1) + ": " + array[0] + "\n");
    QMessageBox::information(nullptr, titleStr, msgStr, buttonStr);
}

void View::getDatasetsList(QStringList array){
    w->setDatasetList(array);
    //showDatasetsList(array);
}
