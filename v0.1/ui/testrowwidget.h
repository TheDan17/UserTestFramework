#ifndef TESTROWWIDGET_H
#define TESTROWWIDGET_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QLayout>
#include <QVector>
#include <QPair>

#include <QDebug>

enum type { LINE_EDIT, LABEL };

const int testElemWidth = 90;

class TestRowWidget : public QWidget {
    Q_OBJECT
private:
    int rowNumber;
    QHBoxLayout* head;
    QLabel* number;
    QList<QPair<QWidget*, enum type>> words;
public:
    explicit TestRowWidget(int rowNumber, QWidget *parent = nullptr) : QWidget(parent), rowNumber(rowNumber) {}
    void initTestLine(QStringList data){
        const QStringList captions = {"русский", "1 форма", "2 форма", "3 форма"};
        this->head = new QHBoxLayout(this);
        this->number = new QLabel(QString::number(rowNumber), this);
        for (int i = 0; i < 4; i++){
            auto vline = new QFrame(this);
            vline->setFrameShape(QFrame::VLine);
            auto group = new QVBoxLayout();
            auto caption = new QLabel("**" + captions[i] + "**", this);
            caption->setTextFormat(Qt::MarkdownText);
            caption->setAlignment(Qt::AlignHCenter);
            caption->setFixedWidth(testElemWidth);
            QWidget* elem;
            QString dataStr = data[i];
            if (dataStr.isEmpty()) {
                elem = new QLineEdit(this);
                words.append({elem, LINE_EDIT});
            } else {
                elem = new QLabel(data[i], this);
                words.append({elem, LABEL});
            }
            elem->setFixedWidth(testElemWidth);
            group->addWidget(caption);
            group->addWidget(elem);
            head->addWidget(vline);
            head->addLayout(group);
        }
    }
    QStringList getTestInput(){
        auto list = QStringList();
        for (auto& word : words){
            QLabel* label; QLineEdit* lineEdit;
            switch (word.second){
                case LABEL:
                    label = (QLabel*)word.first;
                    list.append(label->text());
                    break;
                case LINE_EDIT:
                    lineEdit = (QLineEdit*)word.first;
                    list.append(lineEdit->text().trimmed());
                    break;
            }
        }
        return std::move(list);
    }
    void markTestWords(QList<bool> data){
        for (int i = 0; i < 4; i++){
            if (words[i].second == LINE_EDIT){
                if (data[i] == true)
                    ((QLineEdit*)words[i].second)->setStyleSheet("background-color: rgb(255, 145, 145);");
                else
                    ((QLineEdit*)words[i].second)->setStyleSheet("background-color: rgb(145, 255, 145);");
            }
        }
    }

    void setUnactiveAll(bool isUnactive){
        QLineEdit* buff;
        for (auto& elem : words){
            if (elem.second == LINE_EDIT){
                buff = static_cast<QLineEdit*>(elem.first);
                buff->setDisabled(isUnactive);
            }
        }
    }

    void setMarks(QList<bool> marks){
        QLineEdit* buff;
        for (int i = 0; i < words.size(); i++) {
            auto& elem = words[i];
            if (elem.second == LINE_EDIT){
                buff = static_cast<QLineEdit*>(elem.first);
                if (marks[i] == true)
                    buff->setStyleSheet("background-color: rgb(255, 140, 140); color: rgb(0, 0, 0);");
                else
                    buff->setStyleSheet("background-color: rgb(140, 255, 140); color: rgb(0, 0, 0);");
            }
        }
    }

    void setAnswers(QStringList answers){
        QLineEdit* buff;
        for (int i = 0; i < words.size(); i++) {
            auto& elem = words.at(i);
            if (elem.second == LINE_EDIT){
                buff = static_cast<QLineEdit*>(elem.first);
                buff->setText(answers[i]);
            }
        }
    }

};

#endif // TESTROWWIDGET_H
