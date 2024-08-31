#include "../s21_decimal.h"

/**
 * Функция получает бит, находящийся по индексу {index}
 * из числа {decimal} типа s21_decimal
 * @param decimal - откуда получаем бит
 * @param index - по какому интексу хотим получить бит
 * @return возвращает 1 или 0 в зависимости от того
 * какой бит был по искомому индексу
 */
int get_bit(int index, s21_decimal decimal) {
  int return_value = 0;
  if (index < 0 || index > 127) {
    return_value = -1;
  }
  int num_of_int = index / 32;  // определение номера bits[]
  int index_of_bit = index % 32;  // определение позиции в найденном bits[]
  unsigned int mask =
      1 << (index_of_bit);  // создаём число для последующей проверки
  if ((decimal.bits[num_of_int] & mask) ==
      0) {  // узнаем, выставлен ли бит на позиции index_of_bit
    return_value = 0;
  } else {
    return_value = 1;
  }
  return return_value;
}

// Returns maximum mantis with .bits[3] = 0
s21_decimal GET_MAX_MANTISS() {
  s21_decimal MAX_MANTISS;
  make_zero(&MAX_MANTISS);
  MAX_MANTISS.bits[0] = 0b11111111111111111111111111111111;
  MAX_MANTISS.bits[1] = 0b11111111111111111111111111111111;
  MAX_MANTISS.bits[2] = 0b11111111111111111111111111111111;
  return MAX_MANTISS;
}

/**
 * Функция возвращет показатель степени от 0 до 28
 * @param decimal - откуда извлекаем показатель степени
 * @return возвращает -1, если ошибка и от 0 до 28, если нет
 */
int get_scale(s21_decimal decimal) {
  unsigned int mask = 255 << 16;
  // 1111111100...00
  int scale = (decimal.bits[3] & mask) >> 16;
  // if (scale > 28) return -1;
  return scale;
}

/**
 * Функция зануляет структуру число {decimal}
 * @param decimal структура типа s21_decimal, которую будем занулять
 */
int make_zero(s21_decimal *decimal) {
  if (NULL == decimal) {
    return -1;
  }
  decimal->bits[0] = decimal->bits[1] = decimal->bits[2] = decimal->bits[3] = 0;
  return 0;
}

int s21_control_sign(big_decimal dec1, big_decimal dec2, int *dec_comparison) {
  int flag = 0;
  if ((dec1.sign) && ((!dec2.sign) || !s21_control_zero(dec2))) {
    *dec_comparison = 1;
    flag = 1;
  } else if ((dec2.sign) && ((!dec1.sign) || !s21_control_zero(dec1))) {
    *dec_comparison = 0;
    flag = 1;
  }
  return flag;
}

/**
 * Функция проверяет равняется ли число
 * типа s21_decimal нулю
 * @param decimal число, которое проверяем
 * @return возвращает: 0 - число равно нулю,
 * 1 - число не равно нулю
 */
int s21_control_zero(big_decimal decimal) {
  int control_zero = 1;
  if ((decimal.bits[0] == 0) && (decimal.bits[1] == 0) &&
      (decimal.bits[2] == 0) && (decimal.bits[3] == 0) &&
      (decimal.bits[4] == 0) && (decimal.bits[5] == 0) &&
      (decimal.bits[6] == 0))
    control_zero = 0;
  return control_zero;
}

