/*
    SPDX-FileCopyrightText: 2020-2020 Gustavo Carneiro <gcarneiroa@hotmail.com>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef GIRLFILTERHOTSPOT_H
#define GIRLFILTERHOTSPOT_H

#include "RegExpFilterHotspot.h"

#include <QPoint>
#include <QPointer>
#include <QColor>


namespace Konsole
{
    class GirlFilterHotSpot : public RegExpFilterHotSpot
    {
    public:
        GirlFilterHotSpot(int startLine, int startColumn, int endLine, int endColumn, const QStringList &capturedTexts, const QColor &color);
        ~GirlFilterHotSpot() override = default;

        void mouseEnterEvent(TerminalDisplay *td, QMouseEvent *ev) override;
        void mouseLeaveEvent(TerminalDisplay *td, QMouseEvent *ev) override;

    private:
        void tooltipRequested();

        QColor _color;
        QPoint _toolPos;
        static bool _canGenerateTooltip;
    };
}

#endif
