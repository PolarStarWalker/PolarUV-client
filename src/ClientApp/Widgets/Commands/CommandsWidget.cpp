#include "Gamepad.hpp"

CommandsWidget::CommandsWidget(QWidget *parent, WidgetResources &resources) :
        QWidget(parent),
        resources_(resources) {
    connect(&timer_, SIGNAL(timeout()), this, SLOT(SendCommands()));
}

void CommandsWidget::SendCommands() {
    CommandsStruct commands{};

    auto response = resources_.Network.SendRequest(commands, lib::network::Request::TypeEnum::W, 3);

}

void CommandsWidget::StopWidget() { timer_.stop(); }

void CommandsWidget::StartWidget() { timer_.start(1); }