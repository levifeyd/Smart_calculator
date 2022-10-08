#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton_0,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_1,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_3,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_4,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_5,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_6,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_7,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_8,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_9,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_sum,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_sub,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_mul,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_div,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_rightbracket,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_leftbracket,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_sin,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_cos,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_tan,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_dot,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_asin,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_acos,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_atan,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_mod,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_ln,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_log,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_pow,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_sqrt,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_x,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_make_graph,SIGNAL(clicked()),this,SLOT(on_pushButton_make_graph_clicked()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digits_numbers()
{
    QPushButton *button = (QPushButton *)sender();  //метод возваращает кнопку push_button и преобразуем к классу Qush
    ui->result_show->setText(ui->result_show->toPlainText() + button->text());
}

void MainWindow::on_pushButton_EXIT_clicked()
{
    QApplication::quit();
}


void MainWindow::on_pushButton_CA_clicked()
{
    ui->result_show->clear();
}


void MainWindow::on_pushButton_CE_clicked()
{
    QString str = ui->result_show->toPlainText();
    str.resize(str.size()-1);
    ui->result_show->setText(str);
}


void MainWindow::on_pushButton_equal_clicked()
{
   QString str = ui->result_show->toPlainText();
   if (str.contains("(-")) {
       str.replace("(-","(0-");
   }
   if (str.contains("mod")) {
       str.replace("mod","%");
   }

   QByteArray ba = str.toLocal8Bit();

   char* str2 = ba.data();
   double res = 0;
   int parser_res = 0;

   parser_res = startuem(str2, &res);

   if (parser_res != 18) {
    QString toStr = QString::number(res);
    ui->result_show->setText(toStr);
   } else {
       ui->result_show->setText("ERROR");
       QMessageBox::critical(this,"Заголовок", "Некорректные данные");
       ui->result_show->clear();
   }




}

void MainWindow::on_pushButton_make_graph_clicked()
{

        x.clear();
        y.clear();
        QString str = ui->result_show->toPlainText();
        if (!str.contains("x")) {
            ui->label->setText("expression doesn't contain x");
        } else {
            int Xmin = ui->spinBox_2->value();
            int Xmax = ui->spinBox->value();;
            double step = 0.005 * (qFabs(Xmin) + qFabs(Xmax));
            double Y;
            double X = (double)Xmin;
            double Ymin = 0;
            double Ymax = 0;

            while (X < (double)Xmax) {
                x.push_back(X);
                str = ui->result_show->toPlainText();
                X = X * 10000;
                X = (double)(qRound(X));
                X = X / 10000;
               if (X < 0.0) {
                   str.replace("x", "(0" + QString::number(X, 'g', 10) + ")");
                } else {
                    str.replace("x", "(" + QString::number(X, 'g', 10) + ")");
                }
                QByteArray ba = str.toLocal8Bit();
                char* char_array = ba.data();
                startuem(char_array, &Y);
                if (X == Xmin) {
                   Ymin = Y;
                   Ymax = Y;
                }
                if (Y < Ymin) Ymin = Y;
                if (Y > Ymax) Ymax = Y;
                y.push_back(Y);
                X += step;
            }

            ui->widget->addGraph();
            ui->widget->graph(0)->data()->clear();
            ui->widget->graph(0)->addData(x,y);
            ui->widget->xAxis->setRange(Xmin, Xmax);
            ui->widget->yAxis->setRange(Ymin, Ymax);
            ui->widget->replot();
        }
}


