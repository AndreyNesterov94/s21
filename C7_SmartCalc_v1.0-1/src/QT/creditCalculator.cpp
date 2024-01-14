#include "creditCalculator.h"

#include "ui_creditCalculator.h"

CreditCalculator::CreditCalculator(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::CreditCalculator) {
  ui->setupUi(this);

  connect(ui->creditCalcButton, &QPushButton::clicked, this,
          &CreditCalculator::onButtonClickedCalculate);
  connect(ui->cleanCreditButton, &QPushButton::clicked, this,
          &CreditCalculator::onButtonClickedClean);
}

CreditCalculator::~CreditCalculator() { delete ui; }

void CreditCalculator::onButtonClickedCalculate() {
  double principal = ui->sumSpinBox->value();
  double interestRate = ui->percentSpinBox->value();
  int months = (int)ui->termSpinBox->value();
  double totalPayment = NAN;
  if (ui->autonomousRadioButton->isChecked()) {
    totalPayment = calculateAnnuityLoan(principal, interestRate, months);
  } else if (ui->differentiatedRadioButton->isChecked() && principal > 0 &&
             interestRate > 0 && months > 0) {
    totalPayment = calculateDifferentiatedLoan(principal, interestRate, months);
  }
  if (!isnan(totalPayment)) {
    ui->monthlyPayLineEdit->setText(
        QString::number(totalPayment / months, 'f', 2));
    ui->overpaymentLineEdit->setText(
        QString::number(totalPayment - principal, 'f', 2));
    ui->paymentLineEdit->setText(QString::number(totalPayment, 'f', 2));
  } else {
    ui->monthlyPayLineEdit->setText("0");
    ui->overpaymentLineEdit->setText("0");
    ui->paymentLineEdit->setText("0");
  }
}

void CreditCalculator::onButtonClickedClean() {
  ui->sumSpinBox->setValue(0);
  ui->percentSpinBox->setValue(0);
  ui->termSpinBox->setValue(0);

  ui->monthlyPayLineEdit->setText("0");
  ui->overpaymentLineEdit->setText("0");
  ui->paymentLineEdit->setText("0");
}
