#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

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


void MainWindow::on_pushButton_clicked()
{
    std::string access_keyid = ui->lineEdit->text().toStdString();
    std::string access_keysecret = ui->lineEdit_2->text().toStdString();
    std::string endpointname = ui->lineEdit_3->text().toStdString();
    std::string bucketname = ui->lineEdit_4->text().toStdString();

    cloud_ptr = std::make_shared<CloudData>(access_keyid, access_keysecret, endpointname, bucketname);

    std::string path = "\\";
    std::vector<file_detail_st> file_details_vec;
    if (cloud_ptr->query_directory(path, file_details_vec))
    {
        QMessageBox::information(this, tr("Aliyun Connect status"),
                                         tr("Connect to Aliyun success .\n"),
                                         QMessageBox::Ok,
                                         QMessageBox::Ok);
    } else {
        QMessageBox::warning(this, tr("Aliyun Connect status"),
                                         tr("Connect to Aliyun failed!\n"),
                                         QMessageBox::Ok,
                                         QMessageBox::Ok);
    }
}
