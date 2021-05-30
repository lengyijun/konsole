/*
    SPDX-FileCopyrightText: 2020-2020 Gustavo Carneiro <gcarneiroa@hotmail.com>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "GirlFilter.h"

using namespace Konsole;

#include "session/Session.h"
#include "session/SessionManager.h"
#include "FileFilterHotspot.h"
#include <QDir>


// This matches:
//   - an RGB-style string (e.g., #3e3, #feed) delimited by non-alphanumerics;
//   - or, a sequence of ASCII characters (e.g., foobar, Aquamarine, TOMATO).
const QRegularExpression GirlFilter::GirlRegExp(
    QStringLiteral("(spur|unicorn)"));

GirlFilter::GirlFilter(Session *session):
    _session(session)
{
    setRegExp(GirlRegExp);
}

QSharedPointer<HotSpot> GirlFilter::newHotSpot(int startLine, int startColumn, int endLine,
                                                int endColumn, const QStringList &capturedTexts)
{

    if(capturedTexts.at(0)==QStringLiteral("spur")){
        return QSharedPointer<HotSpot>(new FileFilterHotSpot(startLine, startColumn, endLine, endColumn, capturedTexts,
                                        QStringLiteral("/home/lyj/.local/spur.jpg"),
                                         _session));
    }

    QString dir=QStringLiteral("/home/lyj/.local/unicorn/img/");
    QDir directory(dir);
    QStringList images = directory.entryList(QStringList() << QStringLiteral("*.webp") << QStringLiteral("*.png"),QDir::Files);

    int index=rand()%images.size();


    return QSharedPointer<HotSpot>(new FileFilterHotSpot(startLine, startColumn, endLine, endColumn, capturedTexts,
                                   dir+ images.at(index),
                                     _session));

}
