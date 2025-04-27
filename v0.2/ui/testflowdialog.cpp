#include "testflowdialog.h"
#include "ui_testflowdialog.h"

TestFlowDialog::TestFlowDialog(QWidget *parent) : QDialog(parent),
                                                  ui(new Ui::TestFlowDialog),
                                                  currentStatus(NOTHING),
                                                  rightScore(0),
                                                  wrongScore(0),
                                                  allScore(0) {
    ui->setupUi(this);
    currentLayouts = {ui->layoutRussianForm, ui->layoutFirstForm, ui->layoutSecondForm, ui->layoutThirdForm};
    currentStatus = NOTHING;
    updateMetrics();
}
TestFlowDialog::~TestFlowDialog() {
    delete ui;
}

#include <QDebug>
void TestFlowDialog::keyPressEvent(QKeyEvent* keyEvent){
    //qInfo() << "keyPressEvent: " << keyEvent->key() << " / Enter = " << (int)Qt::Key_Enter << "\n";
    if (keyEvent->key() == (int)Qt::Key_Enter ||
        keyEvent->key() == (int)Qt::Key_Return)
        catchedEnterKey();
}

void TestFlowDialog::addScore(int plus, bool isRight){
    allScore += plus;
    if (isRight)
        rightScore += plus;
    else
        wrongScore += plus;
    updateMetrics();
}

#include <QtMath>
void TestFlowDialog::updateMetrics(){
    ui->rightScoreLabel->setText(QString::number(rightScore));
    ui->wrongScoreLabel->setText(QString::number(wrongScore));
    if (allScore != 0) {
        int rightPercent = qBound(0, qFloor(rightScore * 100.0 / allScore), 100);
        ui->rightPercentLabel->setText(QString::number(rightPercent) + "%");
        if (rightPercent >= 80)
            ui->summaryLabel->setText("ОГО ДА ТЫ КРУТОЙ КПЦ");
        else
            ui->summaryLabel->setText("НУ ТЫ И ЛУЗЕР ХАХАХА");
    } else {
        ui->rightPercentLabel->setText("-%");
        ui->summaryLabel->setText("НИЧЕГО НЕ ПОНЯТНО");
    }
}

#include <QLineEdit>
#include <QLabel>
void TestFlowDialog::captureTestInput(){
    QList<QStringList> list;
    QStringList strlist;
    for (auto& pair : currentElems) {
        if (pair.second == FLABEL)
            strlist.append(static_cast<QLabel*>(pair.first)->text());
        else
            strlist.append(static_cast<QLineEdit*>(pair.first)->text());
    }
    list.append(std::move(strlist));
    this->capturedInput = std::move(list);
}

void TestFlowDialog::catchedEnterKey(){
    switch(currentStatus){
    case NOTHING:
        captureTestInput();
        emit requestTestResult(capturedInput);
        break;
    case CHECKED_RIGHT:
        emit requestNextTest();
        break;
    case CHECKED_WRONG:
        emit requestSameTest();
        break;
    case END:
        this->accept();
    }
}

void TestFlowDialog::clearTestElems(){
    for (auto& layout : currentLayouts){
        for (int i = 0; i < layout->count(); i++){
            QLayoutItem* item = layout->takeAt(0);
            QWidget* widget = item->widget();
            if (widget)
                delete widget;
            layout->removeItem(item);
            delete item;
        }
    }
    int all = currentElems.size();
    for (int i = 0; i < all; i++)
        currentElems.erase(currentElems.begin());
}


void TestFlowDialog::makeStarting(){
    ui->checkAnswerLabel->setText("Нажмите Enter, чтобы проверить");
    ui->checkAnswerLabel->setStyleSheet("color: black;");
    ui->continueLabel->setText("Нажмите Enter, чтобы продолжить");
    ui->continueLabel->setStyleSheet("color: gray;");
    currentStatus = NOTHING;
}
void TestFlowDialog::makeRightChecked(){
    ui->checkAnswerLabel->setText("Проверено: правильно");
    ui->checkAnswerLabel->setStyleSheet("color: green;");
    ui->continueLabel->setStyleSheet("color: black;");
    currentStatus = CHECKED_RIGHT;
}
void TestFlowDialog::makeWrongChecked(){
    ui->checkAnswerLabel->setText("Проверено: неправильно");
    ui->checkAnswerLabel->setStyleSheet("color: red;");
    ui->continueLabel->setStyleSheet("color: black;");
    currentStatus = CHECKED_WRONG;
}
void TestFlowDialog::makeFinished(){
    ui->checkAnswerLabel->setText("Нажмите Enter, чтобы закрыть обучение");
    ui->checkAnswerLabel->setStyleSheet("color: black;");
    ui->continueLabel->setText("Нажмите Enter, чтобы закрыть обучение");
    ui->continueLabel->setStyleSheet("color: black;");
    ui->summaryLabel->setText("ОБУЧЕНИЕ ЗАКОНЧЕНО");
    currentStatus = END;
}


void TestFlowDialog::makeTestReq(QPair<QString, QMap<QString, QString>> testReq){
    rightScore = 0;
    wrongScore = 0;
    allScore = 0;
    updateMetrics();
    auto requestDSName = std::move(testReq.first);
    auto requestDSParams = std::move(testReq.second);
    this->currentStatus = WAITING;
    emit requestNewTestLot(requestDSName, requestDSParams);
}


void TestFlowDialog::getTest(QList<QStringList> data) {
    if (currentStatus == END)
        return;
    if (data.empty()) {
        makeFinished();
        return;
    } else {
        makeStarting();
    }
    clearTestElems();
    QStringList testData = data[0];
    QWidget* elem;
    for(int i = 0; i < testData.size(); i++){
        auto& str = testData[i];
        if (str.isEmpty()) {
            elem = new QLineEdit(this);
            currentElems.append({elem, FLINE_EDIT});
        } else {
            elem = new QLabel(str, this);
            currentElems.append({elem, FLABEL});
        }
        currentLayouts[i]->addWidget(elem);
    }
}

void TestFlowDialog::getTestResult(QList<QList<bool>> marks){
    if (currentStatus == END)
        return;
    QList<bool> testMarks = marks[0];
    QLineEdit* buff;
    bool isRight = true;
    for(int i = 0; i < testMarks.size(); i++){
        auto& pair = currentElems[i];
        if (pair.second == FLINE_EDIT) {
            buff = static_cast<QLineEdit*>(pair.first);
            if (testMarks[i] == true) {
                buff->setStyleSheet("background-color: green; color: black;");
            } else {
                isRight = false;
                buff->setStyleSheet("background-color: red; color: black;");
            }
        }
    }
    if (isRight) {
        addScore(1, true);
        makeRightChecked();
    } else {
        addScore(1, false);
        makeWrongChecked();
    }
}

void TestFlowDialog::getTestAnswers(QList<QStringList> answers){
    if (currentStatus == END)
        return;
    QStringList testAnswers = answers[0];
    for(int i = 0; i < testAnswers.size(); i++){
        auto& pair = currentElems[i];
        if (pair.second == FLINE_EDIT)
            static_cast<QLineEdit*>(pair.first)->setText(testAnswers[i]);
    }
}
