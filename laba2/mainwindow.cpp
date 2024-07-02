#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<fstream>
#include<vector>
#include<string>
#include<algorithm>
#include<QTableWidgetItem>
#include<QStringListModel>
#include<QObject>
#include<QPixmap>
#include<QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tableWidget, &QTableView::customContextMenuRequested, [&](const QPoint& pos) {
        static QMenu* menu = nullptr;

        if (!menu) {
            menu = new QMenu();
            menu->addAction(new QAction("1", this));
            menu->addAction(new QAction("2", this));
            menu->addAction(new QAction("3", this));
        }
        menu->popup( mapToGlobal(pos) );
    });
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
            QStandardItemModel* model = new QStandardItemModel(this);
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
                model->appendRow(new QStandardItem(line));
                ui->listWidget->addItem(line);
            }
            this->ui->listView->setModel(model);
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
            QStandardItemModel* model = new QStandardItemModel(this);
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
                model->appendRow(new QStandardItem(line));
                ++row;
                ui->listWidget->addItem(line);
            }
            this->ui->listView->setModel(model);
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

void MainWindow::binaryInsertionSort() {
      QString file_name = this->current_file;
    QFile file(file_name);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Не удалось открыть файл для чтения";
        return;
    }
    QStandardItemModel* model = new QStandardItemModel(this);
    QTextStream in(&file);
    while (!in.atEnd()) {
        //this->current_num++;
        QString line = in.readLine();
        QStringList parts = line.split(" "); // Предполагаем, что данные разделены пробелом
        int columnCount = parts.size();
        int row=0;
        // Добавляем новую строку в таблицу
        ui->tableWidget->insertRow(row);

       for (int col = 0; col < columnCount; ++col) {
            // Записываем данные в ячейку таблицы
          ui->tableWidget->setItem(row,col, new QTableWidgetItem(parts.at(col)));
        }

        ++row;
}

    QTableWidget *tableWidget_ = this->ui->tableWidget;
   int rowCount = tableWidget_->rowCount();

    // Сортировка по первому столбцу
    for (int i = 1; i < rowCount; ++i) {
        QTableWidgetItem *key = tableWidget_->item(i, 0);

        // Бинарный поиск
        int left = 0;
        int right = i - 1;
        while (left <= right) {
            int mid = (left + right) / 2;
            QTableWidgetItem *midItem = tableWidget_->item(mid, 0);
            if (midItem->text().compare(key->text()) < 0) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        // Перемещение элементов в первом столбце
        for (int j = i; j > right + 1; --j) {
            tableWidget_->setItem(j, 0, tableWidget_->item(j - 1, 0));
        }

        // Вставка элемента в правильное положение
        tableWidget_->setItem(right + 1, 0, key);

        // Перемещение элементов в остальных столбцах (если нужно)
        for (int col = 1; col < tableWidget_->columnCount(); ++col) {
            // Сохранение данных из текущей строки
            QTableWidgetItem *tempItem = tableWidget_->item(i, col);
            // Перемещение данных из строки right + 1 в строку i
            tableWidget_->setItem(i, col, tableWidget_->item(right + 1, col));
            // Вставка сохраненных данных в строку right + 1
            tableWidget_->setItem(right + 1, col, tempItem);
        }
    }

}

void MainWindow::on_pushButton_2_clicked()
{
    this->binaryInsertionSort();
    this->ui->listWidget->sortItems();
}


void MainWindow::on_pushButton_4_clicked()
{
    QString file_name = this->current_file;

        QFile file(file_name);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "Не удалось открыть файл для чтения";
            return;
        }
        QStandardItemModel* model = new QStandardItemModel(this);
      QTextStream in(&file);
         while (!in.atEnd()) {
    QString line = in.readLine();

     model->appendRow(new QStandardItem(line));
     model->sort(0, Qt::DescendingOrder);
         }
      this->ui->listView->setModel(model);
         file.close();

}

void MainWindow::ReadFile1()
{

    QFile file(current_file);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {

        qDebug() << "Error opening file:" << file.errorString();
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        qDebug() << line;
    }

    file.close();
}
void MainWindow::on_pushButton_5_clicked()
{
    QString file_name = QFileDialog::getOpenFileName(0,"Open dialog","","*.jpg");
    this->current_file = file_name;
    this->ReadFile1();

    QPixmap pixmap1(":/img/img/mashina-1193x671px.jpg");
    QPixmap pixmap2(":/img/img/mashina-1200x675px.jpg");
    QPixmap pixmap3(":/img/img/mashina-1440x900px.jpg");

    // Изменяем размеры изображений
    int labelWidth = ui->label1->width();
    int labelHeight = ui->label1->height();
    pixmap1 = pixmap1.scaled(labelWidth, labelHeight, Qt::KeepAspectRatio);
    pixmap2 = pixmap2.scaled(labelWidth, labelHeight, Qt::KeepAspectRatio);
    pixmap3 = pixmap3.scaled(labelWidth, labelHeight, Qt::KeepAspectRatio);

    ui->label1->setPixmap(pixmap1);
    ui->label2->setPixmap(pixmap2);
    ui->label3->setPixmap(pixmap3);
}

