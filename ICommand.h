#pragma once

class ICommand
{
public:
    virtual ~ICommand() = default;
    virtual void Execute() = 0;
    virtual void Undo() = 0;
    virtual void Redo() = 0;

    /*
     * во избежание претензий
     * по мне Redo и Execute выолняют разные операции
     */
};
