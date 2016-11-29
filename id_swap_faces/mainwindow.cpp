#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"

#include "face_detection.h"
#include "face_recognition.h"
#include "face_swap.h"

#define OFFSET 50

using namespace cv;

QString _imagePath = "";
QString _imagePersonnePath = "";
QString _dirPath = "";
QString _imageSwapPath1 = "";
QString _imageSwapPath2 = "";

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
    if (img.channels() ==3 || img.channels() ==4)
        cv::cvtColor(img,img,CV_BGR2RGB);
    QImage imdisplay((uchar*)img.data, img.cols, img.rows, img.step, QImage::Format_RGB888);
    imdisplay = imdisplay.scaled(MainWindow::height()-OFFSET, MainWindow::width()-OFFSET, Qt::KeepAspectRatio);
    ui->l_image->resize(imdisplay.size());
    ui->l_image->setPixmap(QPixmap::fromImage(imdisplay));
}

void MainWindow::DisplayImage(Mat img){
    if (img.channels() ==3 || img.channels() ==4)
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

        // Apprentissage
        std::string instruction = "./../../Reconnaissance/generateCSV.sh " + _dirPath.toStdString();
        system(instruction.c_str());

        _rec = new face_recognition("learning.csv");
        _rec->learning();
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
        int nb_visages = _objects.size();
        QString textDetect = "";
        textDetect = QString::number(nb_visages);
        ui->l_nbDetect->setText(textDetect);
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

        // Apprentissage

        std::string instruction = "./../../Reconnaissance/generateCSV.sh " + _dirPath.toStdString();
        system(instruction.c_str());

        _rec = new face_recognition("learning.csv");
        _rec->learning();
    }


}

void MainWindow::on_pb_clear_clicked()
{
    ui->l_image->clear();
    ui->l_pathDir->clear();
    _imagePath = "";
    _dirPath = "";
    ui->l_nbDetect->clear();
    _detectionOK = false;
}

void MainWindow::on_pb_imagePersonne_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Ouvrir image..."), QDir::homePath());
    if ( path.isNull() == false )
    {
        _imagePersonnePath = path;
    }
    if(!(_imagePersonnePath == ""))
    {
        DisplayImage(_imagePersonnePath);
    }
}

void MainWindow::on_pb_predict_clicked()
{
    if (!(_imagePersonnePath == ""))
    {
        Mat sample = imread(_imagePersonnePath.toStdString(),0);
        Mat wanted = _rec->get_reconizedPic(_rec->predicting(sample));
        //DisplayImage(wanted);
        imshow("Retrouve", wanted);
    }
}

void MainWindow::on_pb_personne1_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Ouvrir image..."), QDir::homePath());
    if ( path.isNull() == false )
    {
        _imageSwapPath1 = path;
    }
}

void MainWindow::on_pb_personne2_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Ouvrir image..."), QDir::homePath());
    if ( path.isNull() == false )
    {
        _imageSwapPath2 = path;
    }
}



void MainWindow::on_pb_swap_clicked()
{
    if(!(_imageSwapPath1 == "") && !(_imageSwapPath2 == ""))
    {
        const char* tmp = "/tmp/tmp.png";
        const char* new_tmp = "/tmp/new_tmp.png";

        cv::Mat img1 = cv::imread(_imageSwapPath1.toStdString().c_str());
        std::vector<cv::Rect> faces1 = detect_objects(img1, Detectors::faces1);
        std::vector<cv::Rect> eyes1 = detect_objects(img1, Detectors::eye1);

        cv::Mat img2 = cv::imread(_imageSwapPath2.toStdString().c_str());
        std::vector<cv::Rect> faces2 = detect_objects(img2, Detectors::faces1);
        std::vector<cv::Rect> eyes2 = detect_objects(img2, Detectors::eye1);

        compute_mask(faces2[0],eyes2[0],eyes2[1],_imageSwapPath2.toStdString().c_str(),tmp);

        cv::Mat tm = transformed_matrix(faces1[0],eyes1[0],eyes1[1],faces2[0],eyes2[0],eyes2[1]);
        modify_foreground(tmp,new_tmp,tm);

        face_swap(200,_imageSwapPath1.toStdString().c_str(),new_tmp);

        DisplayImage("/tmp/swap.png");

    }
}
