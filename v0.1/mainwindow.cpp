#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) { ui->setupUi(this); }
MainWindow::~MainWindow() { delete ui; }


void MainWindow::replaceTestList(QListWidget* newList){
    QWidget* oldListWidget = this->ui->testLayout->itemAt(0)->widget();
    this->ui->testLayout->removeWidget(oldListWidget);
    delete (QListWidget*)oldListWidget;
    this->ui->testLayout->addWidget(newList);
}

void MainWindow::fixTestInput(){
    if (currTest == nullptr)
        return;
    currTestInput = currTest->getTestData();
    currTest->setUnactiveAll(true);
}


#include <QMap>
void MainWindow::on_startTestButton_clicked() {
    QString name = this->ui->datasetComboBox->currentText();
    QMap<QString, QString> params;
    bool isRandomized = this->ui->checkBoxRandomized->isChecked();
    params.insert("isRandomized", QString::number(isRandomized));
    int diffLevel = this->ui->difficultyComboBox->currentIndex();
    params.insert("difficultyLevel", QString::number(diffLevel+1));
    bool isAll = this->ui->isAllAmountCheckBox->isChecked();
    params.insert("isAllAmount", QString::number(isAll));
    int linesAmount = this->ui->LinesAmountSpinBox->value();
    params.insert("linesAmount", QString::number(linesAmount));
    emit requestNewTest(std::move(name), std::move(params));
}

#include "ui/testsummarydialog.h"
void MainWindow::on_endTestButton_clicked() {
    this->ui->endTestButton->setDisabled(true);
    this->ui->startTestButton->setDisabled(false);
    fixTestInput();
    emit requestTestSummary(currTestInput);
    isFilled = -1;
}


#include "./ui/testsummarydialog.h"
void MainWindow::on_showTestResultDialog_triggered() {
    auto dialog = new TestSummaryDialog();
    dialog->setWindowTitle("Итог теста");
    dialog->show();
    auto result = dialog->exec();
}

void MainWindow::on_showDatasetAction_triggered() {  } // old slot
void MainWindow::on_requestDatasetUpdateAction_triggered() {
    emit requestDatasetsList();
}

void MainWindow::setDatasetList(QStringList data){
    this->ui->datasetComboBox->clear();
    this->ui->datasetComboBox->addItems(data);
}

#include <QInputDialog>
void MainWindow::on_showDatasetContentAction_triggered() {
    QStringList items;
    for (int index = 0; index < ui->datasetComboBox->count(); index++)
        items << ui->datasetComboBox->itemText(index);
    QString title("Перед тем, как начать..."), label("Выберите датасет, который хотите увидеть:");
    QString result = QInputDialog::getItem(this, title, label, items, 0, false);
    emit requestDatasetContentStr(result);
}


#include <QMessageBox>
void MainWindow::getDatasetContentStr(QString str){
    QString title("Получено содержимое датасета");
    QMessageBox::information(this, title, str);
}

#include "ui/testlistwidget.h"
void MainWindow::getNewTest(QList<QStringList> testRows){
    // init test
    auto testList = new TestListWidget(this->ui->testLayout->widget());
    for (int i = 0; i < testRows.count(); i++)
        testList->addTestRow(i+1, testRows[i]);
    this->currTest = testList;
    // other
    this->replaceTestList(currTest);
    this->ui->startTestButton->setEnabled(false);
    this->ui->endTestButton->setEnabled(true);
}

#include <QtMath>
#include "ui/testsummarydialog.h"
void MainWindow::getTestSummary(int all, int done, bool isPassed){
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

void MainWindow::getTestResult(QList<QList<bool>> marks){
    isFilled++;
    if (currTest != nullptr)
        currTest->setTestMarks(marks);
    if (isFilled == true)
        this->ui->startTestButton->setDisabled(false);
}

void MainWindow::getTestAnswers(QList<QStringList> answers){
    isFilled++;
    if (currTest != nullptr)
        currTest->setAnswers(answers);
    if (isFilled == true)
        this->ui->startTestButton->setDisabled(false);
}
