#include "CommandsWidget.hpp"
#include <iostream>

CommandsWidget::CommandsWidget(QWidget *parent) :
        QWidget(parent),
        network_(lib::network::TcpSession::GetInstance()) {
        connect(&timer_, SIGNAL(timeout()), this, SLOT(SendCommands()));
}

void CommandsWidget::SendCommands() {
    std::cout << "I'm cuming" << std::endl;
}

void CommandsWidget::StopWidget() { timer_.stop(); }

void CommandsWidget::StartWidget() { timer_.start(1); }