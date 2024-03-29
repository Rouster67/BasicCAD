#ifndef PROCESSING_H
#define PROCESSING_H

#include <QDialog>

namespace Ui {
class Processing;
}

class Processing : public QDialog
{
    Q_OBJECT

public:
    explicit Processing(QWidget *parent = nullptr);
    ~Processing();

private slots:
    void on_OKButton_clicked();

private:
    Ui::Processing *ui;
};

#endif // PROCESSING_H
