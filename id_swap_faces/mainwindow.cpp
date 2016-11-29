#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"

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