void integer_big_div(big_decimal value, big_decimal dividing,
                     big_decimal *big_result, big_decimal *big_reminder) {
  if (NULL == big_result || NULL == big_reminder ||
      s21_control_zero(dividing) == 0)
    return;
  int ar_round = big_result->ar_round;
  int bnk_round = big_result->bnk_round;
  int sing = big_result->sign;
  make_zero_bd(big_result);
  big_result->ar_round = ar_round;
  big_result->bnk_round = bnk_round;
  big_result->sign = sing;
  if (s21_control_zero(value) == 0) {
    return;
  }
  big_decimal big_multiplication = dividing;
  while (compare_mantiss_only_bd(value, big_multiplication) >= 0) {
    int s = 0;
    for (;; s++) {
      big_decimal buffer = big_multiplication;
      shift_to_left_bd(&buffer);
      if (compare_mantiss_only_bd(buffer, value) <= 0)
        shift_to_left_bd(&big_multiplication);
      else
        break;
    }
    set_bit_bd(s, 1, big_result);
    value = simple_help_minus_bd(value, big_multiplication);
    big_multiplication = dividing;
  }
  *big_reminder = value;
}

void s21_introdution_to_common_den(big_decimal *dec1, big_decimal *dec2,
                                   int flag) {
  if (((*dec1).scale > (*dec2).scale) && ((*dec1).scale <= 28)) {
    (*dec2).ar_round = flag;
    if (flag == 0) (*dec2).bnk_round = 1;
    *dec2 = get_mantissa_with_scale_bd((*dec1).scale, (*dec2));
  } else if (((*dec2).scale > (*dec1).scale) && ((*dec2).scale <= 28)) {
    (*dec1).ar_round = flag;
    if (flag == 0) (*dec1).bnk_round = 1;
    *dec1 = get_mantissa_with_scale_bd((*dec2).scale, (*dec1));
  } else if ((((*dec1).scale > (*dec2).scale) && ((*dec1).scale > 28) &&
              ((*dec2).scale <= 28)) ||
             (((*dec2).scale > (*dec1).scale) && ((*dec2).scale > 28) &&
              ((*dec1).scale <= 28)) ||
             (((*dec2).scale > 28) && ((*dec1).scale > 28))) {
    (*dec1).ar_round = flag;
    (*dec2).ar_round = flag;
    if (flag == 0) {
      (*dec1).bnk_round = 1;
      (*dec2).bnk_round = 1;
    }
    *dec1 = get_mantissa_with_scale_bd(28, (*dec1));
    *dec2 = get_mantissa_with_scale_bd(28, (*dec2));
  }
}

/* Return value:
 * 0 -> Ok
 * 1 -> the number is too large or equal to infinity
 * 2 -> the number is too small or equal to negative infinity
 */
int s21_transform_to_96_bit(big_decimal *big_value) {
  int error_code = 0;
  bool non_zero_remainders = false;
  int last_reminder = 0;
  while ((big_value->scale > 28 ||
          compare_mantiss_only_bd(decimal_to_big_dec(GET_MAX_MANTISS()),
                                  *big_value) < 0) &&
         big_value->scale > 0) {
    non_zero_remainders = non_zero_remainders || 0 != last_reminder;

    last_reminder =
        simple_help_minus_bd(
            *big_value,
            get_mantissa_with_scale_bd(
                big_value->scale,
                get_mantissa_with_scale_bd(big_value->scale - 1, *big_value)))
            .bits[0];
    *big_value = get_mantissa_with_scale_bd(big_value->scale - 1, *big_value);
  }
  if (!non_zero_remainders && last_reminder == 5) {
    if (big_value->bits[0] & 1) {
      big_decimal big_one;
      make_zero_bd(&big_one);
      big_one.bits[0] = 1;
      *big_value = simple_help_plus_bd(*big_value, big_one);
    }
  } else {
    if (last_reminder > 4) {
      big_decimal big_one;
      make_zero_bd(&big_one);
      big_one.bits[0] = 1;
      *big_value = simple_help_plus_bd(*big_value, big_one);
    }
  }

  if (compare_mantiss_only_bd(decimal_to_big_dec(GET_MAX_MANTISS()),
                              *big_value) < 0)
    error_code = 1;
  if (error_code == 1 && big_value->sign == 1) error_code = 2;
  return error_code;
}

