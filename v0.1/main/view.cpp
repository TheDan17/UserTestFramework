#include "view.h"

View::View() {
    this->w = new MainWindow;
    w->setWindowTitle("TestingWords v0.1");
    w->setWindowIcon(QIcon("TestingWords.ico"));
    w->show();
    QObject::connect(w, &MainWindow::requestDatasetsList,
                     this, &View::responseDatasetsList);
}

#include <QMessageBox>
void View::getDatasetsList(QStringList array){
    w->setDatasetList(array);
    /*
    QString titleStr("Получен список датасетов"), buttonStr("Okay, I guess");
    QString msgStr("Всего датасетов: " + QString::number(array.size()) + "\n");
    for (int i = 0; i < array.size(); i++)
        msgStr += (QString::number(i+1) + ": " + array[0] + "\n");
    QMessageBox::information(nullptr, titleStr, msgStr, buttonStr);
    */
}
