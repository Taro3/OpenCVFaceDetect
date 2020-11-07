#include <opencv2/opencv.hpp>

#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    cv::CascadeClassifier cc("./haarcascade_frontalface_default.xml");

    cv::VideoCapture vc(0);
    if (!vc.isOpened())
        return;

    while (true) {
        if (cv::waitKey(1) >= 0)
            break;
        cv::Mat frame;
        vc >> frame;
        if (frame.empty())
            break;
        std::vector<cv::Rect> faces;
        cv::Mat grayFrame;
        cv::cvtColor(frame, grayFrame, cv::COLOR_BGR2GRAY);
        cc.detectMultiScale(grayFrame, faces, 1.3, 5);

        cv::Scalar color = cv::Scalar(0, 0, 255);   // red
        for(size_t i = 0; i <faces.size(); i++)
            cv::rectangle(frame, faces[i], color, 1);

        cv::imshow("Video", frame);
    }
    vc.release();
    cv::destroyAllWindows();
}
