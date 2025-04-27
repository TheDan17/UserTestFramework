#include "testlistwidget.h"

#include <QSizePolicy>

TestListWidget::TestListWidget(QWidget* parent) : QListWidget(parent){
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void TestListWidget::addTestRow(TestRowWidget* row){
    auto item = new QListWidgetItem(this);
    item->setSizeHint(row->sizeHint());
    row->setParent(this);
    this->addItem(item);
    this->setItemWidget(item, row);
}

void TestListWidget::addTestRow(int num, QStringList words){
    auto row = new TestRowWidget(num, this);
    row->initTestLine(words);
    this->addTestRow(row);
}

QList<QStringList> TestListWidget::getTestData(){
    QList<QStringList> result;
    for (int i = 0; i < this->count(); i++){
        auto* row = static_cast<TestRowWidget*>(this->itemWidget(this->item(i)));
        if (row)
            result.append(row->getTestInput());
    }
    return std::move(result);
}

void TestListWidget::setUnactiveAll(bool isUnactive){
    for (int i = 0; i < this->count(); i++){
        auto* row = static_cast<TestRowWidget*>(this->itemWidget(this->item(i)));
        if (row)
            row->setUnactiveAll(isUnactive);
    }
}

void TestListWidget::setTestMarks(QList<QList<bool>> marks){
    for (int i = 0; i < this->count(); i++){
        auto* row = static_cast<TestRowWidget*>(this->itemWidget(this->item(i)));
        if (row)
            row->setMarks(marks[i]);
    }
}

void TestListWidget::setAnswers(QList<QStringList> answers){
    for (int i = 0; i < this->count(); i++){
        auto* row = static_cast<TestRowWidget*>(this->itemWidget(this->item(i)));
        if (row)
            row->setAnswers(answers[i]);
    }
}
