#include "s21_sprintf.h"

void fillFlags(char *template, int *offset, formatSpecifier *specific) {
  // Парсинг флагов
  while (template[*offset] == '+' || template[*offset] == '-' ||
         template[*offset] == ' ' || template[*offset] == '0' ||
         template[*offset] == '#') {
    switch (template[*offset]) {
      case '+':
        specific->isFlagPlus = 1;
        break;
      case '-':
        specific->isFlagMinus = 1;
        break;
      case '0':
        specific->isFlagZero = 1;
        break;
      case ' ':
        specific->isFlagSpace = 1;
        break;
      case '#':
        specific->isFlagSharp = 1;
        break;
    }
    (*offset)++;
  }
}

// Парсинг длинны
void fillLength(char *template, int *offset, formatSpecifier *specific) {
  while (template[*offset] == 'h' || template[*offset] == 'l' ||
         template[*offset] == 'L') {
    switch (template[*offset]) {
      case 'h':
        specific->length_h += 1;
        break;
      case 'l':
        specific->length_l += 1;
        break;
      case 'L':
        specific->length_L += 1;
        break;
    }
    (*offset)++;
  }
}

// Метод получения числа из строки
int getInt(char *str, int *offset) {
  char strDigit[128];
  int idx = 0;
  while (isdigit(str[*offset])) {
    strDigit[idx++] = str[(*offset)++];
  }
  strDigit[idx] = '\0';
  int result = atoi(strDigit);
  return idx != 0 ? result : -1;
}

// Метод для формирования настроек для конкретного template
formatSpecifier *initFormatSpecifier(char *template, va_list args) {
  formatSpecifier *specific = calloc(1, sizeof(formatSpecifier));
  int offset = 1;
  fillFlags(template, &offset, specific);
  if (template[offset] == '*') {
    specific->width = va_arg(args, int);
    offset++;
  } else {
    specific->width = getInt(template, &offset);
  }

  if (template[offset] == '.') {
    offset++;
    if (template[offset] == '*') {
      specific->precision = va_arg(args, int);
      offset++;
    } else {
      specific->precision = getInt(template, &offset);
    }
  }
  fillLength(template, &offset, specific);
  specific->specifier = template[offset];

  return specific;
}

// Метод для перебора всех совпадений регулярного выражения
void extractMatches(const char *input, const char *pattern, Match **matches,
                    s21_size_t *numMatches) {
  regex_t regex;
  int ret;

  // Компилируем регулярное выражение
  ret = regcomp(&regex, pattern, REG_EXTENDED);
  if (ret == 0) {
    regmatch_t match;
    int offset = 0;

    while (1) {
      ret = regexec(&regex, input + offset, 1, &match, 0);

      if (ret == REG_NOMATCH) {
        break;  // Совпадений больше нет
      }

      // Извлечение совпадения из строки
      int start = match.rm_so + offset;
      int end = match.rm_eo + offset;

      // Расширяем массив совпадений
      *matches = realloc(*matches, (*numMatches + 1) * sizeof(Match));
      (*matches)[*numMatches].start = start;
      (*matches)[*numMatches].end = end;
      (*numMatches)++;

      offset =
          end;  // Устанавливаем новый сдвиг для поиска следующего совпадения
    }
  }
  regfree(&regex);
}

void write_c(char *result, formatSpecifier *specific, va_list args) {
  if (specific->length_l > 0) {
    wchar_t longChar = va_arg(args, wchar_t);
    wchar_t srt[] = {longChar, '\0'};
    wcstombs(result, srt, 2);
  } else {
    int ch = va_arg(args, int);
    char srt[] = {ch, '\0'};
    s21_strcpy(result, srt);
  }
}

void write_s(char *result, formatSpecifier *specific, va_list args) {
  if (specific->length_l > 0) {
    wchar_t *longCharStr = va_arg(args, wchar_t *);
    if (specific->precision == -1) {
      wcstombs(result, longCharStr, wcslen(longCharStr));

    } else {
      wcstombs(result, longCharStr, specific->precision);
    }

  } else {
    char *str = va_arg(args, char *);
    if (specific->precision == -1) {
      s21_strncpy(result, str, s21_strlen(str));
    } else {
      s21_strncpy(result, str, specific->precision);
    }
  }
}

