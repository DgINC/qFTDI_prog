#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QTreeWidget>
#include <QStatusBar>
#include <QMessageBox>
#include <QDebug>
#include <QtWidgets>
#include <QMetaType>

#include <ftdi.hpp>
#include <libusb.h>
#include <unistd.h>
#include <sys/types.h>

using namespace std;
using namespace Ftdi;

namespace Ui {
class MainWindow;
}

Q_DECLARE_METATYPE(Context*)

class MainWindow : public QMainWindow {
    Q_OBJECT

protected:
    void showEvent(QShowEvent *ev);
    //int hotplug_callback(struct libusb_context *ctx, struct libusb_device *dev, libusb_hotplug_event event, void *user_data);

public:
    explicit MainWindow(QWidget *parent = 0);
    QMessageBox msgBox;
    ~MainWindow();

    template<typename T>
    const T& convert(const T& v)
    {
       return v;
    }

    QString convert(const std::string& s);

private slots:
    void on_pushButton_clicked();
    void Initialization();

    void on_treeWidget_itemClicked(QTreeWidgetItem *item);

signals:
      void window_loaded();

private:
    Ui::MainWindow *ui;
    QLabel *statusLabel;

    enum error_layer {
        DEBG = 0,
        INFO = 1,
        WARN = 2,
        ERRR = 3,
        CRIT = 4
    };

    void getAllDevices(const int vid = 0,const int pid = 0);
    void setupTree(QMap<QString, Context *> *all_ftdi);
    void error_Handler(const char *mesg, int errnum, error_layer el);
    void getDevPins(Context* ctx);
};

#endif // MAINWINDOW_H
