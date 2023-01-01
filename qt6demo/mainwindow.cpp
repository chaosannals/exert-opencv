#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->filepathButton, &QPushButton::clicked, this, &MainWindow::onClickFilepathButton);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onClickFilepathButton(bool)
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setNameFilter("*.png *.jpg");
    dialog.setViewMode(QFileDialog::Detail);
    if (dialog.exec()) {
        try {
            auto first = dialog.selectedFiles().at(0);
            ui->filepathEdit->setText(first);
            cv::Mat image = cv::imread(first.toStdString());
//            cv::imwrite("H:/1.png", image);

            // 下面这个会出现野指针访问错误
//            cv::namedWindow("My Image");
//            cv::imshow("My Image", image);
        } catch (...) {

        }
    }
}
