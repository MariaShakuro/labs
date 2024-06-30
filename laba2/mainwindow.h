#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QLabel>
#include <QComboBox>
#include <QMessageBox>
#include <QTableWidget>
#include <QFileDialog>
#include <QFile>
#include "widget.h"
#include <iostream>
#include <sstream>
//#include <QTextWidget>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_tableWidget_cellActivated(WidgetA&widgetA,QTableWidget*tableWidget);
   // void on_openAction_triggered();
   // void on_saveHowAction_triggered();
    void on_openAction_triggered();

    void on_saveHowAction_triggered();

private:
    Ui::MainWindow *ui;

   WidgetA widgetA;
};
#endif // MAINWINDOW_H
