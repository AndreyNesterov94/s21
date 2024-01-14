#ifndef DEPOSIT_CALC_WINDOW_H
#define DEPOSIT_CALC_WINDOW_H

#include <math.h>

#include <QMainWindow>
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui {
class DepositCalculator;
}
QT_END_NAMESPACE

#ifdef __cplusplus

extern "C" {
#endif

#include "../s21_calculate.h"

#ifdef __cplusplus
}
#endif

class DepositCalculator : public QMainWindow {
  Q_OBJECT

 public:
  DepositCalculator(QWidget *parent = nullptr);
  ~DepositCalculator();

 private slots:
  void onButtonClickedCalculate();
  void onButtonClickedClean();
  void onButtonClickedCleanTable();
  void onButtonClickedAddEntry();

 private:
  Ui::DepositCalculator *ui;
  void parseTable(QVector<QVector<double>> &data);
  double **convertToDoubleArray(const QVector<QVector<double>> &data);
};
#endif  // DEPOSIT_CALC_WINDOW_H
