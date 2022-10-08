#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMainWindow>
#include <QVector>
extern "C" {
    #include "../calculator.h"
}

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QVector<double> x, y;  // начало прожетка конец помежутка и шаг промежутка и перменная для заполнения вектора


private slots:
    void digits_numbers();
    void on_pushButton_EXIT_clicked();
    void on_pushButton_CA_clicked();
    void on_pushButton_CE_clicked();
    void on_pushButton_equal_clicked();
    void on_pushButton_make_graph_clicked();
};
#endif // MAINWINDOW_H
