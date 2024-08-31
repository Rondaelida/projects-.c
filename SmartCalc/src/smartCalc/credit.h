#ifndef CREDIT_H
#define CREDIT_H

#include <QDialog>

extern "C" {
#include "../s21_calc.h"
#include "../s21_credit.h"
}

namespace Ui {
class Credit;
}

class Credit : public QDialog {
  Q_OBJECT

 public:
  explicit Credit(QWidget *parent = nullptr);
  ~Credit();

 private slots:
  void but_clicked();

 private:
  Ui::Credit *ui;
};

#endif  // CREDIT_H
