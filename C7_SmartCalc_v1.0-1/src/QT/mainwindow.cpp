#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->historyLineEdit->setText("");
  // Очищение уравнения
  connect(ui->cleanButton, &QPushButton::clicked, this,
          &MainWindow::onButtonClickedClean);
  // Цифры
  connect(ui->numberButton_0, &QPushButton::clicked, this,
          &MainWindow::onButtonClickedASimpleObject);
  connect(ui->numberButton_1, &QPushButton::clicked, this,
          &MainWindow::onButtonClickedASimpleObject);
  connect(ui->numberButton_2, &QPushButton::clicked, this,
          &MainWindow::onButtonClickedASimpleObject);
  connect(ui->numberButton_3, &QPushButton::clicked, this,
          &MainWindow::onButtonClickedASimpleObject);
  connect(ui->numberButton_4, &QPushButton::clicked, this,
          &MainWindow::onButtonClickedASimpleObject);
  connect(ui->numberButton_5, &QPushButton::clicked, this,
          &MainWindow::onButtonClickedASimpleObject);
  connect(ui->numberButton_6, &QPushButton::clicked, this,
          &MainWindow::onButtonClickedASimpleObject);
  connect(ui->numberButton_7, &QPushButton::clicked, this,
          &MainWindow::onButtonClickedASimpleObject);
  connect(ui->numberButton_8, &QPushButton::clicked, this,
          &MainWindow::onButtonClickedASimpleObject);
  connect(ui->numberButton_9, &QPushButton::clicked, this,
          &MainWindow::onButtonClickedASimpleObject);
  connect(ui->paramButton_x, &QPushButton::clicked, this,
          &MainWindow::onButtonClickedASimpleObject);
  connect(ui->moveButton_comma, &QPushButton::clicked, this,
          &MainWindow::onButtonClickedASimpleObject);
  // Простые действия (Которые не требуют скобочки после себя)
  connect(ui->moveButton_minus, &QPushButton::clicked, this,
          &MainWindow::onButtonClickedAMoveObject);
  connect(ui->moveButton_plus, &QPushButton::clicked, this,
          &MainWindow::onButtonClickedAMoveObject);
  connect(ui->moveButton_div, &QPushButton::clicked, this,
          &MainWindow::onButtonClickedAMoveObject);
  connect(ui->moveButton_mul, &QPushButton::clicked, this,
          &MainWindow::onButtonClickedAMoveObject);
  connect(ui->moveButton_mod, &QPushButton::clicked, this,
          &MainWindow::onButtonClickedAMoveObject);
  connect(ui->moveButton_pow, &QPushButton::clicked, this,
          &MainWindow::onButtonClickedAMoveObject);
  connect(ui->parenthesisButton_open, &QPushButton::clicked, this,
          &MainWindow::onButtonClickedASimpleObject);
  connect(ui->parenthesisButton_close, &QPushButton::clicked, this,
          &MainWindow::onButtonClickedASimpleObject);
  // Сложные действия (Которые требуют скобочки после себя)
  connect(ui->moveButton_log, &QPushButton::clicked, this,
          &MainWindow::onButtonClickedDifficultObject);
  connect(ui->moveButton_ln, &QPushButton::clicked, this,
          &MainWindow::onButtonClickedDifficultObject);
  connect(ui->moveButton_cos, &QPushButton::clicked, this,
          &MainWindow::onButtonClickedDifficultObject);
  connect(ui->moveButton_acos, &QPushButton::clicked, this,
          &MainWindow::onButtonClickedDifficultObject);
  connect(ui->moveButton_sin, &QPushButton::clicked, this,
          &MainWindow::onButtonClickedDifficultObject);
  connect(ui->moveButton_asin, &QPushButton::clicked, this,
          &MainWindow::onButtonClickedDifficultObject);
  connect(ui->moveButton_tan, &QPushButton::clicked, this,
          &MainWindow::onButtonClickedDifficultObject);
  connect(ui->moveButton_atan, &QPushButton::clicked, this,
          &MainWindow::onButtonClickedDifficultObject);
  connect(ui->moveButton_sqrt, &QPushButton::clicked, this,
          &MainWindow::onButtonClickedDifficultObject);

  // Вычисление примера
  connect(ui->calculateButton, &QPushButton::clicked, this,
          &MainWindow::onButtonClickedCalculate);

  // Построение графика
  connect(ui->graphButton, &QPushButton::clicked, this,
          &MainWindow::onButtonClickedBuildGraph);
  connect(ui->graphCleanButton, &QPushButton::clicked, this,
          &MainWindow::onButtonClickedGraphClean);

  // Отркытие калькуляторов
  connect(ui->creditCalcOpenButton, &QPushButton::clicked, this,
          &MainWindow::onButtonClickedCreditCalcOpen);
  connect(ui->depositCalcOpenButton, &QPushButton::clicked, this,
          &MainWindow::onButtonClickedDepositCalcOpen);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::onButtonClickedASimpleObject() {
  QPushButton *button = qobject_cast<QPushButton *>(sender());
  if (button) {
    QString buttonText = button->text();
    ui->equationLineEdit->insert(buttonText);
  }
}

