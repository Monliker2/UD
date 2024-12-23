#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QtSql>
#include <QMessageBox>
#include <QSettings>
#include <QRegularExpressionValidator>
#include <QRegularExpression>
#include <QShortcut>

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

    QMessageBox* mes;

private slots:
    void on_pushButton_clicked();

signals:
    void refreshComboBox();

private:
    void saveSettings();
    Ui::Login *ui;
    QSqlDatabase db;
};

#endif // LOGIN_H