/**
 * Функция получает устанавливает бит {value} по индексу {index} в числе
 * {decimal} типа s21_decimal
 * @param decimal куда устанавливаем бит
 * @param index по какому интексу устанавливаем бит
 * @param value какой бит необходимо установить (0 или 1)
 * @return возвращает -1, если ошибка, и 0, если нет
 */
int set_bit(int index, int value, s21_decimal *decimal) {
  int return_value = 0;
  if (index < 0 || index > 127 || (value != 0 && value != 1) ||
      decimal == NULL) {
    return_value = -1;
  }

  int num_of_int = index / 32;
  int index_of_bit = index % 32;
  unsigned int mask = 1 << (index_of_bit);
  if (value == 1)
    decimal->bits[num_of_int] |= mask;
  else
    decimal->bits[num_of_int] &= (~mask);
  return return_value;
}

/**
 * Функция устанавливает показатель степени от 0 до 28
 * @param new_scale - устанавливаемый показатель степени
 * @param decimal - число с новым показателем степени
 * @return возвращает -1, если ошибка, и 0, если нет
 */
int set_scale(int new_scale, s21_decimal *decimal) {
  int return_value = 0;
  if (new_scale < 0 || new_scale > 255 || NULL == decimal) {
    return_value = -1;
  }
  int sign_bit = get_bit(127, *decimal);
  decimal->bits[3] = 0;
  decimal->bits[3] = new_scale << 16;
  set_bit(127, sign_bit, decimal);
  return return_value;
}

/**
 * Функция сдвигает число {decimal} побитово влево
 * @param decimal число, которое будем сдвигать
 * @return 1 если потеря битов при сдвиге, -1 если сдвига не было,
 * 0 при успешном выполнении
 */
int shift_to_left(s21_decimal *decimal) {
  if (NULL == decimal) return -1;
  int return_code = 0;
  if (get_bit(95, *decimal)) return_code = +1;
  int high_bit_of_0 = get_bit(31, *decimal);
  int high_bit_of_1 = get_bit(63, *decimal);
  (decimal->bits[0]) <<= 1;
  decimal->bits[1] <<= 1;
  decimal->bits[2] <<= 1;
  // 01010101010101010101010010100110 11010110101010010100110100101010
  // 10101010101010101010100101001101 10101101010100101001101001010100
  set_bit(32, high_bit_of_0, decimal);
  set_bit(64, high_bit_of_1, decimal);

  return return_code;
}

/**
 * Функция увеличения степени
 * @param new_scale подаваемая степень
 * @param old_scale степень big_value
 * @param decimal переменная, в которую запишется результат
 */
void increase_in_degree(int new_scale, int old_scale, s21_decimal *decimal) {
  for (int i = 0; i < new_scale - old_scale; i++) {
    s21_decimal decimal_ten;
    s21_decimal sum;
    make_zero(&sum);
    make_zero(&decimal_ten);
    decimal_ten.bits[0] = 10;
    for (int j = 0; j < 96; j++) {
      if (get_bit(j, *decimal) == 1) {
        sum = simple_help_plus(sum, decimal_ten);
      }
      shift_to_left(&decimal_ten);
    }
    *decimal = sum;
  }
}

s21_decimal get_mantissa_with_scale(int new_scale, s21_decimal decimal) {
  if (new_scale < 0) return decimal;
  int old_scale = get_scale(decimal);
  int sing_bit = get_bit(127, decimal);
  increase_in_degree(new_scale, old_scale, &decimal);
  set_scale(new_scale, &decimal);
  set_bit(127, sing_bit, &decimal);
  return decimal;
}

int arr(int i, int j);
int arr_0_18(int i, int j);
int arr_19_37(int i, int j);
int arr_38_56(int i, int j);
int arr_57_75(int i, int j);
int arr_76_95(int i, int j);

/** @brief Функция для записи значения переменной типа s21_decimal в строку. Она
 * принимает переменную типа s21_decimal и перезаписывает ее значение в формате
 * строки.
 * @param dst переменная типа s21_decimal
 * @param src[32] строка, которая хранит значения переменной типа s21_decimal
 * в привычном виде - в десятичной системе счисления;
 * @return возвращает код ошибки: 0 - ОК, 1 - ошибка преобразования;
 */
