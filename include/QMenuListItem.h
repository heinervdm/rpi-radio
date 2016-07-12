#ifndef QMENULISTITEM_H
#define QMENULISTITEM_H

#include <QtCore/QObject>

class QMenuListItem : public QObject {
	Q_OBJECT

	Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
	Q_PROPERTY(QString subtitle READ subtitle WRITE setSubtitle NOTIFY subtitleChanged)
	Q_PROPERTY(QString key  READ key WRITE setKey NOTIFY keyChanged)
public:
	QMenuListItem(QObject *parent=0);
	QMenuListItem(const QString &title, const QString &subtitle, const QString &key, QObject *parent=0);

	QString title() const;
	void setTitle(const QString &title);

	QString subtitle() const;
	void setSubtitle(const QString &subtitle);

	QString key() const;
	void setKey(const QString &key);

signals:
	void titleChanged();
	void subtitleChanged();
	void keyChanged();

private:
	QString m_title;
	QString m_subtitle;
	QString m_key;
};
#endif // QMENULISTITEM_H
