#include "s21_calculate.h"

#include <stdio.h>

#include "s21_helpers.h"
#include "s21_settings.h"

// Вычисление математического выражения
double s21_calculate(const char *example, double x) {
  double result = NAN;
  int count = 0;

  // Получение токенов из выражения
  char **tokens = s21_getTokensList(example, &count);

  // Проверка валидности выражения
  if (s21_isValidExpression(tokens, count)) {
    int outputCount = 0;

    // Преобразование в обратную польскую запись (RPN)
    char **pol_nat = s21_convertToRPN(tokens, count, &outputCount);

    // Вычисление значения выражения в RPN
    result = s21_calculateExample(pol_nat, outputCount, x);

    // Освобождение памяти
    s21_freeStringArray(pol_nat, count);
  }

  // Освобождение памяти
  s21_freeStringArray(tokens, count);

  return result;
}

// Проверка валидности математического выражения
int s21_isValidExpression(char **tokens, int count) {
  int result = 1;
  int balance = 0;
  int expectOperand = -1;
  int isUnary = 0;

  // Перебор токенов
  for (int i = 0; i < count; i++) {
    // Проверка токена на число, оператор или параметр
    if (!s21_isNumber(tokens[i]) && !s21_isOperator(tokens[i]) &&
        strcmp(tokens[i], PARAM) != 0) {
      result = 0;
      break;
    } else if (strcmp(tokens[i], "(") == 0) {
      balance++;
      isUnary = 1;
    } else if (strcmp(tokens[i], ")") == 0) {
      if (--balance < 0) {
        result = 0;  // Несбалансированные скобки
        break;
      }
    } else {
      // Проверка корректности использования операторов и чисел
      if (expectOperand == -1 && s21_isBinaryOperator(tokens[i]) &&
          strcmp(tokens[i], "-") != 0 && strcmp(tokens[i], "+") != 0) {
        result = 0;
        break;
      }
      if (s21_isNumber(tokens[i]) || strcmp(tokens[i], PARAM) == 0) {
        if (expectOperand == 3) {
          result = 0;
          break;
        }
        expectOperand = 3;
      } else if (s21_isBinaryOperator(tokens[i])) {
        if ((strcmp(tokens[i], "-") == 0 || strcmp(tokens[i], "+") == 0) &&
            isUnary) {
        } else if (expectOperand == 2) {
          result = 0;
          break;
        }
        expectOperand = 2;
      }
    }
  }

  // Валидное выражение должно иметь сбалансированные скобки и правильное
  // количество операндов
  return result && balance == 0 && expectOperand == 3;
}

// Вычисление значения выражения
double s21_calculateExample(char **tokens, int count, double x) {
  double stack[count];
  int stackSize = 0;

  // Перебор токенов в RPN
  for (int i = 0; i < count; i++) {
    if (s21_isNumber(tokens[i])) {
      // Если токен - число, помещаем его в стек
      stack[stackSize++] = atof(tokens[i]);
    } else if (strcmp(tokens[i], "x") == 0) {
      // Если токен - переменная x, помещаем значение x в стек
      stack[stackSize++] = x;
    } else {
      double result = 0;

      // Выполнение операции над числами в соответствии с оператором
      if (s21_isBinaryOperator(tokens[i])) {
        if (stackSize < 2) {
          stack[0] = NAN;
          break;
        }
        double num_b = stack[--stackSize], num_a = stack[--stackSize];
        result = s21_calculateAction(num_a, num_b, tokens[i]);
      } else {
        if (stackSize < 1) {
          stack[0] = NAN;
          break;
        }
        double num_a = stack[--stackSize];
        result = s21_calculateAction(num_a, NAN, tokens[i]);
      }

      // Помещаем результат в стек
      if (isnan(result)) {
        stack[0] = NAN;
        break;
      }
      stack[stackSize++] = result;
    }
  }

  // Если стек содержит не один элемент, результат - NaN
  if (stackSize != 1) {
    stack[0] = NAN;
  }

  return stack[0];
}

// Функция для расчета кредита аннуитетным способом
double calculateAnnuityLoan(double principal, double interestRate, int months) {
  // Преобразование процентной ставки в месячную ставку
  double monthlyInterestRate = interestRate / 12 / 100;

  // Расчет аннуитетного коэффициента
  double annuityFactor =
      (monthlyInterestRate * pow(1 + monthlyInterestRate, months)) /
      (pow(1 + monthlyInterestRate, months) - 1);

  // Расчет ежемесячного платежа
  double monthlyPayment = principal * annuityFactor;

  // Расчет общей выплаты
  double totalPayment = monthlyPayment * months;

  return totalPayment;
}

