#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<fstream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_tableWidget_cellActivated(WidgetA&widgetA, QTableWidget*tableWidget)
{
    QString fileName = QFileDialog::getOpenFileName(0,"Open dialog","","*.txt");
    if (fileName.isEmpty())
        return;

    std::ifstream file(fileName.toStdString());
    if (!file.is_open()) {
        QMessageBox::warning(nullptr, "Error", "Failed to open file.");
        return;
    }

    widgetA.GetW().clear();
    widgetA.ReadW(file);
    tableWidget->setRowCount(static_cast<int>(widgetA.GetW().size()));
    int row = 0;
    for (const auto& item : widgetA.GetW()) {
        tableWidget->setItem(row, 0, new QTableWidgetItem(item.model));
        tableWidget->setItem(row, 1, new QTableWidgetItem(item.speed));
        tableWidget->setItem(row, 2, new QTableWidgetItem(item.price));
        row++;
    }
}
/*void MainWindow::on_openAction_triggered()
{

    QString file_name = QFileDialog::getOpenFileName(0,"Open dialog","","*.txt");
    //QFile file(file_name);
    if(!file_name.isEmpty()){
        QFile file(file_name);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "Не удалось открыть файл для чтения";
            return;
        }
        QTextStream in(&file);
        if(!in.atEnd()){
            QString tempQString = in.readLine();
            type1->setCurrentIndex(typeStringToInt(tempQString));
        }
        if(!in.atEnd()){
            QString tempQString = in.readLine();
            type2->setCurrentIndex(typeStringToInt(tempQString));
        }

       // QString input_ = "";
        QString output_ = "";

        while(!in.atEnd()){
            QString tempQString = in.readLine();
            std::istringstream inStr(tempQString.toStdString());
            qreal temp;
            while (inStr >> temp){
               // input_ = input_ + QString::number(temp) + "\n";
                output_ = output_ + convert(temp,type1->currentIndex(),type2->currentIndex()) + "\n";
            }
        }
        input->setText(input_);
        output->setText(output_);
    }
}


void MainWindow::on_saveHowAction_triggered()
{
    QString file_name = QFileDialog::getSaveFileName(0,"Open dialog","","*.txt");
    QFile file(file_name);
    if(file.open(QIODevice::WriteOnly|QIODevice::Truncate)){
        QTextStream out(&file);
        out << type1->currentText() << "\n" << type2->currentText() << "\n" << input->toPlainText();
        file.close();
    }
    return;
}*/




void MainWindow::on_openAction_triggered()
{
    QString file_name = QFileDialog::getOpenFileName(0,"Open dialog","","*.txt");
    //QFile file(file_name);
    if(!file_name.isEmpty())
    {
        QFile file(file_name);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "Не удалось открыть файл для чтения";
            return;
        }
        return;
    }
}


void MainWindow::on_saveHowAction_triggered()
{
    QString file_name = QFileDialog::getSaveFileName(0,"Open dialog","","*.txt");
    QFile file(file_name);
    if(file.open(QIODevice::WriteOnly|QIODevice::Truncate)){
        QTextStream out(&file);
        //out << type1->currentText() << "\n" << type2->currentText() << "\n" << input->toPlainText();
       file.close();
    }
    return;
}

