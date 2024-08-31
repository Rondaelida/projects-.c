#include "credit.h"
#include "ui_credit.h"

Credit::Credit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Credit)
{
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(but_clicked()));
}



Credit::~Credit()
{
    delete ui;
}

void Credit::but_clicked(){
    double summa = ui->lineEdit_3->text().toDouble();
    int data = ui->lineEdit->text().toInt();
    double procent = ui->lineEdit_2->text().toDouble();
    double total_payout = 0.0;
    double prepayment = 0.0;
    double montly_payment = 0.0;

    if (ui->radioButton->isChecked()) {
        calc_credit(1, summa, data, procent, &total_payout, &prepayment, &montly_payment);
    } else {
        calc_credit(2, summa, data, procent, &total_payout, &prepayment, &montly_payment);
    }

    ui->lineEdit_4->setText(QString::number(montly_payment, 'g', 15));
    ui->lineEdit_5->setText(QString::number(prepayment, 'g', 15));
    ui->lineEdit_6->setText(QString::number(total_payout, 'g', 15));
}
