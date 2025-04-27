#include "testsummarydialog.h"
#include "ui_testsummarydialog.h"

TestSummaryDialog::TestSummaryDialog(QWidget *parent) : QDialog(parent), ui(new Ui::TestSummaryDialog) {
    ui->setupUi(this);
    QObject::connect(ui->closeTestButton, &QPushButton::clicked, this, &QDialog::reject);
    QObject::connect(ui->seeResultButton, &QPushButton::clicked, this, &QDialog::accept);
}
TestSummaryDialog::~TestSummaryDialog() {
    delete ui;
}

void TestSummaryDialog::setSummaryMark(int all, int done){
    this->ui->pointAllLabel->setText(QString::number(all));
    this->ui->pointsDoneLabel->setText(QString::number(done));
}
void TestSummaryDialog::setSummaryPercentage(int perc){
    this->ui->resultPercentLabel->setText("("+QString::number(perc)+"%)");
}
void TestSummaryDialog::setSummaryPassed(bool isPassed){
    if (isPassed) {
        this->ui->pointsDoneLabel->setStyleSheet("color: green;");
        this->ui->resultLabel->setText("Пройдено");
    } else {
        this->ui->pointsDoneLabel->setStyleSheet("color: red;");
        this->ui->resultLabel->setText("НЕ пройдено");
    }
}
