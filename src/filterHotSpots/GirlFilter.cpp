/*
    SPDX-FileCopyrightText: 2020-2020 Gustavo Carneiro <gcarneiroa@hotmail.com>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "GirlFilter.h"

using namespace Konsole;

// #include "GirlFilterHotSpot.h"
#include "session/Session.h"
#include "session/SessionManager.h"
#include "FileFilterHotspot.h"


// This matches:
//   - an RGB-style string (e.g., #3e3, #feed) delimited by non-alphanumerics;
//   - or, a sequence of ASCII characters (e.g., foobar, Aquamarine, TOMATO).
const QRegularExpression GirlFilter::GirlRegExp(
    QStringLiteral("unicorn"));

GirlFilter::GirlFilter(Session *session):
    _session(session)
{
    setRegExp(GirlRegExp);
}

QSharedPointer<HotSpot> GirlFilter::newHotSpot(int startLine, int startColumn, int endLine,
                                                int endColumn, const QStringList &capturedTexts)
{

    // QColor color(255, 0, 0, 127);

    // if (!color.isValid()) {
        // return nullptr;
    // }

    // return QSharedPointer<HotSpot>(
        // new GirlFilterHotSpot(startLine, startColumn, endLine, endColumn, capturedTexts, color));

    return QSharedPointer<HotSpot>(new FileFilterHotSpot(startLine, startColumn, endLine, endColumn, capturedTexts,
                                QStringLiteral("/home/lyj/x240s/unicorn/98c27142d2709a45833e1a9837db10e78839c239.jpg@518w.webp"),
                                                         _session));

}
