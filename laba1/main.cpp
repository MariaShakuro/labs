#include "mainwindow.h"
#include <QApplication>
#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QFormLayout>
#include <QDoubleValidator>
#include <QComboBox>
#include <QDebug>


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow w;
    w.show();
    return app.exec();
}
