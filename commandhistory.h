#pragma once

#include "ICommand.h"
#include <vector>
#include <memory>
#include <QDebug>

class CommandHistory
{
public:
    CommandHistory() = default;

    void ExecuteCommand(std::unique_ptr<ICommand> cmd);
    void Undo();

private:
    std::vector<std::unique_ptr<ICommand>> m_history;
};
