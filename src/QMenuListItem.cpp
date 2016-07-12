#include "QMenuListItem.h"

QMenuListItem::QMenuListItem(QObject *p)
    : QObject(p)
{
}

QMenuListItem::QMenuListItem(const QString &t, const QString &st, const QString &k, QObject *p)
    : QObject(p), m_title(t), m_subtitle(st), m_key(k)
{
}

QString QMenuListItem::title() const
{
    return m_title;
}

void QMenuListItem::setTitle(const QString &t)
{
    if (t != m_title) {
        m_title = t;
        emit titleChanged();
    }
}

QString QMenuListItem::subtitle() const
{
    return m_subtitle;
}

void QMenuListItem::setSubtitle(const QString &st)
{
    if (st != m_subtitle) {
        m_subtitle = st;
        emit subtitleChanged();
    }
}

QString QMenuListItem::key() const
{
    return m_key;
}

void QMenuListItem::setKey(const QString &k)
{
    if (k != m_key) {
        m_key = k;
        emit keyChanged();
    }
}
