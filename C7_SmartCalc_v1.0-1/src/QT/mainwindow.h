#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <math.h>

#include <QMainWindow>

#include "creditCalculator.h"
#include "depositCalculator.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

#ifdef __cplusplus

extern "C" {
#endif

#include "../s21_calculate.h"
#include "../s21_helpers.h"

#ifdef __cplusplus
}
#endif

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void onButtonClickedCalculate();
  void onButtonClickedASimpleObject();
  void onButtonClickedDifficultObject();
  void onButtonClickedClean();
  void onButtonClickedAMoveObject();
  void onButtonClickedBuildGraph();
  void onButtonClickedGraphClean();

  void onButtonClickedCreditCalcOpen();
  void onButtonClickedDepositCalcOpen();

 private:
  CreditCalculator *creditCalc;
  DepositCalculator *depositCalc;
  Ui::MainWindow *ui;
};
#endif  // MAINWINDOW_H
