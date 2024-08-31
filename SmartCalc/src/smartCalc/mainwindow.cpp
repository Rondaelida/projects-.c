#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graph.h"
#include "ui_graph.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(number_clicked()));
    connect(ui->pushButton_13, SIGNAL(clicked()), this, SLOT(number_clicked()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(number_clicked()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(number_clicked()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(number_clicked()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(number_clicked()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(number_clicked()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(number_clicked()));
    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(number_clicked()));
    connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(number_clicked()));
    connect(ui->pushButton_10, SIGNAL(clicked()), this, SLOT(number_clicked()));
    connect(ui->pushButton_14, SIGNAL(clicked()), this, SLOT(number_clicked()));
    connect(ui->pushButton_17, SIGNAL(clicked()), this, SLOT(number_clicked()));
    connect(ui->pushButton_16, SIGNAL(clicked()), this, SLOT(number_clicked()));
    connect(ui->pushButton_11, SIGNAL(clicked()), this, SLOT(number_clicked()));
    connect(ui->pushButton_27, SIGNAL(clicked()), this, SLOT(number_clicked()));
    connect(ui->pushButton_28, SIGNAL(clicked()), this, SLOT(number_clicked()));
    connect(ui->pushButton_22, SIGNAL(clicked()), this, SLOT(number_clicked()));
    connect(ui->pushButton_15, SIGNAL(clicked()), this, SLOT(number_clicked()));
    connect(ui->pushButton_20, SIGNAL(clicked()), this, SLOT(number_clicked()));
    connect(ui->pushButton_24, SIGNAL(clicked()), this, SLOT(number_clicked()));
    connect(ui->pushButton_19, SIGNAL(clicked()), this, SLOT(number_clicked()));
    connect(ui->pushButton_23, SIGNAL(clicked()), this, SLOT(number_clicked()));
    connect(ui->pushButton_18, SIGNAL(clicked()), this, SLOT(number_clicked()));
    connect(ui->pushButton_21, SIGNAL(clicked()), this, SLOT(number_clicked()));
    connect(ui->pushButton_25, SIGNAL(clicked()), this, SLOT(number_clicked()));
    connect(ui->pushButton_29, SIGNAL(clicked()), this, SLOT(number_clicked()));
    connect(ui->pushButton_30, SIGNAL(clicked()), this, SLOT(number_clicked()));
    connect(ui->pushButton_26, SIGNAL(clicked()), this, SLOT(del_clicked()));
    connect(ui->pushButton_12, SIGNAL(clicked()), this, SLOT(equal_clicked()));
    connect(ui->radioButton_3, SIGNAL(clicked()), this, SLOT(next_window()));
//    connect(ui->radioButton_2, SIGNAL(clicked()), this, SLOT(next_2_window()));
    connect(ui->pushButton_31, SIGNAL(clicked()), this, SLOT(on_graphics_button_clicked()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::number_clicked(){
    QPushButton *button = (QPushButton *)sender();
    ui->lineEdit->setText(ui->lineEdit->text() + button->text());
}
void MainWindow::del_clicked(){
     ui->lineEdit->setText("");
}

void MainWindow::on_graphics_button_clicked()
{
    QString str = ui->lineEdit->text();
    QByteArray ba = str.toLocal8Bit();
    char* buf = ba.data();

    h = 0.1;
    xBegin = ui->x_min->text().toDouble();
    xEnd = ui->x_max->text().toDouble();
    double y_min = ui->y_min->text().toDouble();
    double y_max = ui->y_max->text().toDouble();
    ui->widget->clearGraphs();
    ui->widget->xAxis->setRange(xBegin, xEnd);
    ui->widget->yAxis->setRange(y_min, y_max);

    for (X = xBegin; X <= xEnd; X += h) {
        Y = s21_parser(buf, X);
        x.push_back(X);
        y.push_back(Y);
    }

    ui->widget->addGraph();
    ui->widget->graph(0)->addData(x, y);
    ui->widget->replot();
    x.clear();
    y.clear();

}
void MainWindow::equal_clicked(){
    QString expression = ui->lineEdit->text() + " + 0.0";

    if (expression.isEmpty()) {
      return;
    }

    QByteArray byteArray = expression.toLocal8Bit();
    char *infix = byteArray.data();
    char *postfix = (char *)malloc(255 * sizeof(char));

    double result;
    if(ui->lineEdit_2->text().isEmpty()){
        result = s21_parser(infix, 0.0);
    }
    else{
        result = s21_parser(infix,  ui->lineEdit_2->text().toDouble());
    }

    ui->lineEdit->setText(QString::number(result, 'g', 15));
}

void MainWindow::next_window(){
    credit = new Credit();
     credit->setModal(true);
     credit->show();
}
//void MainWindow::next_2_window(){
//    graph = new Graph();
//     graph->setModal(true);
//     graph->show();
//}


