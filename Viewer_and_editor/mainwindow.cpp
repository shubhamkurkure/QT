//This is the C++ code for an application which enables the user to open and edit various files in linux.
//OpenCV as a prerequisite is required to run the run the program in Qt.
//To run the program just open it in Qt and click the green play button on the bottom right.

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QTimer>
#include <QDateTime>
#include <iostream>
#include <QApplication>
#include <QDebug>
#include <QDesktopWidget>
#include <string>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include <cv.h>
#include <highgui.h>
#include <QFileInfo>
#include <QDesktopServices>
#include <QPixmap>
using namespace std;
using namespace cv;
static Mat image2;
static std::string fpath2;
static std::string fpath_txtf;
MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow){
    this->setFixedSize(930,700);
    ui->setupUi(this);
    ui->grey_scale->setVisible(false);
    ui->properties->setVisible(false);
    ui->bright->setVisible(false);
    ui->d_image->setVisible(false);
    ui->original->setVisible(false);
    ui->textBrowser->setVisible(true);
    ui->textBrowser->setText("\t\t**THIS APPLICATION ENABLES THE USER TO EDIT FILE IN UBUNTU**.\n\n1. Click on OPEN FILE to choose the file. \n\n2. If you choose an image file you can change it's brightness using BRIGHT button, convert it into    grayscale by clicking GREYSCALE, display it's properties by clicking on PROPERTIES button. \n\n3. For files other than images the app automatically opens the file in default Desktop apps.");

    QPixmap pix1("/home/shubhamkurkure/Downloads/tifrlogo.png");
    ui->tifr_logo->setPixmap(pix1.scaled(QSize(131, 41), Qt::KeepAspectRatio));
    QPixmap pix2("/home/shubhamkurkure/Downloads/fcritlogo.png");
    ui->fcrit_logo->setPixmap(pix2.scaled(QSize(61, 41), Qt::KeepAspectRatio));

    QDateTime date = QDateTime::currentDateTime();
    QString datetime = date.toString();
    ui->date->setText(datetime);
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(show_time()));
    timer->start();
  }
