#ifdef __cplusplus
extern "C" {
#endif
#ifndef SRC_S21_CREDIT_H_
#define SRC_S21_CREDIT_H_

#include <math.h>

void calc_credit(int type, double sum, int data, double procent,
                 double *total_payout, double *prepayment,
                 double *monthly_payment);

#endif
#ifdef __cplusplus
}
#endif