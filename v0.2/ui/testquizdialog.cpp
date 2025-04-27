#include "testquizdialog.h"
#include "ui_testquizdialog.h"

TestQuizDialog::TestQuizDialog(QWidget *parent) : QDialog(parent),
                                                  ui(new Ui::TestQuizDialog) {
    ui->setupUi(this);
}

TestQuizDialog::~TestQuizDialog() {
    delete ui;
}

void TestQuizDialog::setTestReq(QPair<QString, QMap<QString, QString> > testReq){

}

void TestQuizDialog::replaceTestList(QListWidget* newList){
    QWidget* oldListWidget = this->ui->testContainer->itemAt(0)->widget();
    this->ui->testContainer->removeWidget(oldListWidget);
    delete (QListWidget*)oldListWidget;
    this->ui->testContainer->addWidget(newList);
}

void TestQuizDialog::fixTestInput(){
    if (currTest == nullptr)
        return;
    currTestInput = currTest->getTestData();
    currTest->setUnactiveAll(true);
}


#include "testlistwidget.h"
void TestQuizDialog::getNewTest(QList<QStringList> testRows){
    // init test
    auto testList = new TestListWidget(this->ui->testLayout->widget());
    for (int i = 0; i < testRows.count(); i++)
        testList->addTestRow(i+1, testRows[i]);
    this->currTest = testList;
    this->replaceTestList(currTest);
}


#include <QtMath>
#include "testsummarydialog.h"
void TestQuizDialog::getTestSummary(int all, int done, bool isPassed){
    this->ui->endTestButton->setDisabled(true);
    auto dialog = new TestSummaryDialog(this);
    dialog->setSummaryMark(all, done);
    dialog->setSummaryPercentage(qBound(0, qFloor((double)done / all * 100.0), 100));
    dialog->setSummaryPassed(isPassed);

    QListWidget* buff;
    switch(dialog->exec()){
    case QDialog::Rejected : // clear test
        buff = new QListWidget(this);
        buff->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        this->replaceTestList(buff);
        currTest = nullptr;
        break;
    case QDialog::Accepted : // mark test
        emit requestTestResult(currTestInput);
        emit requestTestAnswers();
    }
}

void TestQuizDialog::getTestResult(QList<QList<bool>> marks){
    if (currTest != nullptr)
        currTest->setTestMarks(marks);
}

void TestQuizDialog::getTestAnswers(QList<QStringList> answers){
    if (currTest != nullptr)
        currTest->setAnswers(answers);
}

#include "testsummarydialog.h"
void TestQuizDialog::on_endTestButton_clicked() {
    this->ui->endTestButton->setDisabled(true);
    fixTestInput();
    emit requestTestSummary(currTestInput);
    //isFilled = -1;
}
