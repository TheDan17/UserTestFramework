#ifndef TESTSUMMARYDIALOG_H
#define TESTSUMMARYDIALOG_H

#include <QDialog>

namespace Ui { class TestSummaryDialog; }

class TestSummaryDialog : public QDialog {
    Q_OBJECT
private:
    Ui::TestSummaryDialog *ui;
public:
    explicit TestSummaryDialog(QWidget *parent = nullptr);
    ~TestSummaryDialog();

    void setSummaryMark(int all, int done);
    void setSummaryPercentage(int perc);
    void setSummaryPassed(bool isPassed);
};

#endif // TESTSUMMARYDIALOG_H
