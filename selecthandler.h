#pragma once

#include <QMouseEvent>
#include "iviewportcontext.h"

class SelectHandler
{
private:
    IViewportContext* m_cntx = nullptr;

public:
    SelectHandler(IViewportContext* cntx) : m_cntx(cntx) {};

    void OnMousePress(QMouseEvent* e)
    {
        if (!e || !m_cntx) return;

        if (e->button() == Qt::LeftButton)
        {
            auto picked = m_cntx->PickObject(e->pos());
            m_cntx->SetPickedObject(picked);
        }
    }
};

