#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <iostream>
#include <QFileDialog>
#include <QDebug>
#include  <QFile>
#include <QMessageBox>
#include <QShortcut>
#include <QKeySequence>
QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    QFile file;
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_btnopen_clicked();

    void on_btnSave_clicked();

    void on_btnclose_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
