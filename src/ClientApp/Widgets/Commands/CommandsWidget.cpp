#include "CommandsWidget.hpp"

Commands::Commands() : network_(lib::network::TcpSession::GetInstance()){

    connect(&timer_, SIGNAL(timeout()), this, SLOT(SendCommand()));

    timer_.start(1);
}

void Commands::SendCommands() {}