void write_f(char *result, formatSpecifier *specific, va_list args) {
  char *str = s21_NULL;
  int isNegative = 0;
  if (specific->length_l == 1) {
    double arg = va_arg(args, double);
    isNegative = arg < 0;
    str = convertDoubleToStr(arg, specific->precision);
  } else if (specific->length_l == 2 || specific->length_L == 1) {
    long double arg = va_arg(args, long double);
    isNegative = arg < 0;
    str = convertDoubleToStr(arg, specific->precision);
  } else {
    double arg = va_arg(args, double);
    isNegative = arg < 0;
    str = convertDoubleToStr(arg, specific->precision);
  }
  if (str != s21_NULL) {
    if (specific->isFlagSharp) {
      putPeriod(str);
    }
    if (specific->isFlagZero) {
      specific->width -=
          (specific->isFlagPlus || specific->isFlagSpace || isNegative);
      printSpace(str, specific);
    }
    putSign(str, specific, isNegative);
    s21_strcpy(result, str);
  }
  free(str);
}

char *convertDoubleToStr(long double number, int precision) {
  int bufferSize = BUFFER_SIZE;
  char *buffer = calloc(bufferSize, sizeof(char));
  if (number < 0) {
    number *= -1;
  }
  double roundedNumber = roundToPrecision(number, precision);
  double numberDoublePart;
  int numberIntPart;
  splitNumber(roundedNumber, precision, &numberIntPart, &numberDoublePart);
  char *numberIntStr = convertIntToStr(numberIntPart, 10);
  int idx = s21_strlen(numberIntStr);
  s21_strcpy(buffer, numberIntStr);
  if (precision > 0) {
    buffer[idx++] = '.';
    for (int i = 1; i <= precision; ++i) {
      numberDoublePart *= 10;
      int offset = 0;
      if (i != precision) {
        offset = (int)numberDoublePart % 10;
      } else {
        offset = (int)round(numberDoublePart);
        offset = offset > 9 ? 9 : offset;
      }
      buffer[idx++] = '0' + offset;
      numberDoublePart -= offset;
    }
    buffer[idx] = '\0';
  }
  free(numberIntStr);
  return buffer;
}

double roundToPrecision(long double number, int precision) {
  double multiplier = pow(10, precision);
  return round(number * multiplier) / multiplier;
}

void splitNumber(double originalNumber, int precision, int *numberInt,
                 double *numberDouble) {
  double multiplier = pow(10, precision);
  double roundedNumber = floor(originalNumber * multiplier) / multiplier;

  *numberInt = (int)roundedNumber;
  *numberDouble = fmod(roundedNumber, 1.0);
}

void write_ouxXp(char *result, formatSpecifier *specific, va_list args,
                 int numberSystem) {
  char *str = s21_NULL;
  if (specific->length_h == 1) {
    unsigned short int arg = va_arg(args, unsigned int);
    str = convertIntToStr(arg, numberSystem);
  } else if (specific->length_l == 1) {
    unsigned long int arg = va_arg(args, unsigned long int);
    str = convertIntToStr(arg, numberSystem);
  } else if (specific->length_l == 2) {
    unsigned long long int arg = va_arg(args, unsigned long long int);
    str = convertIntToStr(arg, numberSystem);
  } else {
    unsigned int arg = va_arg(args, unsigned int);
    str = convertIntToStr(arg, numberSystem);
  }
  if (str != s21_NULL) {
    char *newStr = s21_NULL;
    formatSpecifier SettingsForPrecision = {0, 0, 1, 0, 0,  specific->precision,
                                            0, 0, 0, 0, 'e'};
    if (specific->specifier == 'o' && specific->isFlagSharp) {
      newStr = s21_insert(str, "0", 0);
      printSpace(newStr, &SettingsForPrecision);
    } else if (specific->specifier == 'p') {
      newStr = s21_insert(str, "0x", 0);
      if (specific->isFlagPlus || specific->isFlagSpace) {
        putSign(newStr, specific, 0);
      }
    } else if (specific->isFlagSharp &&
               (specific->specifier == 'x' || specific->specifier == 'X')) {
      printSpace(str, &SettingsForPrecision);
      newStr = s21_insert(str, "0x", 0);
    }
    if (newStr != s21_NULL) {
      s21_strcpy(result, newStr);
    } else {
      printSpace(str, &SettingsForPrecision);
      s21_strcpy(result, str);
    }
    free(newStr);
  }
  free(str);
}

