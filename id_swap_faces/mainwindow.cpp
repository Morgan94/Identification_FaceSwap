#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"

#include "face_detection.h"
#include "face_recognition.h"
#include "face_swap.h"

#define OFFSET 50

using namespace cv;

QString _imagePath = "";
QString _dirPath = "";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    _timer = new QTimer(this);
    connect(_timer, SIGNAL(timeout()), this, SLOT(DisplayImage()));
    _timer->start();



    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::DisplayImage(QString path){
    Mat img;
    img = imread(path.toStdString());
    cv::cvtColor(img,img,CV_BGR2RGB);
    QImage imdisplay((uchar*)img.data, img.cols, img.rows, img.step, QImage::Format_RGB888);
    imdisplay = imdisplay.scaled(MainWindow::height()-OFFSET, MainWindow::width()-OFFSET, Qt::KeepAspectRatio);
    ui->l_image->resize(imdisplay.size());
    ui->l_image->setPixmap(QPixmap::fromImage(imdisplay));
}

void MainWindow::DisplayImage(Mat img){
    cv::cvtColor(img,img,CV_BGR2RGB);
    QImage imdisplay((uchar*)img.data, img.cols, img.rows, img.step, QImage::Format_RGB888);
    imdisplay = imdisplay.scaled(MainWindow::height()-OFFSET, MainWindow::width()-OFFSET, Qt::KeepAspectRatio);
    ui->l_image->resize(imdisplay.size());
    ui->l_image->setPixmap(QPixmap::fromImage(imdisplay));
}

void MainWindow::on_pb_file_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Ouvrir image..."), QDir::homePath());
    if ( path.isNull() == false )
    {
        _imagePath = path;
    }
    if(!(_imagePath == ""))
    {
        DisplayImage(_imagePath);
    }

}



void MainWindow::on_pb_folder_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Ouvrir dossier..."),
                                                "/home",
                                                QFileDialog::ShowDirsOnly
                                                | QFileDialog::DontResolveSymlinks);
    if ( dir.isNull() == false )
    {
        _dirPath = dir;
    }
    if(!(_dirPath == ""))
    {
        ui->l_pathDir->setText(": " + _dirPath);
    }
}

void MainWindow::on_pb_detection_clicked()
{
    if(!(_imagePath == "") && (_dirPath == ""))
    {
        _img = imread(_imagePath.toStdString());
        _objects = detect_objects(_img, Detectors::faces);
        draw_objects(_img, _objects);
        DisplayImage(_img);
        _detectionOK = true;
    }
}

void MainWindow::on_pb_arb_clicked()
{
    if (_detectionOK)
    {
        QString dir = QFileDialog::getExistingDirectory(this, tr("Ouvrir dossier..."),
                                                    "/home",
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);
        if ( dir.isNull() == false )
        {
            _dirPath = dir;
        }
        save_square_images(_img, _objects, _dirPath.toStdString());
    }


}

void MainWindow::on_pb_clear_clicked()
{
    ui->l_image->clear();
    ui->l_pathDir->clear();
    _imagePath = "";
    _dirPath = "";
    _detectionOK = false;
}
