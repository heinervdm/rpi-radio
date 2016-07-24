#ifndef MPDPLAYERWIDGET_H
#define MPDPLAYERWIDGET_H

#include <QDeclarativeView>
#include <QDeclarativeProperty>

#include <QMpdClient>

class MpdPlayerWidget : public QDeclarativeView {
	Q_OBJECT

public:
	MpdPlayerWidget();
	~MpdPlayerWidget();

private:
	QMpdClient *mpd;
	QString currentPath;
	QDeclarativeProperty *qmlState;
	bool connected;

private slots:
	void onMpdInitialized();
	void setVolume(int v);
	void stateChanged();
	void populateMenu();
	void populatePlaylist();
	void onMenuItemSelected(QString key, QString name);
	void onSongChanged(const QMpdSong& song);
	void onMpdStatusChanged(const QMpdStatus::State state);
	void onPlayStopClicked();
	void onPlaylistClearClicked();
};

#endif // MPDPLAYERWIDGET_H
