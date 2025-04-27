#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
                                          ui(new Ui::MainWindow) {
    ui->setupUi(this);
}
MainWindow::~MainWindow() { delete ui; }


#include <QMap>
QMap<QString, QString> MainWindow::getParams(bool isFlow) {
    QMap<QString, QString> params;
    int diffLevel = this->ui->difficultyComboBox->currentIndex();
    params.insert("difficultyLevel", QString::number(diffLevel+1));
    params.insert("isRandomized", QString::number(true)); // bool isRandomized = this->ui->checkBoxRandomized->isChecked();
    params.insert("isAllAmount", QString::number(true)); // bool isAll = this->ui->isAllAmountCheckBox->isChecked();
    params.insert("linesAmount", QString::number(-1)); // int linesAmount = this->ui->LinesAmountSpinBox->value();
    params.insert("isFlow", QString::number(isFlow));
    return std::move(params);
}

void MainWindow::on_startFlowButton_clicked() {
    QString name = this->ui->datasetComboBox->currentText();
    auto params = getParams(true);
    emit requestStartFlowTest(name, params);
}
void MainWindow::on_startTestButton_clicked() {
    QString name = this->ui->datasetComboBox->currentText();
    auto params = getParams(false);
    emit requestStartQuizTest(name, params);
}


void MainWindow::setDatasetList(QStringList data){
    this->ui->datasetComboBox->clear();
    this->ui->datasetComboBox->addItems(data);
}


// DEBUG MENU ACTIONS
void MainWindow::on_showDatasetAction_triggered() {  } // old slot
void MainWindow::on_requestDatasetUpdateAction_triggered() {
    emit requestDatasetsList();
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

#include "./ui/testsummarydialog.h"
void MainWindow::on_showTestResultDialog_triggered() {
    auto dialog = new TestSummaryDialog();
    dialog->setWindowTitle("Итог теста");
    dialog->show();
    dialog->exec();
}