void write_d(char *result, formatSpecifier *specific, va_list args) {
  char *str = s21_NULL;
  int isNegative = 0;
  if (specific->length_h == 1) {
    short int arg = va_arg(args, int);
    isNegative = arg < 0;
    str = convertIntToStr(arg, 10);
  } else if (specific->length_l == 1) {
    long int arg = va_arg(args, long int);
    isNegative = arg < 0;
    str = convertIntToStr(arg, 10);
  } else if (specific->length_l == 2) {
    long long int arg = va_arg(args, long long int);
    isNegative = arg < 0;
    str = convertIntToStr(arg, 10);
  } else {
    int arg = va_arg(args, int);
    isNegative = arg < 0;
    str = convertIntToStr(arg, 10);
  }
  if (str != s21_NULL) {
    if (specific->precision > 0) {
      formatSpecifier SettingsForPrecision = {
          0, 0, 1, 0, 0, specific->precision, 0, 0, 0, 0, 'd'};
      printSpace(str, &SettingsForPrecision);
    } else if (specific->isFlagZero) {
      specific->width -=
          (specific->isFlagPlus || specific->isFlagSpace || isNegative);
      printSpace(str, specific);
    }
    putSign(str, specific, isNegative);
    s21_strcpy(result, str);
  }
  free(str);
}

// Добавляет сивол + - " "  в зависимости от флагов
void putSign(char *str, formatSpecifier *specific, int isNegative) {
  char *newStr = s21_NULL;
  if (specific->isFlagPlus) {
    newStr = s21_insert(str, isNegative ? "-" : "+", 0);
  } else if (specific->isFlagSpace) {
    newStr = s21_insert(str, isNegative ? "-" : " ", 0);
  } else {
    newStr = s21_insert(str, isNegative ? "-" : "", 0);
  }
  if (newStr != s21_NULL) {
    s21_strcpy(str, newStr);
  }
  free(newStr);
}

void putPeriod(char *str) {
  if (s21_strchr(str, '.') == s21_NULL) {
    int idx = 0;
    getInt(str, &idx);
    char *newStr = s21_insert(str, ".", idx);
    if (newStr != s21_NULL) {
      s21_strcpy(str, newStr);
    }
    free(newStr);
  }
}

char *convertIntToStr(long long int number, int numberSystem) {
  int bufferSize = BUFFER_SIZE / 2;
  char *buffer = calloc(bufferSize, sizeof(char));
  int idx = 0;
  if (number < 0) {
    number *= -1;
  }
  do {
    int remainder = number % numberSystem;
    buffer[idx++] =
        (remainder < 10) ? ('0' + remainder) : ('a' + remainder - 10);
    number /= numberSystem;
  } while (number > 0 && idx < bufferSize - 1);
  buffer[idx] = '\0';

  // Переворачиваем строку в обратном порядке
  int start = 0;
  int end = idx - 1;

  while (start < end) {
    char temp = buffer[start];
    buffer[start] = buffer[end];
    buffer[end] = temp;
    ++start;
    --end;
  }
  return buffer;
}

void write_gG(char *result, formatSpecifier *specific, va_list args) {
  char *str = s21_NULL;
  int isNegative = 0;
  if (specific->length_l == 1) {
    double arg = va_arg(args, double);
    isNegative = arg < 0;
    str = convertDoubleToShortestRepresentationStr(arg, specific->precision);
  } else if (specific->length_l == 2 || specific->length_L == 1) {
    long double arg = va_arg(args, long double);
    isNegative = arg < 0;
    str = convertDoubleToShortestRepresentationStr(arg, specific->precision);
  } else {
    double arg = va_arg(args, double);
    isNegative = arg < 0;
    str = convertDoubleToShortestRepresentationStr(arg, specific->precision);
  }
  if (str != s21_NULL) {
    if (!specific->isFlagSharp) {
      removeEndZeros(str);
    }
    if (specific->isFlagZero) {
      specific->width -=
          (specific->isFlagPlus || specific->isFlagSpace || isNegative);
      printSpace(str, specific);
    }
    putSign(str, specific, isNegative);
    s21_strcpy(result, str);
  }
  free(str);
}

