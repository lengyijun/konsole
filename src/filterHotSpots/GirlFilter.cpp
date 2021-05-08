/*
    SPDX-FileCopyrightText: 2020-2020 Gustavo Carneiro <gcarneiroa@hotmail.com>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "GirlFilter.h"

using namespace Konsole;

#include "GirlFilterHotSpot.h"


// This matches:
//   - an RGB-style string (e.g., #3e3, #feed) delimited by non-alphanumerics;
//   - or, a sequence of ASCII characters (e.g., foobar, Aquamarine, TOMATO).
const QRegularExpression GirlFilter::GirlRegExp(
    QStringLiteral("unicorn"));

GirlFilter::GirlFilter()
{
    setRegExp(GirlRegExp);
}

QSharedPointer<HotSpot> GirlFilter::newHotSpot(int startLine, int startColumn, int endLine,
                                                int endColumn, const QStringList &capturedTexts)
{
    QColor color(255, 0, 0, 127);

    // Make sure we've actually matched a color.
    if (!color.isValid()) {
        return nullptr;
    }

    return QSharedPointer<HotSpot>(
        new GirlFilterHotSpot(startLine, startColumn, endLine, endColumn, capturedTexts, color));
}