void MainWindow::onButtonClickedAMoveObject() {
  QPushButton *button = qobject_cast<QPushButton *>(sender());
  if (button) {
    QString buttonText = button->text();
    ui->equationLineEdit->insert(" " + buttonText + " ");
  }
}

void MainWindow::onButtonClickedDifficultObject() {
  QPushButton *button = qobject_cast<QPushButton *>(sender());
  if (button) {
    QString buttonText = button->text();
    ui->equationLineEdit->insert(buttonText + "(");
  }
}
void MainWindow::onButtonClickedClean() { ui->equationLineEdit->setText(""); }
// Вычисление примера
void MainWindow::onButtonClickedCalculate() {
  const char *example = ui->equationLineEdit->text().toStdString().c_str();
  ui->historyLineEdit->setText(ui->equationLineEdit->text());
  double param = ui->xValueSpinBox->value();
  double result = s21_calculate(example, param);
  if (isnan(result)) {
    ui->historyLineEdit->setText("Ошибка");
  } else {
    ui->equationLineEdit->setText(QString::number(result));
  }
}
// Построение графика
void MainWindow::onButtonClickedBuildGraph() {
  // Получаем максимальные и минимальные значения осей
  double x_min = ui->minXSpinBox->value();
  double x_max = ui->maxXSpinBox->value();
  double y_min = ui->minYSpinBox->value();
  double y_max = ui->maxYSpinBox->value();
  if (x_min < x_max && y_min < y_max) {
    // шаг
    double h = (x_max - x_min) / 250;
    QVector<double> x, y;  // Массивы координат точек

    // собираем все точки
    for (double X = x_min; X <= x_max; X += h) {
      x.push_back(X);
      const char *example = ui->equationLineEdit->text().toStdString().c_str();
      y.push_back(s21_calculate(example, X));
    }

    // добавляем один график в widget
    ui->graph_frame->addGraph();

    // говорим, что отрисовать нужно график по нашим двум массивам x и y
    ui->graph_frame->graph(0)->setData(x, y);

    // устанавливаем область, которая будет показываться на графике
    ui->graph_frame->xAxis->setRange(x_min, x_max);
    ui->graph_frame->yAxis->setRange(y_min, y_max);

    // задаем возможность зумировать график
    ui->graph_frame->setInteraction(QCP::iRangeZoom, true);
    ui->graph_frame->setInteraction(QCP::iRangeDrag, true);

    // задаем цвет точки и толщину линии
    ui->graph_frame->graph(0)->setPen(QColor(61, 82, 62, 255));
    QPen graphPen = ui->graph_frame->graph(0)->pen();
    graphPen.setWidth(2);
    ui->graph_frame->graph(0)->setPen(graphPen);

    // перерисуем график на нашем graph_frame
    ui->graph_frame->replot();
  } else {
    QMessageBox msgBox;
    msgBox.setStyleSheet("background-color: black; color: white;");
    msgBox.setText("Недопустимое значение осей функции");
    msgBox.setWindowTitle("Ошибка");
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.exec();
  }
}

void MainWindow::onButtonClickedGraphClean() {
  for (int g = 0; g < ui->graph_frame->graphCount(); g++) {
    ui->graph_frame->graph(g)->data().data()->clear();
  }
  ui->graph_frame->clearGraphs();
  ui->graph_frame->replot();
}

void MainWindow::onButtonClickedCreditCalcOpen() {
  creditCalc = new CreditCalculator(this);
  creditCalc->setFixedSize(creditCalc->width(), creditCalc->height());
  creditCalc->show();
}

void MainWindow::onButtonClickedDepositCalcOpen() {
  depositCalc = new DepositCalculator(this);
  depositCalc->setFixedSize(depositCalc->width(), depositCalc->height());
  depositCalc->show();
}
