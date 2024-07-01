#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    input = this->ui->input_1;
    type1 = this->ui->typeBox_1;
    output = this->ui->input_2;
    type2 = this->ui->typeBox_2;
    this->ui->directionBox->setCheckState(Qt::Checked);
    way = " => ";

}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::convert(qreal item, int from, int where)
{
    qreal radian;
    switch(from) {
    case 0:
        radian = (qreal) item /3437.74677;
        break;
    case 1:
        radian = (qreal) item / 206265;
        break;
    case 2:
        radian = (qreal) item / 57.2957795;
        break;
    case 3:
        radian = (qreal) item / 63.662;
        break;
    case 4:
        radian = (qreal) item / 0.063662 ;
        break;
    case 5:
        radian = (qreal) item;
        break;
    default:
        return "Invalid unit";
    }

    switch(where) {
    case 0:
        return QString::number(radian * 3437.74677,'f',2);
    case 1:
        return QString::number(radian *206265 ,'f',2);
    case 2:
        return QString::number(radian * 57.2957795,'f',2);
    case 3:
        return QString::number(radian * 63.662,'f',2);
    case 4:
        return QString::number(radian * 0.063662,'f',2);
    case 5:
        return QString::number(radian,'f',2);
    default:
        return "Invalid unit";
    }
    return "ok";
}

void MainWindow::on_convertButton_clicked()
{
    std::istringstream inStr(input->toPlainText().toStdString());
    qreal temp;
    QString input_ = "";
    QString output_ = "";
    while (inStr >> temp){
        input_ = input_ + QString::number(temp) + "\n";
        output_ = output_ + convert(temp,type1->currentIndex(),type2->currentIndex()) + "\n";
    }
    input->setText(input_);
    output->setText(output_);
}


void MainWindow::on_directionBox_clicked(bool checked)
{
    if(this->ui->directionBox->isChecked() == true){
        input = this->ui->input_1;
        type1 = this->ui->typeBox_1;
        output = this->ui->input_2;
        type2 = this->ui->typeBox_2;
        way = " => ";
        this->ui->label->setText("КОНВЕРТАТОР: " + this->ui->typeBox_1->currentText() + way + this->ui->typeBox_2->currentText());
    }
    else{
        input = this->ui->input_2;
        type1 = this->ui->typeBox_2;
        output = this->ui->input_1;
        type2 = this->ui->typeBox_1;
        way = " <= ";
       this->ui->label->setText("КОНВЕРТАТОР: " + this->ui->typeBox_1->currentText() + way + this->ui->typeBox_2->currentText());
    }
}

int MainWindow::typeStringToInt(QString& type)
{
    if(type == "минуты"){
        return 0;
    }
    if(type == "секунды"){
        return 1;
    }
    if(type == "градусы"){
        return 2;
    }
    if(type == "грады"){
        return 3;
    }
    if(type == "тысячные"){
        return 4;
    }
    if(type == "радианы"){
        return 5;
    }
    return -1;
}


void MainWindow::on_openAction_triggered()
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

        QString input_ = "";
        QString output_ = "";

        while(!in.atEnd()){
            QString tempQString = in.readLine();
            std::istringstream inStr(tempQString.toStdString());
            qreal temp;
            while (inStr >> temp){
                input_ = input_ + QString::number(temp) + "\n";
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
}


void MainWindow::on_typeBox_1_currentTextChanged(const QString &arg1)
{
    this->ui->label->setText("КОНВЕРТАТОР: " + this->ui->typeBox_1->currentText() + way + this->ui->typeBox_2->currentText());
}


void MainWindow::on_typeBox_2_currentTextChanged(const QString &arg1)
{
    this->ui->label->setText("КОНВЕРТАТОР: " + this->ui->typeBox_1->currentText() + way + this->ui->typeBox_2->currentText());
}




void MainWindow::on_pushButton_clicked()
{    dialog=new Dialog();
    dialog->exec();
    dialog->show();
}

