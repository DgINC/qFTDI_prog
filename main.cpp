#include "mainwindow.h"
#include <QApplication>

using namespace std;
using namespace Ftdi;

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    if ( getuid() != 0 ){
        w.msgBox.setText("Root privileges are required for running.");
        w.msgBox.exec();
        a.quit();
        return EXIT_FAILURE;
    }

    return a.exec();
}

void MainWindow::getAllDevices() {
    int ret;
    struct ftdi_context ftdictx;
    struct ftdi_device_list *devlist;
    QMap<ftdi_context*, libusb_device*> ftdi_list;

    if((ret = ftdi_init(&ftdictx)) < 0) {
        error_Handler(ftdi_get_error_string(&ftdictx), ret, ERRR);
        ftdi_free(&ftdictx);
    }

    if ((ret = ftdi_usb_find_all(&ftdictx, &devlist, 0, 0)) <= 0) {
        if(ret == 0) {
            error_Handler((char *)"No device found!", 0, INFO);
        } else {
            error_Handler(ftdi_get_error_string(&ftdictx), ret, ERRR);
        }
        ftdi_list_free(&devlist);
        ftdi_free(&ftdictx);
    } else {
        for (; devlist != 0; devlist = devlist->next) {
            if ((ret = ftdi_usb_open_dev(&ftdictx, devlist->dev)) < 0) {
                error_Handler(ftdi_get_error_string(&ftdictx), ret, ERRR);
                ftdi_free(&ftdictx);
            }

            ftdi_list.insertMulti(&ftdictx, devlist->dev);

            if ((ret = ftdi_usb_close(&ftdictx)) < 0) {
                error_Handler(ftdi_get_error_string(&ftdictx), ret, ERRR);
                ftdi_free(&ftdictx);
            }
        }
        setupTree(&ftdi_list);
    }
}

void MainWindow::getDevInfo(ftdi_context *ftdictx, libusb_device *usbdev) {

}
