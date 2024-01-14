#ifndef S21_SPRINTF
#define S21_SPRINTF
#include <ctype.h>
#include <math.h>
#include <regex.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include "s21_string.h"

#define BUFFER_SIZE 1024

// Структура для хранения совпадений
typedef struct {
  int start;
  int end;
} Match;

typedef struct {
  int isFlagPlus;   // указывает на флаг +
  int isFlagMinus;  // указывает на флаг -
  int isFlagZero;   // указывает на флаг 0
  int isFlagSpace;  // указывает на флаг ' '
  int isFlagSharp;  // указывает на флаг #
  int width;        //  указывает на ширину вывода
  int precision;    // указывает на точность
  int length_h;     // указывает на длинну h
  int length_l;     // указывает на длинну l
  int length_L;     // указывает на длинну L
  char specifier;   // указывает на спецификатор типа
} formatSpecifier;

void fillFlags(char *template, int *offset, formatSpecifier *specific);
void fillLength(char *template, int *offset, formatSpecifier *specific);
int getInt(char *str, int *offset);
formatSpecifier *initFormatSpecifier(char *template, va_list args);
void extractMatches(const char *input, const char *pattern, Match **matches,
                    s21_size_t *numMatches);
void write_c(char *result, formatSpecifier *specific, va_list args);
void write_d(char *result, formatSpecifier *specific, va_list args);
void write_ouxXp(char *result, formatSpecifier *specific, va_list args,
                 int numberSystem);
void write_f(char *result, formatSpecifier *specific, va_list args);
void write_eE(char *result, formatSpecifier *specific, va_list args);
void write_gG(char *result, formatSpecifier *specific, va_list args);
void write_s(char *result, formatSpecifier *specific, va_list args);

char *convertIntToStr(long long int number, int numberSystem);
char *convertDoubleToStr(long double number, int precision);
char *convertDoubleToShortestRepresentationStr(long double number,
                                               int precision);
char *convertScientificNotationToStr(long double number, int precision);

long double scientificNotation(long double num, int *exponent);
void splitNumber(double originalNumber, int precision, int *numberInt,
                 double *numberDouble);
void putSign(char *str, formatSpecifier *specific, int isNegative);
void putPeriod(char *str);
void removeEndZeros(char *str);
double roundToPrecision(long double number, int precision);
int isZeroPrint(formatSpecifier *specific);
void printSpace(char *result, formatSpecifier *specific);
char *getStrFromTemplate(formatSpecifier *specific, va_list args);
void adjustPrecision(formatSpecifier *specific);

int s21_sprintf(char *str, const char *format, ...);
#endif