int s21_decimal_print(s21_decimal dst, char *src) {
  int error = 0;
  if (src) {
    int num = 0;
    char str_rev[32] = {0};
    for (int j = 0; j < 29; ++j) {
      for (int i = 0; i < 96; ++i) {
        if (get_bit(i, dst) == 1) {
          num += arr(i, j);
        }
      }
      str_rev[j] = num % 10;
      num /= 10;
    }
    int scale = get_scale(dst);
    if (scale > 0) {
      for (int i = 30; i >= 0; --i) {
        if (i > scale) {
          str_rev[i] = str_rev[i - 1];
        } else if (i == scale) {
          str_rev[i] = '.' - 48;  //чтобы в итоге получить '.'
        }
      }
    } else if (scale == -1) {
      error = 1;
    }
    int n = 0;
    for (int i = 29; i >= 0; --i) {
      if (str_rev[i] == 0) {
        ++n;
      } else {
        break;
      }
    }
    if (n == 0 && scale == 28) ++n;
    int bit_127 = get_bit(127, dst), point = scale > 0 ? 1 : 0;
    for (int i = 29 + point; i >= 0; --i) {
      if (i > 29 + point - n + bit_127) {
        src[i] = '\0';
      } else if (i <= 29 + point - n + bit_127) {
        src[i] = str_rev[29 + point - n - i + bit_127] + 48;  //см. ASCII
      }
      if (bit_127 == 1) {
        src[0] = '-';
      }
    }
  } else {
    error = 1;
  }
  return error;
}