MainWindow::~MainWindow(){
  delete ui;
}
void MainWindow::on_quit_clicked(){
  this->close();
}
void MainWindow::on_select_file_clicked(){
  QString path = QFileDialog::getOpenFileName(this,tr("File Name"),"/home/","All Files(*.*)");
  QFile file(path);
  std::string fpath = path.toUtf8().constData();
  ui->d_name->setVisible(false);
  ui->image_name->setVisible(false);
  ui->loc->setVisible(false);
  ui->sze->setVisible(false);
  ui->typei->setVisible(false);
  ui->res->setVisible(false);
  ui->d_image->setVisible(false);
  ui->bright->setVisible(false);
  ui->grey_scale->setVisible(false);
  ui->properties->setVisible(false);
  ui->original->setVisible(false);
  ui->textBrowser->setVisible(true);
  fpath_txtf=fpath;
  int i=fpath.length()-1;
  while (fpath.at(i)!='.'){
    i--;
  }
  std::string ptype;
  for(;i<fpath.length();i++){
    string c(1,fpath.at(i));
    ptype.append(c);
  }
   if(!(ptype.compare(".png"))){
    ui->loc->setVisible(false);
    ui->sze->setVisible(false);
    ui->typei->setVisible(false);
    ui->res->setVisible(false);
    ui->textBrowser->setVisible(false);
    ui->d_image->setVisible(true);
    ui->image_name->setVisible(true);
    Mat image = imread(fpath);
    image2=image;
    fpath2=fpath;
    if(!image.empty()){
     ui->grey_scale->setVisible(true);
     ui->properties->setVisible(true);
     ui->bright->setVisible(true);
     ui->original->setVisible(true);
     ui->loc->setVisible(false);
     ui->sze->setVisible(false);
     ui->typei->setVisible(false);
     ui->res->setVisible(false);
     int i;
     i=fpath.length()-1;
     while (fpath.at(i)!='/'){
       i--;
     }
     i++;
     std::string file_name;
     for(;i<fpath.length();i++){
       std::string c(1,fpath.at(i));
       file_name.append(c);
     }
     QString qpic1 = QString::fromStdString(file_name);
     ui->image_name->setText(qpic1);
   }
    QPixmap temp(path);
    QPixmap pix = temp.scaled(QSize(631,321), Qt::KeepAspectRatio);
    ui->d_image->setPixmap(pix);
  }else{
       const char* editor_path=fpath_txtf.c_str();
       QDesktopServices::openUrl(QUrl(editor_path));
  }
}
void MainWindow::show_time(){
  QTime time = QTime::currentTime();
  QString time_text = time.toString(" hh:mm:ss");
  ui->clock->setText(time_text);
}
void MainWindow::on_grey_scale_clicked(){
  ui->grey_scale->setStyleSheet(QString("QPushButton {background-color: green;} QPushButton:checked{background-color: green;} QPushButton:pressed {background-color: green;}"));
  ui->original->setStyleSheet(QString("QPushButton {background-color: white;} QPushButton:checked{background-color: white;} QPushButton:pressed {background-color: white;}"));
  ui->bright->setStyleSheet(QString("QPushButton {background-color: white;} QPushButton:checked{background-color: white;} QPushButton:pressed {background-color: white;}"));
  ui->properties->setStyleSheet(QString("QPushButton {background-color: white;} QPushButton:checked{background-color: white;} QPushButton:pressed {background-color: white;}"));
  if(!image2.data){
           cout << "No image data \n";
  }
  //Converting the Image into GrayScale
  Mat img_gray;
  img_gray = imread(fpath2,IMREAD_GRAYSCALE);
  long i=fpath2.length()-1;
  while(fpath2.at(i)!='.')
    i--;
  string grayPath;
  grayPath.assign(fpath2,0,i);
  i++;
  string c;
  grayPath.append("1.");
  for(;i<fpath2.length();i++){
    string c(1,fpath2.at(i));
    grayPath.append(c);
  }
  cout<<fpath2<<"\n"<<grayPath;
  imwrite(grayPath,img_gray);
  QString qstr = QString::fromStdString(grayPath);
  QPixmap temp(qstr);
  QPixmap pix = temp.scaled(QSize(631,321),  Qt::KeepAspectRatio);
  ui->d_image->setPixmap(pix);
}
void MainWindow::on_bright_clicked(){
  ui->bright->setStyleSheet(QString("QPushButton {background-color: green;} QPushButton:checked{background-color: green;} QPushButton:pressed {background-color: green;}"));
  ui->original->setStyleSheet(QString("QPushButton {background-color: white;} QPushButton:checked{background-color: white;} QPushButton:pressed {background-color: white;}"));
  ui->grey_scale->setStyleSheet(QString("QPushButton {background-color: white;} QPushButton:checked{background-color: white;} QPushButton:pressed {background-color: white;}"));
  ui->properties->setStyleSheet(QString("QPushButton {background-color: white;} QPushButton:checked{background-color: white;} QPushButton:pressed {background-color: white;}"));
  if(!image2.data){
    cout << "Error loading the image" << endl;
  }
  //Create a window
  namedWindow("My Window", 1);
  //Create trackbar to change brightness
  int iSliderValue1 = 50;
  createTrackbar("Brightness", "My Window", &iSliderValue1, 100);
  //Create trackbar to change contrast
  int iSliderValue2 = 50;
  createTrackbar("Contrast", "My Window", &iSliderValue2, 100);
  //createButton()
  //createButton("QUIT", my_button,NULL, CV_PUSH_BUTTON, 0);
  while(true){
    //Change the brightness and contrast of the image
    Mat dst;
    int iBrightness  = iSliderValue1 - 50;
    double dContrast = iSliderValue2 / 50.0;
    image2.convertTo(dst, -1, dContrast, iBrightness);
    //show the brightness and contrast adjusted image
    imshow("My Window", dst);
    // Wait until user press some key for 50ms
    int iKey = waitKey(50);
    //if user press 'ESC' key
    if (iKey == 27){
      break;
    }
  }
  waitKey(1); // Wait for any keystroke in the window
  destroyWindow("My Window");//destroy the created window
}
void MainWindow::on_properties_clicked(){
  ui->properties->setStyleSheet(QString("QPushButton {background-color: green;} QPushButton:checked{background-color: green;} QPushButton:pressed {background-color: green;}"));
  ui->original->setStyleSheet(QString("QPushButton {background-color: white;} QPushButton:checked{background-color: white;} QPushButton:pressed {background-color: white;}"));
  ui->bright->setStyleSheet(QString("QPushButton {background-color: white;} QPushButton:checked{background-color: white;} QPushButton:pressed {background-color: white;}"));
  ui->grey_scale->setStyleSheet(QString("QPushButton {background-color: white;} QPushButton:checked{background-color: white;} QPushButton:pressed {background-color: white;}"));
  ui->loc->setVisible(true);
  ui->sze->setVisible(true);
  ui->typei->setVisible(true);
  ui->res->setVisible(true);
  int i;
  i=fpath2.length()-1;
  while(fpath2.at(i)!='.'){
    i--;
  }
  std::string ptype("Type:");
  for(;i<fpath2.length();i++){
    string c(1,fpath2.at(i));
    ptype.append(c);
  }
  QString qtype = QString::fromStdString(ptype);
  ui->typei->setText(qtype);
  QString qloc = QString::fromStdString(fpath2);
  ui->loc->setText("Location"+qloc);
  QPixmap pix1(qloc);
  int h= pix1.height();
  int w=pix1.width();
  cout<<h<<" "<<w;
  std::string psize("Resolution:");
  psize.append(std::to_string(w));
  psize.append(" X ");
  psize.append(std::to_string(h));
  QString qsize = QString::fromStdString(psize);
  ui->res->setText(qsize);
  const char* fp=fpath2.c_str();
  QFile myfile(fp);
  float imsize=myfile.size();
  std::string image_size;
  image_size.append(std::to_string(imsize));
  QString qimage_size=  QString::fromStdString(image_size);
  //convert bytes in kb or Mb
  QStringList list;
  list << "KB" << "MB" << "GB" << "TB";
  QStringListIterator k(list);
  QString unit("bytes");
  while(imsize >= 1024.0 && k.hasNext()){
                unit = k.next();
                imsize /= 1024.0;
  }
  ui->sze->setText("Size:"+QString().setNum(imsize,'f',2)+" "+unit);
}
void MainWindow::on_original_clicked(){
  ui->original->setStyleSheet(QString("QPushButton {background-color: green;} QPushButton:checked{background-color: green;} QPushButton:pressed {background-color: green;}"));
  ui->grey_scale->setStyleSheet(QString("QPushButton {background-color: white;} QPushButton:checked{background-color: white;} QPushButton:pressed {background-color: white;}"));
  ui->bright->setStyleSheet(QString("QPushButton {background-color: white;} QPushButton:checked{background-color: white;} QPushButton:pressed {background-color: white;}"));
  ui->properties->setStyleSheet(QString("QPushButton {background-color: white;} QPushButton:checked{background-color: white;} QPushButton:pressed {background-color: white;}"));
  QString qstr = QString::fromStdString(fpath2);
  QPixmap temp(qstr);
  QPixmap pix = temp.scaled(QSize(631,321),  Qt::KeepAspectRatio);
  ui->d_image->setPixmap(pix);
}