void removeEndZeros(char *str) {
  // Найти позицию точки в строке
  char *dotPosition = s21_strchr(str, '.');
  char *expSymbol = s21_strchr(str, 'e');
  if (expSymbol == s21_NULL) {
    expSymbol = s21_strchr(str, 'E');
  }
  char *exp = s21_NULL;
  if (expSymbol != s21_NULL) {
    s21_size_t lengthToCopy = s21_strlen(expSymbol);
    exp = (char *)calloc(lengthToCopy + 1, sizeof(char));
    s21_strcpy(exp, expSymbol);
    *expSymbol = '\0';
  }
  int length = s21_strlen(str);
  if (dotPosition != s21_NULL) {
    char *lastNonZero = str + length - 1;
    while (lastNonZero > dotPosition &&
           (*lastNonZero == '0' || *lastNonZero == '.')) {
      lastNonZero--;
    }
    if (*lastNonZero == '.') {
      *lastNonZero = '\0';
    } else {
      *(lastNonZero + 1) = '\0';
    }
  }
  if (exp != s21_NULL) {
    s21_strcat(str, exp);
  }
  free(exp);
}

char *convertDoubleToShortestRepresentationStr(long double number,
                                               int precision) {
  int bufferSize = BUFFER_SIZE;
  char *buffer = calloc(bufferSize, sizeof(char));
  int exp = 0;
  scientificNotation(number, &exp);
  char *resultStr = s21_NULL;
  if (exp >= precision || exp < -4) {
    resultStr = convertScientificNotationToStr(number, precision - 1);
  } else {
    if (number < 1 && number > -1 && number != 0) {
      double numberCopy = number;
      numberCopy *= 10;
      int firstNumber = (int)numberCopy % 10;
      numberCopy -= firstNumber;
      while (firstNumber == 0) {
        precision++;
        numberCopy *= 10;
        firstNumber = (int)numberCopy % 10;
        numberCopy -= firstNumber;
      }
    } else {
      char *wholePart = convertDoubleToStr(number, 0);
      int lenWholePart = s21_strlen(wholePart);
      free(wholePart);
      precision = abs(precision - lenWholePart);
    }
    resultStr = convertDoubleToStr(number, precision);
  }
  if (resultStr != s21_NULL) {
    s21_strcpy(buffer, resultStr);
  }
  free(resultStr);
  return buffer;
}

void write_eE(char *result, formatSpecifier *specific, va_list args) {
  char *str = s21_NULL;
  int isNegative = 0;
  if (specific->length_l == 1) {
    double arg = va_arg(args, double);
    isNegative = arg < 0;
    str = convertScientificNotationToStr(arg, specific->precision);
  } else if (specific->length_l == 2 || specific->length_L == 1) {
    long double arg = va_arg(args, long double);
    isNegative = arg < 0;
    str = convertScientificNotationToStr(arg, specific->precision);
  } else {
    double arg = va_arg(args, double);
    isNegative = arg < 0;
    str = convertScientificNotationToStr(arg, specific->precision);
  }
  if (str != s21_NULL) {
    if (specific->isFlagSharp) {
      putPeriod(str);
    }
    if (specific->isFlagZero) {
      specific->width -=
          (specific->isFlagPlus || specific->isFlagSpace || isNegative);
      printSpace(str, specific);
    }
    putSign(str, specific, isNegative);
    s21_strcpy(result, str);
  }
  free(str);
}

char *convertScientificNotationToStr(long double number, int precision) {
  int bufferSize = BUFFER_SIZE;
  char *buffer = calloc(bufferSize, sizeof(char));

  int exp = 0;
  long double numExp = scientificNotation(number, &exp);

  char *numExpStr = convertDoubleToStr(numExp, precision);
  int idx = s21_strlen(numExpStr);
  s21_strcpy(buffer, numExpStr);
  buffer[idx++] = 'e';
  char *expStr = convertIntToStr(exp, 10);
  if (exp < 0) {
    buffer[idx++] = '-';
  } else {
    buffer[idx++] = '+';
  }
  if (abs(exp) < 10) {
    buffer[idx++] = '0';
  }
  s21_strcat(buffer, expStr);
  buffer[idx + s21_strlen(expStr)] = '\0';

  free(numExpStr);
  free(expStr);
  return buffer;
}

long double scientificNotation(long double num, int *exponent) {
  *exponent = 0;

  while (num >= 10.0 || num <= -10.0) {
    num /= 10.0;
    (*exponent)++;
  }

  while (num < 1.0 && num > -1.0 && num != 0) {
    num *= 10.0;
    (*exponent)--;
  }

  return num;
}

int isZeroPrint(formatSpecifier *specific) {
  int flag = 0;
  if (specific->isFlagZero &&
      (specific->specifier == 'e' || specific->specifier == 'E' ||
       specific->specifier == 'f' || specific->specifier == 'g' ||
       specific->specifier == 'G' || specific->specifier == 'c')) {
    flag = 1;
  } else if (specific->isFlagZero && specific->precision == 0) {
    flag = 1;
  }
  return flag;
}

