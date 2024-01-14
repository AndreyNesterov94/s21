#include "s21_helpers.h"

// Функция для создания двумерного массива строк
char **s21_createStringArray(int len) {
  // Выделение памяти для массива указателей
  char **array = (char **)calloc(len, sizeof(char *));
  if (array == NULL) {
    // Обработка ошибки выделения памяти
    return NULL;
  }

  // Выделение памяти для каждой строки в массиве
  for (int i = 0; i < len; i++) {
    array[i] = (char *)calloc((BUFFER_SIZE + 1), sizeof(char));
  }

  return array;
}

// Функция для освобождения памяти, выделенной под двумерный массив строк
void s21_freeStringArray(char **array, int len) {
  // Освобождение каждой строки в массиве
  for (int i = 0; i < len; i++) {
    free(array[i]);
  }
  // Освобождение самого массива
  free(array);
}

// Функция для подсчета количества вхождений символа в строку, пропуская повторы
int s21_getCountChar(const char *str, char ch) {
  int count = 1;
  int isLastCharMatch = 1;

  for (size_t i = 0; i < strlen(str); i++) {
    if (str[i] == ch) {
      if (!isLastCharMatch) {
        count++;
      }
      isLastCharMatch = 1;
    } else {
      isLastCharMatch = 0;
    }
  }
  return count - isLastCharMatch;
}

// Функция для проверки, является ли строка операцией
int s21_isOperator(const char *token) {
  int result = 0;
  const char *moveSet[MOVE_SET_LEN] = {MOVE_SET};
  for (int i = 0; i < MOVE_SET_LEN; ++i) {
    if (strcmp(token, moveSet[i]) == 0) {
      result = 1;
      break;  // Если нашли соответствие, дополнительные проверки не нужны
    }
  }
  return result;
}

// Функция для получения приоритета операции
int s21_getPrecedence(const char *operation) {
  int priority = 3;  // По умолчанию - для функций
  if (strcmp(operation, "+") == 0 || strcmp(operation, "-") == 0 ||
      strcmp(operation, "~") == 0) {
    priority = 1;
  } else if (strcmp(operation, "(") == 0 || strcmp(operation, ")") == 0) {
    priority = MAX_PRIORITY;
  } else if (strcmp(operation, "*") == 0 || strcmp(operation, "/") == 0 ||
             strcmp(operation, "mod") == 0) {
    priority = 2;
  }
  return priority;
}

// Проверяет, является ли оператор бинарным
int s21_isBinaryOperator(const char *operation) {
  int result = 0;
  const char *moveSet[BINARY_MOVE_SET_LEN] = {BINARY_MOVE_SET};
  for (int i = 0; i < BINARY_MOVE_SET_LEN; ++i) {
    if (strcmp(operation, moveSet[i]) == 0) {
      result = 1;
      break;  // Если нашли соответствие, дополнительные проверки не нужны
    }
  }
  return result;
}

// Проверяет, является ли строка числом
int s21_isNumber(char *str) {
  int length = strlen(str);
  int dotCount = 0;
  int flag = 1;

  if (length == 0) {
    return 0;
  }

  for (int i = 0; i < length; i++) {
    if (!flag) {
      break;
    }
    char c = str[i];

    if (!(c >= '0' && c <= '9')) {
      if (c == '.') {
        dotCount++;
        if (dotCount > 1) {
          flag = 0;
        }
      } else {
        flag = 0;
      }
    }
  }

  return flag;
}

// Добавление пробелов вокруг операторов
char *s21_addSpacesToOperations(const char *input) {
  const char *moveSet[MOVE_SET_LEN] = {MOVE_SET};
  char *output = calloc(BUFFER_SIZE * 3 + 1, sizeof(char));

  if (!output) {
    return NULL;  // Не удалось выделить память
  } else {
    const char *currentPosition = input;

    while (*currentPosition != '\0') {
      int found = 0;
      for (int i = 0; i < MOVE_SET_LEN; i++) {
        const char *move = moveSet[i];
        int moveLen = strlen(move);
        if (strncmp(currentPosition, move, moveLen) == 0) {
          // Добавление пробела перед и после оператора
          strcat(output, " ");
          strncat(output, currentPosition, moveLen);
          strcat(output, " ");
          currentPosition += moveLen;
          found = 1;
          break;
        }
      }

      if (!found) {
        int len = strlen(output);
        output[len] = *currentPosition;
        output[len + 1] = '\0';
        currentPosition++;
      }
    }
  }
  return output;
}

// Получение списка токенов из выражения
char **s21_getTokensList(const char *example, int *outputCount) {
  char *exampleAddSpace = s21_addSpacesToOperations(example);
  *outputCount = s21_getCountChar(exampleAddSpace, ' ');
  char **output = NULL;

  if (*outputCount > 0) {
    output = s21_createStringArray(*outputCount);
    char *lex = strtok(exampleAddSpace, " ");
    int idx = 0;

    while (lex != NULL) {
      strcpy(output[idx++], lex);
      lex = strtok(NULL, " ");
    }
  }

  free(exampleAddSpace);
  return output;
}

// Преобразование в обратную польскую запись (RPN)
char **s21_convertToRPN(char **tokens, int count, int *outputCount) {
  char **output = s21_createStringArray(count);
  char **stack = s21_createStringArray(count);
  int outPos = 0, stackPos = -1;
  char lastToken[BUFFER_SIZE] = "(";

  for (int i = 0; i < count; i++) {
    char currentToken[BUFFER_SIZE] = "";
    strcpy(currentToken, tokens[i]);

    if (s21_isOperator(currentToken)) {
      if (strcmp(currentToken, ")") == 0) {
        // Перенос операторов из стека в выходную строку до открывающей скобки
        while (stackPos > -1 && strcmp(stack[stackPos], "(") != 0) {
          strcpy(output[outPos++], stack[stackPos--]);
        }

        if (stackPos > -1) {
          stackPos--;
        }
      } else {
        // Обработка операторов в зависимости от приоритета
        while (stackPos > -1 &&
               s21_getPrecedence(stack[stackPos]) != MAX_PRIORITY &&
               (s21_getPrecedence(stack[stackPos]) >
                    s21_getPrecedence(currentToken) ||
                (s21_getPrecedence(stack[stackPos]) ==
                     s21_getPrecedence(currentToken) &&
                 s21_isBinaryOperator(currentToken)))) {
          strcpy(output[outPos++], stack[stackPos--]);
        }

        // Обработка унарного минуса
        if (strcmp(currentToken, "-") == 0 && strcmp(lastToken, "(") == 0) {
          strcpy(currentToken, "~");
        } else if (strcmp(currentToken, "+") == 0 &&
                   strcmp(lastToken, "(") == 0) {
          continue;  // Обработка унарного минуса - игнорирование
        }

        strcpy(stack[++stackPos], currentToken);
      }
    } else {
      // Перенос операндов в выходную строку
      strcpy(output[outPos++], currentToken);
    }

    strcpy(lastToken, currentToken);
  }

  // Перенос оставшихся операторов из стека в выходную строку
  while (stackPos > -1) {
    strcpy(output[outPos++], stack[stackPos--]);
  }

  // Освобождение памяти стека
  s21_freeStringArray(stack, count);

  *outputCount = outPos;
  return output;
}
