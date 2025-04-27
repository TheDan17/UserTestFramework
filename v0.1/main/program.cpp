#include "program.h"

#include <QDebug>

#include <QStyleFactory>
int Program::init(){
    app.setStyle(QStyleFactory::create("Fusion"));

    this->model = new Model();
    this->controller = new Controller(model);
    this->view = new View();

    // datasetsList
    QObject::connect(view, &View::requestDatasetsList, model, &Model::responseDatasetsList);
    QObject::connect(model, &Model::sendDatasetsList, controller, &Controller::getDatasetsList);
    QObject::connect(controller, &Controller::sendDatasetsList, view, &View::getDatasetsList);
    // datasetStr
    QObject::connect(view->w, &MainWindow::requestDatasetContentStr, controller, &Controller::responseDatasetContentStr);
    QObject::connect(controller, &Controller::requestDatasetContentStr, model, &Model::responseDatasetContentStr);
    QObject::connect(model, &Model::sendDatasetContentStr, controller, &Controller::getDatasetContentStr);
    QObject::connect(controller, &Controller::sendDatasetContentStr, view->w, &MainWindow::getDatasetContentStr);
    // newTest
    QObject::connect(view->w, &MainWindow::requestNewTest, controller, &Controller::responseNewTest);
    QObject::connect(controller, &Controller::requestNewTest, model, &Model::responseNewTest);
    QObject::connect(model, &Model::sendTest, controller, &Controller::getTest);
    QObject::connect(controller, &Controller::sendTest, view->w, &MainWindow::getNewTest);
    // testSummary
    QObject::connect(view->w, &MainWindow::requestTestSummary, controller, &Controller::responseTestSummary);
    QObject::connect(controller, &Controller::requestTestSummary, model, &Model::responseTestSummary);
    QObject::connect(model, &Model::sendTestSummary, view->w, &MainWindow::getTestSummary);
    // testResult
    QObject::connect(view->w, &MainWindow::requestTestResult, controller, &Controller::responseTestResult);
    QObject::connect(controller, &Controller::requestTestResult, model, &Model::responseTestResult);
    QObject::connect(model, &Model::sendTestResult, controller, &Controller::getTestResult);
    QObject::connect(controller, &Controller::sendTestResult, view->w, &MainWindow::getTestResult);
    // testAnswers
    QObject::connect(view->w, &MainWindow::requestTestAnswers, model, &Model::responseTestAnswers);
    QObject::connect(model, &Model::sendTestAnswers, controller, &Controller::getTestAnswers);
    QObject::connect(controller, &Controller::sendTestAnswers, view->w, &MainWindow::getTestAnswers);

    view->requestUpdate();

    qInfo() << "after QObject::connect";
    return 0;
}
Program::~Program(){
    delete model;
    delete controller;
    delete view;
}
