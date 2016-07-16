#ifndef QMENULISTITEM_H
#define QMENULISTITEM_H

#include <QtCore/QObject>

class QMenuListItem : public QObject {
	Q_OBJECT

	Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
	Q_PROPERTY(QString subtitle READ subtitle WRITE setSubtitle NOTIFY subtitleChanged)
	Q_PROPERTY(QString key  READ key WRITE setKey NOTIFY keyChanged)
	Q_PROPERTY(bool current READ isCurrent WRITE setCurrent NOTIFY currentChanged)
public:
	QMenuListItem(QObject *parent=0);
	QMenuListItem(const QString &title, const QString &subtitle, const QString &key, bool current = false, QObject *parent=0);

	QString title() const;
	void setTitle(const QString &title);

	QString subtitle() const;
	void setSubtitle(const QString &subtitle);

	QString key() const;
	void setKey(const QString &key);
	
	bool isCurrent();
	void setCurrent(bool current);

signals:
	void titleChanged();
	void subtitleChanged();
	void keyChanged();
	void currentChanged();

private:
	QString m_title;
	QString m_subtitle;
	QString m_key;
	bool m_current;
};
#endif // QMENULISTITEM_H
