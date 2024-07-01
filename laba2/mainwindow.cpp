#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<fstream>
#include<vector>
#include<algorithm>
#include<QTableWidgetItem>
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

void MainWindow::ReadFile()
{
    int index;
    if(this->ui->textEdit_3->toPlainText() == ""){
        index = this->ammount_in_file;
    }
    else{
        index = this->ui->textEdit_3->toPlainText().toInt();
    }

    if(index <= -1){
        QString file_name = this->current_file;
        if(!file_name.isEmpty())
        {
            QFile file(file_name);
            if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                qDebug() << "Не удалось открыть файл для чтения";
                return;
            }

            QTextStream in(&file);
            ui->tableWidget->clearContents();
            ui->tableWidget->setRowCount(0);
            ui->listWidget->clear();
            int row=0;
            //this->current_num = 1;
            while (!in.atEnd()) {
                //this->current_num++;
                QString line = in.readLine();
                QStringList parts = line.split(" "); // Предполагаем, что данные разделены пробелом
                int columnCount = parts.size();

                // Добавляем новую строку в таблицу
                ui->tableWidget->insertRow(row);
                for (int col = 0; col < columnCount; ++col) {
                    // Записываем данные в ячейку таблицы
                    ui->tableWidget->setItem(row,col, new QTableWidgetItem(parts.at(col)));
                }

                ++row;
                ui->listWidget->addItem(line);
            }
            file.close();
        }
    }
    else{
        QString file_name = this->current_file;
        if(!file_name.isEmpty())
        {
            QFile file(file_name);
            if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                qDebug() << "Не удалось открыть файл для чтения";
                return;
            }

            QTextStream in(&file);
            ui->tableWidget->clearContents();
            ui->tableWidget->setRowCount(0);
            ui->listWidget->clear();
            int row=0;
            int i = 1;
            //this->current_num = 1;
            while (!in.atEnd() and i <= index) {
                //this->current_num++;
                QString line = in.readLine();
                i++;
                QStringList parts = line.split(" "); // Предполагаем, что данные разделены пробелом
                int columnCount = parts.size();

                // Добавляем новую строку в таблицу
                ui->tableWidget->insertRow(row);
                for (int col = 0; col < columnCount; ++col) {
                    // Записываем данные в ячейку таблицы
                    ui->tableWidget->setItem(row,col, new QTableWidgetItem(parts.at(col)));
                }

                ++row;
                ui->listWidget->addItem(line);
            }
            file.close();
        }
    }

}

void MainWindow::AmountInFile()
{
    QString file_name = this->current_file;
    if(!file_name.isEmpty())
    {
        QFile file(file_name);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "Не удалось открыть файл для чтения";
            return;
        }

        this->ammount_in_file = 0;
        QTextStream in(&file);
        while (!in.atEnd()) {
            this->ammount_in_file++;
        }
        file.close();
    }
}

void MainWindow::on_openAction_triggered()
{
    QString file_name = QFileDialog::getOpenFileName(0,"Open dialog","","*.txt");
    this->current_file = file_name;
    this->ReadFile();
}


void MainWindow::on_saveHowAction_triggered()
{
    QString file_name = QFileDialog::getSaveFileName(0,"Open dialog","","*.txt");
    QFile file(file_name);
    if(file.open(QIODevice::WriteOnly|QIODevice::Truncate)){
        QTextStream out(&file);
        for(int row = 0; row < ui->tableWidget->rowCount(); ++row) {
            for(int column = 0; column < ui->tableWidget->columnCount(); ++column) {
                out << ui->tableWidget->item(row, column)->text() << "\n";
            }
        }
        file.close();
    }
    QString listFileName = QFileDialog::getSaveFileName(0, "Сохранить данные из списка", "", "*.txt");
    QFile listFile(listFileName);
    if(listFile.open(QIODevice::WriteOnly | QIODevice::Truncate)){
        QTextStream listOut(&listFile);
        for(int i = 0; i < ui->listWidget->count(); ++i){
            listOut << ui->listWidget->item(i)->text() << "\n";
        }
        listFile.close();
    }
}



void MainWindow::on_textEdit_3_textChanged()
{
    if (this->current_file != "") {
        QString inputText = this->ui->textEdit_3->toPlainText().trimmed(); // Убираем пробелы в начале и конце строки
        bool ok;
        int value = inputText.toInt(&ok);

        if (ok) {
            if (value > 8 || value < 0) {
                // Создаем исключительную ситуацию
                QMessageBox::critical(this, "Ошибка", "Число должно быть от 0 до 8.");
            } else {
                this->ReadFile();
            }
        } else {
            return;
        }
    }

}



void MainWindow::on_pushButton_clicked()
{
    if (this->current_file != "") {
        if (this->ui->textEdit_3->toPlainText() != "") {
            int newValue = this->ui->textEdit_3->toPlainText().toInt() + 1;
            if (newValue > 8 || newValue < 0) {
                // Показываем QMessageBox с сообщением об ошибке
                QMessageBox::critical(this, "Ошибка", "Число должно быть от 0 до 8.");
            } else {
                this->ui->textEdit_3->setPlainText(QString::number(newValue));
            }
        }
    }

}


void MainWindow::on_pushButton_3_clicked()
{
    if (this->current_file != "") {
        if (this->ui->textEdit_3->toPlainText() != "") {
            int newValue = this->ui->textEdit_3->toPlainText().toInt() - 1;
            if (newValue > 8 || newValue < 0) {
                // Показываем QMessageBox с сообщением об ошибке
                QMessageBox::critical(this, "Ошибка", "Число должно быть от 0 до 8.");
            } else {
                this->ui->textEdit_3->setPlainText(QString::number(newValue));
            }
        }
    }

}


/*void MainWindow::binarySort(){
    // Получение указателя на QTableWidget (this->ui->tableWidget)
    QTableWidget* tableWidget = this->ui->tableWidget;

    // Получение количества строк в таблице
    int rowCount = tableWidget->rowCount();

    // Создание вектора для хранения значений первого столбца
    std::vector<QTableWidgetItem*> firstColumnValues;
    for (int row = 0; row < rowCount; ++row)
    {
        QTableWidgetItem* item = tableWidget->item(row, 0);
        if (item)
        {
            firstColumnValues.push_back(item);
        }
    }
    // Сортировка вектора с помощью бинарного поиска
    std::sort(firstColumnValues.begin(), firstColumnValues.end(),[](QTableWidgetItem*& a, QTableWidgetItem*& b){
        return a->text().toDouble() < b->text().toDouble();
    });

    // Обновление QTableWidget с отсортированными значениями
    for (int row = 0; row < rowCount; ++row)
    {
        this->ui->tableWidget->setItem(row, 0, firstColumnValues[row]);
    }

}*/
void MainWindow::on_pushButton_2_clicked()
{
   // this->ui->tableWidget->binarySort();
    this->ui->listWidget->sortItems();
}