int arr_0_18(int i, int j) {
  int arr[19][29] = {{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {6, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {4, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {8, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {6, 5, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {2, 1, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {4, 2, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {8, 4, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {6, 9, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {2, 9, 1, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {4, 8, 3, 6, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {8, 6, 7, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {6, 3, 5, 5, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {2, 7, 0, 1, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {4, 4, 1, 2, 6, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
  return arr[i][j];
}

int arr_19_37(int i, int j) {
  int arr[19][29] = {{8, 8, 2, 4, 2, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {6, 7, 5, 8, 4, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {2, 5, 1, 7, 9, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0,
                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {4, 0, 3, 4, 9, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0,
                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {8, 0, 6, 8, 8, 3, 8, 0, 0, 0, 0, 0, 0, 0, 0,
                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {6, 1, 2, 7, 7, 7, 6, 1, 0, 0, 0, 0, 0, 0, 0,
                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {2, 3, 4, 4, 5, 5, 3, 3, 0, 0, 0, 0, 0, 0, 0,
                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {4, 6, 8, 8, 0, 1, 7, 6, 0, 0, 0, 0, 0, 0, 0,
                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {8, 2, 7, 7, 1, 2, 4, 3, 1, 0, 0, 0, 0, 0, 0,
                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {6, 5, 4, 5, 3, 4, 8, 6, 2, 0, 0, 0, 0, 0, 0,
                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {2, 1, 9, 0, 7, 8, 6, 3, 5, 0, 0, 0, 0, 0, 0,
                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {4, 2, 8, 1, 4, 7, 3, 7, 0, 1, 0, 0, 0, 0, 0,
                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {8, 4, 6, 3, 8, 4, 7, 4, 1, 2, 0, 0, 0, 0, 0,
                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {6, 9, 2, 7, 6, 9, 4, 9, 2, 4, 0, 0, 0, 0, 0,
                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {2, 9, 5, 4, 3, 9, 9, 8, 5, 8, 0, 0, 0, 0, 0,
                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {4, 8, 1, 9, 6, 8, 9, 7, 1, 7, 1, 0, 0, 0, 0,
                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {8, 6, 3, 8, 3, 7, 9, 5, 3, 4, 3, 0, 0, 0, 0,
                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {6, 3, 7, 6, 7, 4, 9, 1, 7, 8, 6, 0, 0, 0, 0,
                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {2, 7, 4, 3, 5, 9, 8, 3, 4, 7, 3, 1, 0, 0, 0,
                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
  return arr[i][j];
}

int arr_38_56(int i, int j) {
  int arr[19][29] = {{4, 4, 9, 6, 0, 9, 7, 7, 8, 4, 7, 2, 0, 0, 0,
                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {8, 8, 8, 3, 1, 8, 5, 5, 7, 9, 4, 5, 0, 0, 0,
                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {6, 7, 7, 7, 2, 6, 1, 1, 5, 9, 9, 0, 1, 0, 0,
                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {2, 5, 5, 5, 5, 2, 3, 2, 0, 9, 9, 1, 2, 0, 0,
                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {4, 0, 1, 1, 1, 5, 6, 4, 0, 8, 9, 3, 4, 0, 0,
                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {8, 0, 2, 2, 2, 0, 3, 9, 0, 6, 9, 7, 8, 0, 0,
                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {6, 1, 4, 4, 4, 0, 6, 8, 1, 2, 9, 5, 7, 1, 0,
                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {2, 3, 8, 8, 8, 0, 2, 7, 3, 4, 8, 1, 5, 3, 0,
                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {4, 6, 6, 7, 7, 1, 4, 4, 7, 8, 6, 3, 0, 7, 0,
                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {8, 2, 3, 5, 5, 3, 8, 8, 4, 7, 3, 7, 0, 4, 1,
                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {6, 5, 6, 0, 1, 7, 6, 7, 9, 4, 7, 4, 1, 8, 2,
                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {2, 1, 3, 1, 2, 4, 3, 5, 9, 9, 4, 9, 2, 6, 5,
                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {4, 2, 6, 2, 4, 8, 6, 0, 9, 9, 9, 8, 5, 2, 1,
                      1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {8, 4, 2, 5, 8, 6, 3, 1, 8, 9, 9, 7, 1, 5, 2,
                      2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {6, 9, 4, 0, 7, 3, 7, 2, 6, 9, 9, 5, 3, 0, 5,
                      4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {2, 9, 9, 0, 4, 7, 4, 5, 2, 9, 9, 1, 7, 0, 0,
                      9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {4, 8, 9, 1, 8, 4, 9, 0, 5, 8, 9, 3, 4, 1, 0,
                      8, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {8, 6, 9, 3, 6, 9, 8, 1, 0, 7, 9, 7, 8, 2, 0,
                      6, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {6, 3, 9, 7, 2, 9, 7, 3, 0, 4, 9, 5, 7, 5, 0,
                      2, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
  return arr[i][j];
}

int arr_57_75(int i, int j) {
  int arr[20][29] = {{2, 7, 8, 5, 5, 8, 5, 7, 0, 8, 8, 1, 5, 1, 1,
                      4, 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {4, 4, 7, 1, 1, 7, 1, 5, 1, 6, 7, 3, 0, 3, 2,
                      8, 8, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {8, 8, 4, 3, 2, 4, 3, 0, 3, 2, 5, 7, 0, 6, 4,
                      6, 7, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {6, 7, 9, 6, 4, 8, 6, 0, 6, 4, 0, 5, 1, 2, 9,
                      2, 5, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {2, 5, 9, 3, 9, 6, 3, 1, 2, 9, 0, 0, 3, 4, 8,
                      5, 0, 3, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {4, 0, 9, 7, 8, 3, 7, 2, 4, 8, 1, 0, 6, 8, 6,
                      1, 1, 6, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {8, 0, 8, 5, 7, 7, 4, 5, 8, 6, 3, 0, 2, 7, 3,
                      3, 2, 2, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {6, 1, 6, 1, 5, 5, 9, 0, 7, 3, 7, 0, 4, 4, 7,
                      6, 4, 4, 8, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {2, 3, 2, 3, 0, 1, 9, 1, 4, 7, 4, 1, 8, 8, 4,
                      3, 9, 8, 6, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {4, 6, 4, 6, 0, 2, 8, 3, 8, 4, 9, 2, 6, 7, 9,
                      6, 8, 7, 3, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {8, 2, 9, 2, 1, 4, 6, 7, 6, 9, 8, 5, 2, 5, 9,
                      3, 7, 5, 7, 4, 1, 0, 0, 0, 0, 0, 0, 0, 0},
                     {6, 5, 8, 5, 2, 8, 2, 5, 3, 9, 7, 1, 5, 0, 9,
                      7, 4, 1, 5, 9, 2, 0, 0, 0, 0, 0, 0, 0, 0},
                     {2, 1, 7, 1, 5, 6, 5, 0, 7, 8, 5, 3, 0, 1, 8,
                      5, 9, 2, 0, 9, 5, 0, 0, 0, 0, 0, 0, 0, 0},
                     {4, 2, 4, 3, 0, 3, 1, 1, 4, 7, 1, 7, 0, 2, 6,
                      1, 9, 5, 0, 8, 1, 1, 0, 0, 0, 0, 0, 0, 0},
                     {8, 4, 8, 6, 0, 6, 2, 2, 8, 4, 3, 4, 1, 4, 2,
                      3, 8, 1, 1, 6, 3, 2, 0, 0, 0, 0, 0, 0, 0},
                     {6, 9, 6, 3, 1, 2, 5, 4, 6, 9, 6, 8, 2, 8, 4,
                      6, 6, 3, 2, 2, 7, 4, 0, 0, 0, 0, 0, 0, 0},
                     {2, 9, 3, 7, 2, 4, 0, 9, 2, 9, 3, 7, 5, 6, 9,
                      2, 3, 7, 4, 4, 4, 9, 0, 0, 0, 0, 0, 0, 0},
                     {4, 8, 7, 4, 5, 8, 0, 8, 5, 8, 7, 4, 1, 3, 9,
                      5, 6, 4, 9, 8, 8, 8, 1, 0, 0, 0, 0, 0, 0},
                     {8, 6, 5, 9, 0, 7, 1, 6, 1, 7, 5, 9, 2, 6, 8,
                      1, 3, 9, 8, 7, 7, 7, 3, 0, 0, 0, 0, 0, 0}};
  return arr[i][j];
}

int arr_76_95(int i, int j) {
  int arr[20][29] = {{6, 3, 1, 9, 1, 4, 3, 2, 3, 4, 1, 9, 5, 2, 7,
                      3, 6, 8, 7, 5, 5, 5, 7, 0, 0, 0, 0, 0, 0},
                     {2, 7, 2, 8, 3, 8, 6, 4, 6, 8, 2, 8, 1, 5, 4,
                      7, 2, 7, 5, 1, 1, 1, 5, 1, 0, 0, 0, 0, 0},
                     {4, 4, 5, 6, 7, 6, 3, 9, 2, 7, 5, 6, 3, 0, 9,
                      4, 5, 4, 1, 3, 2, 2, 0, 3, 0, 0, 0, 0, 0},
                     {8, 8, 0, 3, 5, 3, 7, 8, 5, 4, 1, 3, 7, 0, 8,
                      9, 0, 9, 2, 6, 4, 4, 0, 6, 0, 0, 0, 0, 0},
                     {6, 7, 1, 6, 0, 7, 4, 7, 1, 9, 2, 6, 4, 1, 6,
                      9, 1, 8, 5, 2, 9, 8, 0, 2, 1, 0, 0, 0, 0},
                     {2, 5, 3, 2, 1, 4, 9, 4, 3, 8, 5, 2, 9, 2, 2,
                      9, 3, 6, 1, 5, 8, 7, 1, 4, 2, 0, 0, 0, 0},
                     {4, 0, 7, 4, 2, 8, 8, 9, 6, 6, 1, 5, 8, 5, 4,
                      8, 7, 2, 3, 0, 7, 5, 3, 8, 4, 0, 0, 0, 0},
                     {8, 0, 4, 9, 4, 6, 7, 9, 3, 3, 3, 0, 7, 1, 9,
                      6, 5, 5, 6, 0, 4, 1, 7, 6, 9, 0, 0, 0, 0},
                     {6, 1, 8, 8, 9, 2, 5, 9, 7, 6, 6, 0, 4, 3, 8,
                      3, 1, 1, 3, 1, 8, 2, 4, 3, 9, 1, 0, 0, 0},
                     {2, 3, 6, 7, 9, 5, 0, 9, 5, 3, 3, 1, 8, 6, 6,
                      7, 2, 2, 6, 2, 6, 5, 8, 6, 8, 3, 0, 0, 0},
                     {4, 6, 2, 5, 9, 1, 1, 8, 1, 7, 6, 2, 6, 3, 3,
                      5, 5, 4, 2, 5, 2, 1, 7, 3, 7, 7, 0, 0, 0},
                     {8, 2, 5, 0, 9, 3, 2, 6, 3, 4, 3, 5, 2, 7, 6,
                      0, 1, 9, 4, 0, 5, 2, 4, 7, 4, 5, 1, 0, 0},
                     {6, 5, 0, 1, 8, 7, 4, 2, 7, 8, 6, 0, 5, 4, 3,
                      1, 2, 8, 9, 0, 0, 5, 8, 4, 9, 0, 3, 0, 0},
                     {2, 1, 1, 2, 6, 5, 9, 4, 4, 7, 3, 1, 0, 9, 6,
                      2, 4, 6, 9, 1, 0, 0, 7, 9, 8, 1, 6, 0, 0},
                     {4, 2, 2, 4, 2, 1, 9, 9, 8, 4, 7, 2, 0, 8, 3,
                      5, 8, 2, 9, 3, 0, 0, 4, 9, 7, 3, 2, 1, 0},
                     {8, 4, 4, 8, 4, 2, 8, 9, 7, 9, 4, 5, 0, 6, 7,
                      0, 7, 5, 8, 7, 0, 0, 8, 8, 5, 7, 4, 2, 0},
                     {6, 9, 8, 6, 9, 4, 6, 9, 5, 9, 9, 0, 1, 2, 5,
                      1, 4, 1, 7, 5, 1, 0, 6, 7, 1, 5, 9, 4, 0},
                     {2, 9, 7, 3, 9, 9, 2, 9, 1, 9, 9, 1, 2, 4, 0,
                      3, 8, 2, 4, 1, 3, 0, 2, 5, 3, 0, 9, 9, 0},
                     {4, 8, 5, 7, 8, 9, 5, 8, 3, 8, 9, 3, 4, 8, 0,
                      6, 6, 5, 8, 2, 6, 0, 4, 0, 7, 0, 8, 9, 1},
                     {8, 6, 1, 5, 7, 9, 1, 7, 7, 6, 9, 7, 8, 6, 1,
                      2, 3, 1, 7, 5, 2, 1, 8, 0, 4, 1, 6, 9, 3}};
  return arr[i][j];
}

int arr(int i, int j) {
  int result = 0;
  if (i <= 18) {
    result = arr_0_18(i, j);
  } else if (i <= 37) {
    result = arr_19_37(i - 19, j);
  } else if (i <= 56) {
    result = arr_38_56(i - 38, j);
  } else if (i <= 75) {
    result = arr_57_75(i - 57, j);
  } else if (i <= 95) {
    result = arr_76_95(i - 76, j);
  }
  return result;
}

int getFloatSign(float *src) { return *(int *)src >> 31; }

int getFloatExp(float *src) { return ((*(int *)src & ~SIGN) >> 23) - 127; }
