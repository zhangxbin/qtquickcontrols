/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the Qt Components project.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QTMLMENU_H
#define QTMLMENU_H
#include <QtCore/qglobal.h>
#include <QtWidgets/qmenu.h>
#if QT_VERSION < 0x050000
#include <QtDeclarative/qdeclarative.h>
#include <QtDeclarative/QDeclarativeListProperty>
#else
#include <QtQuick/QtQuick>
#include <QtQml/QtQml>
#endif
#include <QtCore/qabstractitemmodel.h>
#include <QtCore/QVariant>
#include "qtmenuitem.h"

class QtMenu : public QtMenuBase
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText)
    Q_PROPERTY(QVariant model READ model WRITE setModel NOTIFY modelChanged)
    Q_PROPERTY(int selectedIndex READ selectedIndex WRITE setSelectedIndex NOTIFY selectedIndexChanged)
    Q_PROPERTY(int hoveredIndex READ hoveredIndex WRITE setHoveredIndex NOTIFY hoveredIndexChanged)
#if QT_VERSION < 0x050000
    Q_PROPERTY(QDeclarativeListProperty<QtMenuBase> menuItems READ menuItems)
#else
    Q_PROPERTY(QQmlListProperty<QtMenuBase> menuItems READ menuItems)
#endif
    Q_CLASSINFO("DefaultProperty", "menuItems")
public:
    QtMenu(QQuickItem *parent = 0);
    virtual ~QtMenu();

    void setText(const QString &text);
    QString text() const;

    int selectedIndex() const { return m_selectedIndex; }
    void setSelectedIndex(int index);
    int hoveredIndex() const { return m_highlightedIndex; }
    void setHoveredIndex(int index);

#if QT_VERSION < 0x050000
    QDeclarativeListProperty<QtMenuBase> menuItems();
#else
    QQmlListProperty<QtMenuBase> menuItems();
#endif
    QMenu* qmenu() { return m_qmenu; }

    QAction* action();

    Q_INVOKABLE int minimumWidth() const { return m_qmenu->minimumWidth(); }
    Q_INVOKABLE void setMinimumWidth(int w) { m_qmenu->setMinimumWidth(w); }
    Q_INVOKABLE void showPopup(qreal x, qreal y, int atActionIndex = -1);
    Q_INVOKABLE void hidePopup();
    Q_INVOKABLE void clearMenuItems();
    Q_INVOKABLE void addMenuItem(const QString &text);
    Q_INVOKABLE QString itemTextAt(int index) const;
    Q_INVOKABLE QString modelTextAt(int index) const;
    Q_INVOKABLE int modelCount() const;

    QVariant model() const { return m_model; }
    Q_INVOKABLE bool hasNativeModel() const { return m_hasNativeModel; }

public slots:
    void setModel(const QVariant &newModel);

public:
Q_SIGNALS:
    void menuClosed();
    void selectedIndexChanged();
    void hoveredIndexChanged();
    void modelChanged(const QVariant &newModel);
    void rebuldMenu();

private Q_SLOTS:
    void emitSelected();
    void emitHovered();

private:
#if QT_VERSION < 0x050000
    static void append_qmenuItem(QDeclarativeListProperty<QtMenuBase> *list, QtMenuBase *menuItem);
#else
    static void append_qmenuItem(QQmlListProperty<QtMenuBase> *list, QtMenuBase *menuItem);
#endif
private:
    QWidget *dummy;
    QMenu *m_qmenu;
    QList<QtMenuBase *> m_qmenuItems;
    int m_selectedIndex;
    int m_highlightedIndex;
    bool m_hasNativeModel;
    QVariant m_model;
};

QML_DECLARE_TYPE(QtMenu)

#endif // QTMLMENU_H