#ifndef TESTLISTWIDGET_H
#define TESTLISTWIDGET_H

#include <QListWidget>
#include <QObject>
#include <QWidget>
#include <QList>

#include "testrowwidget.h"

class TestListWidget : public QListWidget {
    Q_OBJECT
public:
    TestListWidget(QWidget* parent = nullptr);
    void addTestRow(TestRowWidget* row);
    void addTestRow(int num, QStringList words);

    QList<QStringList> getTestData();
    void setUnactiveAll(bool isUnactive);
    void setTestMarks(QList<QList<bool>> marks);
    void setAnswers(QList<QStringList>);
};

#endif // TESTLISTWIDGET_H
