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
    void on_openAction_triggered();
    void on_saveHowAction_triggered();

    void on_textEdit_3_textChanged();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    QString current_file;
    void ReadFile();
    void binarySort();
    quint8 current_num;
    quint8 ammount_in_file;
    void AmountInFile();
};
#endif // MAINWINDOW_H
