#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QTreeWidget>
#include <QStatusBar>
#include <QMessageBox>
#include <QDebug>
#include <QtWidgets>

#include <ftdi.hpp>
#include <libusb.h>
#include <unistd.h>
#include <sys/types.h>

#include "main.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

protected:
    void showEvent(QShowEvent *ev);
    int hotplug_callback(struct libusb_context *ctx, struct libusb_device *dev, libusb_hotplug_event event, void *user_data);

public:
    explicit MainWindow(QWidget *parent = 0);
    QMessageBox msgBox;
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void getAllDevices();

    void on_treeWidget_itemActivated(QTreeWidgetItem *item, int column);

signals:
      void window_loaded();

private:
    Ui::MainWindow *ui;
    QLabel *statusLabel;
    void setupTree(QMap<ftdi_context *, libusb_device *> *all_ftdi);
    void error_Handler(char* mesg, int errnum, error_layer el);
};

#endif // MAINWINDOW_H
