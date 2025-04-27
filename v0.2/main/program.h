#ifndef PROGRAM_H
#define PROGRAM_H

#include <QApplication>

#include "model.h"
#include "controller.h"
#include "view.h"

class Program {
private:
    QApplication app;
    Model* model;
    Controller* controller;
    View* view;
    int init();
public:
    Program(int argc, char** argv) : app(argc, argv) { init(); }
    ~Program();
    int run(){ return app.exec(); }
};

#endif // PROGRAM_H
