#include "commandhistory.h"

//CommandHistory::CommandHistory() {}

void CommandHistory::ExecuteCommand(std::unique_ptr<ICommand> cmd)
{
    cmd->Execute();
    m_history.push_back(std::move(cmd));

    qDebug() << "Текущий размер истории:" << m_history.size();
}

void CommandHistory::Undo()
{
    m_history.back()->Undo();
    m_history.pop_back();
}
