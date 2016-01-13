#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#ifdef GREATERQT
#include <QDialog>
#else
#include <QtGui/QDialog>
#endif

namespace Ui {
    class AboutDialog;
}

class AboutDialog : public QDialog {
    Q_OBJECT
public:
    AboutDialog(QWidget *parent = 0);
    ~AboutDialog();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::AboutDialog *m_ui;
};

#endif // ABOUTDIALOG_H
