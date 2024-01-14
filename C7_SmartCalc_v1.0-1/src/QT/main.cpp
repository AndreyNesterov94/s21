#include <QApplication>

#include "mainwindow.h"

/**
 * @brief Entry point
 *
 * Execution of the program
 * starts here.
 *
 * @param argc Number of arguments
 * @param argv List of arguments
 *
 * @return Program exit status
 */
int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow w;
  w.setFixedSize(w.width(), w.height());
  w.show();
  return a.exec();
}
