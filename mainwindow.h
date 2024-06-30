#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QLabel>
#include <QComboBox>

#include <QFileDialog>
#include <QFile>

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
    //void convertAngle();
    ~MainWindow();
    QString convert(qreal,int,int);
    int typeStringToInt(QString&);
private slots:
    void on_convertButton_clicked();
    void on_directionBox_clicked(bool checked);

    void on_openAction_triggered();

    void on_saveHowAction_triggered();

    void on_typeBox_1_currentTextChanged(const QString &arg1);

    void on_typeBox_2_currentTextChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    QTextEdit* input;
    QTextEdit* output;
    QComboBox* type1;
    QComboBox* type2;
    QString way;

};
#endif // MAINWINDOW_H
