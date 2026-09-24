#include "commandhistory.h"

//CommandHistory::CommandHistory() {}

void CommandHistory::ExecuteCommand(std::unique_ptr<ICommand> cmd)
{
    cmd->Execute();
    m_history.push_back(std::move(cmd));
    CleanRedo();

    qDebug() << "Текущий размер истории:" << m_history.size();
}

void CommandHistory::Undo()
{
    if (m_history.empty()) return;

    m_history.back()->Undo();
    m_redoHistory.push_back(std::move(m_history.back()));
    m_history.pop_back();

    if (m_redoHistory.size() > 10)
    {
        m_redoHistory.erase(m_redoHistory.begin());
    }
}

void CommandHistory::Redo()
{
    if (m_redoHistory.empty()) return;

    m_redoHistory.back()->Redo();
    m_history.push_back(std::move(m_redoHistory.back()));
    m_redoHistory.pop_back();
}

void CommandHistory::CleanRedo()
{
    if (m_redoHistory.empty()) return;

    m_redoHistory.clear();
}
