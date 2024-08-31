#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <credit.h>
#include <graph.h>

#include <QDialog>
#include <QIntValidator>
#include <QMainWindow>
#include <QPixmap>
#include <QPushButton>
#include <QString>
#include <QVector>
#include <QtMath>

extern "C" {
#include "../s21_calc.h"
#include "../s21_credit.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void number_clicked();
  void del_clicked();
  void equal_clicked();
  void next_window();
  //    void next_2_window();
  void on_graphics_button_clicked();

 private:
  Ui::MainWindow *ui;
  Graph *graph;
  Credit *credit;
  double xBegin, xEnd, h;
  int N;
  int count;
  double X = 0.0;
  double Y = 0.0;
  QVector<double> x, y;
};
#endif  // MAINWINDOW_H
