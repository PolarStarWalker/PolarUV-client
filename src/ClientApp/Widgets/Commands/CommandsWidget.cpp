#include "Gamepad.hpp"
#include <iostream>

CommandsWidget::CommandsWidget(QWidget *parent, WidgetResources &resources) :
        QWidget(parent),
        resources_(resources) {
    connect(&timer_, SIGNAL(timeout()), this, SLOT(SendCommands()));
}

void CommandsWidget::SendCommands() {
    CommandsStruct commands{};

    std::string_view data((char *) &commands, sizeof(commands));

    auto response = resources_.Network.SendRequest(data, lib::network::Request::TypeEnum::WR, 3);

    telemetry_ = *((Telemetry *) response.Data.data());

    std::cout << "X: " << telemetry_.Rotation[Telemetry::X]
              << ", Y: " << telemetry_.Rotation[Telemetry::Y]
              << ", Z: " << telemetry_.Rotation[Telemetry::Z]
              << std::endl;

}

void CommandsWidget::StopWidget() { timer_.stop(); }

void CommandsWidget::StartWidget() { timer_.start(1); }