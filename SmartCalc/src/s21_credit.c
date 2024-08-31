#include "s21_credit.h"

// Функция для расчета параметров кредита на основе входных данных
void calc_credit(int type, double sum, int data, double procent,
                 double *total_payout, double *prepayment,
                 double *monthly_payment) {
  // Расчет месячной процентной ставки
  procent = procent / 100.0 / 12.0;
  // Проверка типа кредита
  if (type == 2) {
    // Расчет параметров для равных платежей
    int b = sum / (double)data;
    double sum_static = sum;
    *monthly_payment = round(b + (sum - b * 0) * procent);
    double a = 0.0;
    // Расчет общей суммы выплат для равных платежей
    for (int i = 0; i < data; i++) {
      a = round(b + (sum - b * i) * procent);
      *total_payout = *total_payout + a;
    }
    // Расчет авансового платежа для равных платежей
    *prepayment = *total_payout - sum_static;
  } else {
    // Расчет параметров для аннуитетных платежей
    double month = sum * (procent / (1 - pow(1 + procent, -1 * data)));
    month = (round(month * 100)) / 100.0;
    // Расчет общей суммы выплат и авансового платежа для аннуитетных платежей
    *total_payout = data * month;
    *prepayment = *total_payout - sum;
    *monthly_payment = month;
  }
}
