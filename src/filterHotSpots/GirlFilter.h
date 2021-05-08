/*
    SPDX-FileCopyrightText: 2020-2020 Gustavo Carneiro <gcarneiroa@hotmail.com>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef GIRLFILTER_H
#define GIRLFILTER_H

#include "RegExpFilter.h"

namespace Konsole
{
    class GirlFilter : public RegExpFilter
    {
    public:
        GirlFilter();

        static const QRegularExpression GirlRegExp;

    protected:
        QSharedPointer<HotSpot> newHotSpot(int startLine, int startColumn, int endLine,
                                           int endColumn, const QStringList &capturedTexts) override;
    };
}

#endif
