#include "CommandsWidget.hpp"
#include <iostream>

CommandsWidget::CommandsWidget(QWidget *parent, WidgetResources& resources) :
        QWidget(parent),
        resources_(resources) {
        connect(&timer_, SIGNAL(timeout()), this, SLOT(SendCommands()));
}

void CommandsWidget::SendCommands() {
    std::cout << "I'm sending" << std::endl;
}

void CommandsWidget::StopWidget() { timer_.stop(); }

void CommandsWidget::StartWidget() { timer_.start(1); }