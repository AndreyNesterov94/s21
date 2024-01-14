#include "depositCalculator.h"

#include <iostream>

#include "ui_depositCalculator.h"
DepositCalculator::DepositCalculator(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::DepositCalculator) {
  ui->setupUi(this);

  connect(ui->depositCalcButton, &QPushButton::clicked, this,
          &DepositCalculator::onButtonClickedCalculate);
  connect(ui->depositCleanButton, &QPushButton::clicked, this,
          &DepositCalculator::onButtonClickedClean);
  connect(ui->depositTableClenaButton, &QPushButton::clicked, this,
          &DepositCalculator::onButtonClickedCleanTable);
  connect(ui->addEntryButton, &QPushButton::clicked, this,
          &DepositCalculator::onButtonClickedAddEntry);
}

DepositCalculator::~DepositCalculator() { delete ui; }

void DepositCalculator::parseTable(QVector<QVector<double>>& data) {
  int rowCount = ui->depositsTableWidget->rowCount();
  for (int row = 0; row < rowCount; row++) {
    double replenishment = 0.0;
    double withdrawal = 0.0;
    if (ui->depositsTableWidget->item(row, 1) != nullptr) {
      replenishment = ui->depositsTableWidget->item(row, 1)->text().toDouble();
    }

    if (ui->depositsTableWidget->item(row, 2) != nullptr) {
      withdrawal = ui->depositsTableWidget->item(row, 2)->text().toDouble();
    }
    double priceChange = replenishment - withdrawal;

    QStringList monthStrList = {};
    if (ui->depositsTableWidget->item(row, 0) != nullptr) {
      monthStrList = ui->depositsTableWidget->item(row, 0)->text().split('-');
    }

    if (monthStrList.length() == 1) {
      QVector<double> rowData;
      int month = 0;
      if (monthStrList[0] != nullptr) {
        month = monthStrList[0].toInt();
      }
      rowData.push_back(month);
      rowData.push_back(priceChange);
      data.push_back(rowData);
    } else if (monthStrList.length() == 2) {
      QVector<double> rowData;
      int start = 0;
      int end = 0;
      if (monthStrList[1] != nullptr) {
        end = monthStrList[1].toInt();
      }
      if (monthStrList[0] != nullptr) {
        start = monthStrList[0].toInt();
      }
      if (start != 0 && start <= end) {
        for (; start <= end; start++) {
          QVector<double> rowData;
          rowData.push_back(start);
          rowData.push_back(priceChange);
          data.push_back(rowData);
        }
      }
    }
  }
}

double** DepositCalculator::convertToDoubleArray(
    const QVector<QVector<double>>& data) {
  int rowCount = data.size();
  int colCount = (rowCount > 0) ? data[0].size() : 0;

  double** doubleArray = new double*[rowCount];
  for (int i = 0; i < rowCount; ++i) {
    doubleArray[i] = new double[colCount];
    for (int j = 0; j < colCount; ++j) {
      doubleArray[i][j] = data[i][j];
    }
  }

  return doubleArray;
}

void DepositCalculator::onButtonClickedCalculate() {
  QVector<QVector<double>> data;
  parseTable(data);
  double** doubleArrayData = convertToDoubleArray(data);
  double totalCapitalization = 0.0;
  double accruedInterest = 0.0;

  double percentTax = ui->percentTaxSpinBox->value() / 100;

  double depositAmount = ui->sumSpinBox->value();
  int term = ui->termSpinBox->value();
  double percents = ui->percentSpinBox->value();
  // Периодичнось выплат
  int idxFrequency = ui->frequencyListWidget->currentRow();
  if (idxFrequency < 0 || idxFrequency > 7) {
    idxFrequency = 2;
  }
  ui->frequencyListWidget->setCurrentRow(idxFrequency);
  double frequency[] = {1,
                        7,
                        DAYS_IN_MONTH,
                        DAYS_IN_MONTH * 3,
                        DAYS_IN_MONTH * 6,
                        DAYS_IN_MONTH * 12,
                        ui->termSpinBox->value() * DAYS_IN_MONTH};

  int capitalization = ui->capitalizationCheckBox->isChecked();
  int code = calculateDeposit(
      depositAmount, term, percents, frequency[idxFrequency], capitalization,
      doubleArrayData, data.size(), &totalCapitalization, &accruedInterest);

  if (code == 0) {
    ui->totalAmountLineEdit->setText(
        QString::number(totalCapitalization, 'f', 2));
    double amountTax =
        (accruedInterest - ui->amoutWithoutTaxSpinBox->value()) * percentTax;
    if (amountTax > 0) {
      ui->totalPercenttLineEdit->setText(
          QString::number(accruedInterest - amountTax, 'f', 2));
      ui->totalTaxLineEdit->setText(QString::number(amountTax));
    } else {
      ui->totalPercenttLineEdit->setText(
          QString::number(accruedInterest, 'f', 2));
      ui->totalTaxLineEdit->setText("0");
    }
  } else {
    ui->totalAmountLineEdit->setText("0");
    ui->totalPercenttLineEdit->setText("0");
    ui->totalTaxLineEdit->setText("0");
  }
}

void DepositCalculator::onButtonClickedClean() {
  ui->sumSpinBox->setValue(0);
  ui->termSpinBox->setValue(0);
  ui->percentSpinBox->setValue(0);
  ui->percentTaxSpinBox->setValue(0);
  ui->frequencyListWidget->setCurrentRow(2);
  ui->capitalizationCheckBox->setChecked(false);
  ui->depositsTableWidget->clearContents();
  ui->depositsTableWidget->setRowCount(0);
  ui->totalAmountLineEdit->setText("0");
  ui->totalPercenttLineEdit->setText("0");
  ui->totalTaxLineEdit->setText("0");
}

void DepositCalculator::onButtonClickedCleanTable() {
  ui->depositsTableWidget->clearContents();
  ui->depositsTableWidget->setRowCount(0);
}

void DepositCalculator::onButtonClickedAddEntry() {
  ui->depositsTableWidget->insertRow(ui->depositsTableWidget->rowCount());
}
