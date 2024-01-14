#ifndef CALCULATE
#define CALCULATE

// Среднее количество дней в году
#define DAYS_IN_MONTH 30.43688

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double s21_calculate(const char* example, double x);
int s21_isValidExpression(char** tokens, int count);
double s21_calculateExample(char** tokens, int count, double x);
double s21_calculateAction(double num_a, double num_b, char* operation);
double calculateAnnuityLoan(double principal, double interest_rate, int months);
double calculateDifferentiatedLoan(double principal, double interest_rate,
                                   int months);

int calculateDeposit(double depositAmount, int term, double percents,
                     double frequencyPayments, int capitalization,
                     double** listDepositChanges, int changesCount,
                     double* totalCapitalization, double* accruedInterest);

double getDepositChangesInMonth(double** listDepositChanges, int changesCount,
                                int month);

#endif
