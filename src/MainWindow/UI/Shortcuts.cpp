#include "../MainWindow.hpp"
#include "../ui_mainwindow.h"

void MainWindow::setupShortcuts() {
    this->_keyEsc = new QShortcut(Qt::Key_Escape, this, SLOT(shortcutEsc()));
    this->_keyTab = new QShortcut(Qt::Key_Tab, this, SLOT(shortcutTab()));
    this->_keyF11 = new QShortcut(Qt::Key_F11, this, SLOT(shortcutF11()));
    this->_keyB = new QShortcut(Qt::Key_B, this, SLOT(shortcutB()));
}

void MainWindow::shortcutEsc() {
    if (this->windowState() == Qt::WindowFullScreen) {
        this->setWindowState(Qt::WindowNoState);
    }
}

void MainWindow::shortcutTab() {
    if (ui->TabWidget->currentIndex() < ui->TabWidget->count() - 1) {
        ui->TabWidget->setCurrentIndex(ui->TabWidget->currentIndex() + 1);
    } else {
        ui->TabWidget->setCurrentIndex(0);
    }
}

void MainWindow::shortcutF11() {
    if (this->windowState() == Qt::WindowFullScreen) {
        this->setWindowState(Qt::WindowNoState);
    } else {
        this->setWindowState(Qt::WindowFullScreen);
    }
}

void MainWindow::shortcutB() {
    if (ui->TabWidget->tabBar()->isVisible()) {
        ui->TabWidget->tabBar()->hide();
        ui->FullScreenButton->hide();
        ui->HideTabBarButton->hide();
        ui->CommandsProtocolButton->hide();
        ui->ShowTabBarButton->show();
    } else {
        ui->TabWidget->tabBar()->show();
        ui->FullScreenButton->show();
        ui->HideTabBarButton->show();
        ui->CommandsProtocolButton->show();
        ui->ShowTabBarButton->hide();
    }
}