void printSpace(char *result, formatSpecifier *specific) {
  int len = s21_strlen(result);
  int isZero = isZeroPrint(specific) && !specific->isFlagMinus;
  int spaceStrLen = specific->width - len;
  if (spaceStrLen > 0) {
    char spaceStr[spaceStrLen];
    s21_memset(spaceStr, isZero ? '0' : ' ', spaceStrLen);
    spaceStr[spaceStrLen] = '\0';
    if (specific->isFlagMinus) {
      char *res = s21_insert(result, spaceStr, s21_strlen(result));
      if (res != s21_NULL) {
        s21_strcpy(result, res);
      }
      free(res);
    } else {
      char *res = s21_insert(result, spaceStr, 0);
      if (res != s21_NULL) {
        s21_strcpy(result, res);
      }
      free(res);
    }
  }
}

void adjustPrecision(formatSpecifier *specific) {
  if (specific->specifier == 'f' || specific->specifier == 'e' ||
      specific->specifier == 'E') {
    specific->precision = specific->precision == 0 ? 6 : specific->precision;
    specific->precision = specific->precision == -1 ? 0 : specific->precision;
  } else if (specific->specifier == 'g' || specific->specifier == 'G') {
    specific->precision = specific->precision == 0 ? 6 : specific->precision;
    specific->precision = specific->precision == -1 ? 1 : specific->precision;
  } else if (specific->specifier == 's') {
    if (specific->precision == 0) {
      specific->precision = -1;
    } else if (specific->precision == -1) {
      specific->precision = 0;
    }
  }
}

void upperStr(char *str) {
  char *upperStr = s21_to_upper(str);
  s21_strcpy(str, upperStr);
  free(upperStr);
}

// Метод для получения строки из шаблона
char *getStrFromTemplate(formatSpecifier *specific, va_list args) {
  adjustPrecision(specific);
  char *result = calloc(BUFFER_SIZE, sizeof(char));
  switch (specific->specifier) {
    case 'c':
      write_c(result, specific, args);
      break;
    case 's':
      write_s(result, specific, args);
      break;
    case 'd':
      write_d(result, specific, args);
      break;
    case 'e':
      write_eE(result, specific, args);
      break;
    case 'E':
      write_eE(result, specific, args);
      upperStr(result);
      break;
    case 'f':
      write_f(result, specific, args);
      break;
    case 'g':
      write_gG(result, specific, args);
      break;
    case 'G':
      write_gG(result, specific, args);
      upperStr(result);
      break;
    case 'u':
      write_ouxXp(result, specific, args, 10);
      break;
    case 'o':
      write_ouxXp(result, specific, args, 8);
      break;
    case 'x':
      write_ouxXp(result, specific, args, 16);
      break;
    case 'X':
      write_ouxXp(result, specific, args, 16);
      upperStr(result);
      break;
    case 'p':
      specific->length_l = 2;
      specific->length_h = 0;
      write_ouxXp(result, specific, args, 16);
      break;
    case '%':
      s21_strcpy(result, "%");
      break;
  }
  if (specific->specifier != '%') {
    printSpace(result, specific);
  }
  return result != s21_NULL ? result : "";
}

int s21_sprintf(char *str, const char *format, ...) {
  const char *pattern =
      "%[-+ "
      "0#]*([0-9]*|[*])([.]([0-9]*|[*]))?(hl|ll|hh|[hlL])?[diouxXfFeEgGcspn%]";
  Match *matches = s21_NULL;
  s21_size_t numMatches = 0;
  extractMatches(format, pattern, &matches, &numMatches);
  int offset = 0;
  va_list args;
  va_start(args, format);
  for (s21_size_t i = 0; i < numMatches; ++i) {
    s21_strncat(str, format + offset, matches[i].start - offset);
    char template[255] = "";
    s21_memcpy(template, format + matches[i].start,
               matches[i].end - matches[i].start);
    formatSpecifier *specific = initFormatSpecifier(template, args);
    char *result = getStrFromTemplate(specific, args);
    s21_strcat(str, result);
    free(result);
    free(specific);
    offset = matches[i].end;
  }
  s21_strcat(str, format + offset);
  va_end(args);
  free(matches);
  return s21_strlen(str);
}