// Функция для расчета кредита по дифференцированной системе
double calculateDifferentiatedLoan(double principal, double interestRate,
                                   int months) {
  // Преобразование процентной ставки в месячную ставку
  double monthlyInterestRate = interestRate / 12 / 100;

  // Создание массива для хранения ежемесячных платежей
  double monthlyPayments[months];

  // Расчет ежемесячного платежа для каждого месяца
  for (int month = 1; month <= months; ++month) {
    // Расчет суммы выплаты для текущего месяца
    double monthlyPayment = (principal / months) +
                            (principal - ((month - 1) * (principal / months))) *
                                monthlyInterestRate;
    monthlyPayments[month - 1] = monthlyPayment;
  }

  // Расчет общей выплаты
  double totalPayment = 0.0;
  for (int i = 0; i < months; ++i) {
    totalPayment += monthlyPayments[i];
  }

  return totalPayment;
}

// Функция для получения изменений в сумме депозита за месяц
double getDepositChangesInMonth(double **listDepositChanges, int changesCount,
                                int month) {
  double result = 0;

  // Ищем изменения для указанного месяца
  for (int i = 0; i < changesCount; i++) {
    if (listDepositChanges[i][0] == month) {
      result += listDepositChanges[i][1];
      listDepositChanges[i][1] =
          0;  // Обнуляем значение, чтобы избежать повторного учета
    }
  }

  return result;
}

// Функция для расчета депозита с возможностью капитализации
// и изменениями в сумме депозита в течение срока
int calculateDeposit(double depositAmount, int term, double percents,
                     double frequencyPayments, int capitalization,
                     double **listDepositChanges, int changesCount,
                     double *totalCapitalization, double *accruedInterest) {
  int code = 0;
  *totalCapitalization = depositAmount;
  int termInDays = term * DAYS_IN_MONTH;

  // Если капитализация отключена, устанавливаем frequencyPayments равным сроку
  if (capitalization == 0) {
    frequencyPayments = termInDays;
  }

  // Расчет процента на период
  double percentageForPeriod =
      ((percents / 12) * term / (termInDays * 100)) * frequencyPayments;
  int daysWithoutInterest = 0;

  // Проходим по каждому дню в течение срока депозита
  for (int day = 1; day <= termInDays; day++) {
    // Учитываем изменения в сумме депозита за текущий месяц
    *totalCapitalization += getDepositChangesInMonth(
        listDepositChanges, changesCount, day / DAYS_IN_MONTH);

    // Если сумма депозита стала отрицательной, устанавливаем код ошибки
    if (*totalCapitalization < 0) {
      code = 1;
      break;
    }

    // Если прошло нужное количество дней без начисления процентов,
    // начисляем проценты и обновляем счетчик дней
    if (++daysWithoutInterest == (int)frequencyPayments) {
      double accrualInterest = *totalCapitalization * percentageForPeriod;
      *accruedInterest += accrualInterest;

      // Если включена капитализация, добавляем начисленные проценты к сумме
      // депозита
      if (capitalization) {
        *totalCapitalization += accrualInterest;
      }

      daysWithoutInterest = 0;
    }
  }

  // Если произошла ошибка, сбрасываем значения
  if (code) {
    *totalCapitalization = 0;
    *accruedInterest = 0;
  }

  return code;
}

// Выполнение операции над двумя числами в соответствии с оператором
double s21_calculateAction(double num_a, double num_b, char *operation) {
  double result = NAN;
  if (strcmp(operation, "+") == 0) {
    result = num_a + num_b;
  } else if (strcmp(operation, "-") == 0) {
    result = num_a - num_b;
  } else if (strcmp(operation, "~") == 0) {
    result = -num_a;
  } else if (strcmp(operation, "/") == 0) {
    if (num_b != 0) {
      result = num_a / num_b;
    }
  } else if (strcmp(operation, "mod") == 0) {
    if (num_b != 0) {
      result = fmod(num_a, num_b);
    }
  } else if (strcmp(operation, "*") == 0)
    result = num_a * num_b;
  else if (strcmp(operation, "^") == 0)
    result = pow(num_a, num_b);
  else if (strcmp(operation, "sin") == 0)
    result = sin(num_a);
  else if (strcmp(operation, "asin") == 0)
    result = asin(num_a);
  else if (strcmp(operation, "cos") == 0)
    result = cos(num_a);
  else if (strcmp(operation, "acos") == 0)
    result = acos(num_a);
  else if (strcmp(operation, "tan") == 0)
    result = tan(num_a);
  else if (strcmp(operation, "atan") == 0)
    result = atan(num_a);
  else if (strcmp(operation, "log") == 0)
    result = log10(num_a);
  else if (strcmp(operation, "ln") == 0)
    result = log(num_a);
  else if (strcmp(operation, "sqrt") == 0)
    result = sqrt(num_a);
  return result;
}
