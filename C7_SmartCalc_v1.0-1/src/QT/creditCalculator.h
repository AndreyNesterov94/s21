#ifndef CREDIT_CALC_WINDOW_H
#define CREDIT_CALC_WINDOW_H

#include <math.h>

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class CreditCalculator;
}
QT_END_NAMESPACE

#ifdef __cplusplus

extern "C" {
#endif

#include "../s21_calculate.h"

#ifdef __cplusplus
}
#endif

class CreditCalculator : public QMainWindow {
  Q_OBJECT

 public:
  CreditCalculator(QWidget *parent = nullptr);
  ~CreditCalculator();

 private slots:
  void onButtonClickedCalculate();
  void onButtonClickedClean();

 private:
  Ui::CreditCalculator *ui;
};
#endif  // CREDIT_CALC_WINDOW_H
