#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QTimer>
#include "opencv2/opencv.hpp"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    void DisplayImage(QString path);

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QImage _imdisplay;
    QTimer* _timer;

private slots:
    void on_pb_file_clicked();
    void on_pb_folder_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
