#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QTimer>
#include <QDateTime>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->setFixedSize(750,450);
    ui->setupUi(this);
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(show_time()));
    timer->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_quit_clicked()
{
    this->close();
}

void MainWindow::on_select_file_clicked()
{
    QString path = QFileDialog::getOpenFileName(this,tr("File Name"),"/home/","Text Files(*.*)");
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly))
        QMessageBox::information(0, "info", file.errorString());
    QTextStream in(&file);
    ui->textBrowser->setText(in.readAll());
}

void MainWindow::show_time()
{
    QTime time = QTime::currentTime();
    QString time_text = time.toString(" hh:mm:ss");
    ui->clock->setText(time_text);
}
