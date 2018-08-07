#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_quit_clicked();

    void on_select_file_clicked();

    void show_time();

    void on_grey_scale_clicked();

    void on_bright_clicked();

    void on_properties_clicked();

    void on_select_file_pressed();

    void on_original_clicked();


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
