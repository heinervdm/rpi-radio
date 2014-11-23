#include "PlayerWidget.h"

#include <QGraphicsItem>
#include <QDeclarativeContext>
#include <QDeclarativeItem>
#include <QUrl>
#include <QEventLoop>
#include <QNetworkAccessManager>
#include <QNetworkReply>

#include "StationObject.h"
#include "QmlControl.h"

#ifdef HAVE_QT4
#include <phonon/MediaSource>
#endif

PlayerWidget::PlayerWidget() {
	qmlRegisterType<QmlControl>("QmlControl", 1, 0, "Control");

	QList<QObject *> stations;
	stations.append( new StationObject( "1LIVE", "http://1live.akacast.akamaistream.net/7/706/119434/v1/gnl.akacast.akamaistream.net/1live", "http://www.einslive.de/codebase/img/content/1Live_Logo.jpg"));
	stations.append( new StationObject( "1LIVE diggi",  "http://1live-diggi.akacast.akamaistream.net/7/965/119435/v1/gnl.akacast.akamaistream.net/1live-diggi",  "https://upload.wikimedia.org/wikipedia/commons/4/4d/1LIVE_diggi.svg"));
	stations.append( new StationObject( "89.0 RTL",  "http://mp3.89.0rtl.de:80/",  "http://www.89.0rtl.de/sites/default/files/insight_logo.png"));
	stations.append( new StationObject( "B5 Aktuell",  "http://streams.br-online.de/b5aktuell_2.m3u",  "http://www.br.de/ressourcen/bilder/programmfahne_mit_logo/b5-aktuell-wellenlogo-102~_v-image256_-a42a29b6703dc477fd0848bc845b8be5c48c1667.jpg?version=24c68"));
	stations.append( new StationObject( "Bayern 1",  "http://streams.br-online.de/bayern1_2.m3u",  "http://www.br.de/ressourcen/bilder/programmfahne_mit_logo/b1-wellenlogo100~_v-image256_-a42a29b6703dc477fd0848bc845b8be5c48c1667.jpg?version=b7e7a"));
	stations.append( new StationObject( "Bayern 3",  "http://streams.br-online.de/bayern3_2.m3u",  "http://www.br.de/ressourcen/bilder/programmfahne_mit_logo/b3-wellenlogo100~_v-image256_-a42a29b6703dc477fd0848bc845b8be5c48c1667.png?version=ef9aa"));
	stations.append( new StationObject( "bigFM",  "http://srv05.bigstreams.de/bigfm-mp3-96",  "http://static.bigfm.de/content/pictures/tpl/bigfm.png"));
	stations.append( new StationObject( "Blackbeats.FM",  "http://blackbeats.fm/listen.m3u",  "http://blackbeats.fm/images/logo.png"));
	stations.append( new StationObject( "Bremen Eins",  "http://httpmedia.radiobremen.de/bremeneins.m3u",  "https://upload.wikimedia.org/wikipedia/de/archive/0/0f/20071003205401!Bremeneins-logo.svg"));
	stations.append( new StationObject( "Bremen Vier",  "http://httpmedia.radiobremen.de/bremenvier.m3u",  "http://www.radiobremen.de/bremenvier/_px/logo.png"));
	stations.append( new StationObject( "BR Puls",  "http://streams.br-online.de/jugend-radio_2.m3u",  "http://www.br.de/ressourcen/bilder/programmfahne_mit_logo/bayern-plus-wellenlogo100~_v-image256_-a42a29b6703dc477fd0848bc845b8be5c48c1667.jpg?version=c233f"));
	stations.append( new StationObject( "Dasding",  "http://mp3-live.dasding.de/dasding_m.m3u",  "http://www.dasding.de/-/id=434098/property=detail/m6io9h/index.jpg"));
	stations.append( new StationObject( "delta radio",  "http://streams.deltaradio.de/delta-live/mp3-128/wwwchipde",  "http://www.deltaradio.de/images/DELTA/logo.png"));
	stations.append( new StationObject( "Deluxe Lounge Radio",  "http://deluxetelevision.com/livestreams/radio/DELUXE_LOUNGE_RADIO.pls",  ""));
	stations.append( new StationObject( "detektor.fm",  "http://detektor.fm/stream/mp3/musik/",  "https://upload.wikimedia.org/wikipedia/de/1/1c/Detektor.fm_Logo.svg"));
	stations.append( new StationObject( "Deutschlandfunk",  "http://www.dradio.de/streaming/dlf.m3u",  "http://www.deutschlandradio.de/media/files/1/1a471d2a0586a7aec12cd3199d4b675fv2.png"));
	stations.append( new StationObject( "Deutschlandradio Kultur",  "http://www.dradio.de/streaming/dkultur.m3u",  "http://www.akamus.de/media/pictures/pressemeldung/109_gross.jpg"));
	stations.append( new StationObject( "DRadio Wissen",  "http://www.dradio.de/streaming/dradiowissen.m3u",  "https://pbs.twimg.com/profile_images/447027816685514752/HhR1qOCF.jpeg"));
	stations.append( new StationObject( "egoFM",  "http://edge.live.mp3.mdn.newmedia.nacamar.net/ps-egofm_128/livestream.mp3",  "http://www.egofm.de/templates/egofm/img/logo.png"));
	stations.append( new StationObject( "Electro Radio",  "http://www.electroradio.ch/stream.wpl",  "http://www.electroradio.ch/images/electroradio_logo_200.png"));
	stations.append( new StationObject( "Energy Berlin",  "http://energyradio.de/berlin",  "http://static3.energy.de/fileadmin/images/layout/ci/logo/logo_121_140_on_brightground.png.pagespeed.ce.HUJqn3wPEa.png"));
	stations.append( new StationObject( "Energy Bremen",  "http://energyradio.de/bremen",  "http://static3.energy.de/fileadmin/images/layout/ci/logo/logo_121_140_on_brightground.png.pagespeed.ce.HUJqn3wPEa.png"));
	stations.append( new StationObject( "Energy Hamburg",  "http://energyradio.de/hamburg",  "http://static3.energy.de/fileadmin/images/layout/ci/logo/logo_121_140_on_brightground.png.pagespeed.ce.HUJqn3wPEa.png"));
	stations.append( new StationObject( "Energy München",  "http://www.energyradio.de/muenchen",  "http://static3.energy.de/fileadmin/images/layout/ci/logo/logo_121_140_on_brightground.png.pagespeed.ce.HUJqn3wPEa.png"));
	stations.append( new StationObject( "Energy Stuttgart",  "http://energyradio.de/stuttgart",  "http://static3.energy.de/fileadmin/images/layout/ci/logo/logo_121_140_on_brightground.png.pagespeed.ce.HUJqn3wPEa.png"));
	stations.append( new StationObject( "ffn",  "http://player.ffn.de/tunein_ffn.pls",  "http://www.ffn.de/fileadmin/templates/img/ffn_logo.jpg"));
	stations.append( new StationObject( "FM4",  "http://mp3stream1.apasf.apa.at:8000/listen.pls",  "http://fm4.orf.at/v2static/images/fm4_logo.jpg"));
	stations.append( new StationObject( "Fritz",  "http://www.fritz.de/live.m3u",  "https://upload.wikimedia.org/wikipedia/de/thumb/3/3b/Rbb-fritz-logo.svg/602px-Rbb-fritz-logo.svg.png"));
	stations.append( new StationObject( "Hit-Radio Antenne",  "http://stream.antenne.com/hra-nds/mp3-128/IMDADevice/",  "http://cdn.antenne.com/static/img/ant-logo-004.png"));
	stations.append( new StationObject( "Hit Radio FFH",  "http://streams.ffh.de/radioffh/mp3/hqlivestream.m3u",  "http://static.ffh.de/fileadmin/templates/www.ffh.de/images/logo.png"));
	stations.append( new StationObject( "hr3",  "http://metafiles.gl-systemhaus.de/hr/hr3_1.asx",  "https://upload.wikimedia.org/wikipedia/de/thumb/4/4b/HR4.svg/567px-HR4.svg.png"));
	stations.append( new StationObject( "Kiss FM",  "http://stream.kissfm.de/kissfm/mp3-128/internetradio/",  "http://static.kissfm.de/images/logo.png"));
	stations.append( new StationObject( "Klassik Radio",  "http://edge.live.mp3.mdn.newmedia.nacamar.net/klassikradio128/livestream.mp3",  ""));
	stations.append( new StationObject( "MDR Jump",  "http://www.jumpradio.de/static/webchannel/jump_live_channel_high.m3u",  "http://www.jumpradio.de/service/kontakt/logi100_v-modIndexStandard_zc-fc76ae11.jpg?version=30207"));
	stations.append( new StationObject( "N-JOY",  "http://ndrstream.ic.llnwd.net/stream/ndrstream_n-joy_hi_mp3",  "http://www.n-joy.de/resources/images/logo.png"));
	stations.append( new StationObject( "NDR2",  "http://ndrstream.ic.llnwd.net/stream/ndrstream_ndr2_hi_mp3",  "https://upload.wikimedia.org/wikipedia/commons/thumb/c/ce/NDR_2_logo.svg/250px-NDR_2_logo.svg.png"));
	stations.append( new StationObject( "Oldie 95",  "http://mp3.oldie95.c.nmdn.net/oldie95/livestream80.mp3",  ""));
	stations.append( new StationObject( "Ostseewelle Hit-Radio",  "http://edge.live.mp3.mdn.newmedia.nacamar.net/ostseewellelive/livestream.mp3",  "http://www.ostseewelle.de/wp-content/themes/sight/images/logo.png"));
	stations.append( new StationObject( "Planet Radio",  "http://streams.planetradio.de/planetradio/mp3/hqlivestream.m3u",  "http://static.planetradio.de/fileadmin/templates/www.planetradio.de/images/logo.png"));
	stations.append( new StationObject( "R.SH",  "http://streams.rsh.de/rsh-live/mp3-128/wwwchipde",  "http://www.rsh.de/images/RSH/logo.png"));
	stations.append( new StationObject( "radioeins",  "http://www.radioeins.de/live.m3u",  "https://upload.wikimedia.org/wikipedia/de/6/6f/RBB_Radio_Eins_alt_Logo.svg"));
	stations.append( new StationObject( "Radio Gong 96,3",  "http://www.radiogong.de/live/high_q.m3u",  "http://www.radiogong.de/sites/default/files/insight_logo.png"));
	stations.append( new StationObject( "Radio Hamburg",  "http://mp3.radiohamburg.c.nmdn.net/radiohamburg/livestream192.mp3",  "http://www.radiohamburg.de/var/data/titelanzeige/default-radiohh-100x66.jpg"));
	stations.append( new StationObject( "Rock Antenne",  "http://www.rockantenne.de/webradio/rockantenne.m3u",  "http://www.rockantenne.de/imda/logos/600x600/ROCK-ANTENNE.png"));
	stations.append( new StationObject( "RPR1", "http://rpr1.fmstreams.de/stream8", "http://static.rpr1.de/content/pictures/tpl/rpr1-logo.png"));
	stations.append( new StationObject( "SWR1",  "http://mp3-live.swr.de/swr1bw_m.m3u",  "https://upload.wikimedia.org/wikipedia/de/3/38/SWR1_Logo_alt.svg"));
	stations.append( new StationObject( "SWR3",  "http://mp3-live.swr3.de/swr3_m.m3u",  "http://www.swr3.de/-/id=404778/property=thumbnail/width=260/height=156/pubVersion=15/1ygku8j/index.jpg"));
	stations.append( new StationObject( "Top 100 Station",  "http://www.top100station.de/switch/r3472.pls",  ""));
	stations.append( new StationObject( "UnserDing",  "http://streaming01.sr-online.de/unserding_1.m3u",  "https://upload.wikimedia.org/wikipedia/de/f/f5/UnserDing.svg"));
	stations.append( new StationObject( "WDR 2",  "http://www.wdr.de/wdrlive/media/wdr2.m3u",  "https://pbs.twimg.com/profile_images/2572773571/i5kwksvuf5tkncio6lwn_400x400.png"));
	stations.append( new StationObject( "WDR 4",  "http://www.wdr.de/wdrlive/media/wdr4.m3u",  "http://www.wdr.de/radio/wdr4/_m/images/misc/wdr4_logo.png"));
	stations.append( new StationObject( "You FM",  "http://metafiles.gl-systemhaus.de/hr/youfm_2.m3u",  "http://www.you-fm.de/images/logo-youfm-3.jpg"));
	rootContext()->setContextProperty("stationModel", QVariant::fromValue(stations));

	// 	setWindowFlags(Qt::FramelessWindowHint);
	setSource(QUrl("qrc:/qml/Player.qml"));
// 	setWindowState(Qt::WindowFullScreen);
#ifdef HAVE_QT5
	player = new QMediaPlayer;
// 	connect(player, SIGNAL(currentMediaChanged(QMediaContent)), this, SLOT(mediaDataChanged(QMediaContent)));
#else
	music = new Phonon::MediaObject(this);
	audioOutput = new Phonon::AudioOutput(Phonon::MusicCategory, this);
	Phonon::Path path = Phonon::createPath(music, audioOutput);
	connect(music, SIGNAL(metaDataChanged()), this, SLOT(metaDataChanged()));
	connect(music, SIGNAL(stateChanged(Phonon::State, Phonon::State)), this, SLOT(musicStateChanged(Phonon::State, Phonon::State)));
#endif
	connect(rootObject(), SIGNAL(playClicked()), this, SLOT(playPressed()));
	connect(rootObject(), SIGNAL(stationChanged(QString, QString, QString)), this, SLOT(stationSelected(QString, QString, QString)));

// 	rootContext()->setContextProperty("width", 320);
// 	rootContext()->setContextProperty("height",240);
}

PlayerWidget::~PlayerWidget() {
}

void PlayerWidget::playPressed() {
	if (!rootObject()->property("playing").toBool()) {
#ifdef HAVE_QT5
		player->play();
#else
		music->play();
#endif
	} else {
#ifdef HAVE_QT5
		player->stop();
#else
		music->stop();
#endif
	}
}

void PlayerWidget::stationSelected(QString name, QString url, QString /*cover*/) {
	QUrl u = QUrl(url);
#ifdef HAVE_QT5
	QNetworkRequest req = QNetworkRequest(u);
	player->setMedia(u);
#else
	if (url.endsWith(".pls") || url.endsWith(".m3u")) u = urlFromPlaylist(u);
	music->setCurrentSource(Phonon::MediaSource(u));
	rootObject()->setProperty("name", QVariant(name));
	rootObject()->setProperty("title", QVariant(""));
	rootObject()->setProperty("subtitle", QVariant(""));
#endif
}

#ifdef HAVE_QT5
void PlayerWidget::mediaDataChanged(const QMediaContent& media) {
	
}
#else
void PlayerWidget::metaDataChanged() {
	QStringList artist = music->metaData(Phonon::ArtistMetaData);
	QStringList title = music->metaData(Phonon::TitleMetaData);

	if (artist.count() > 0) {
		rootObject()->setProperty("title", QVariant(artist.first()));
	}
	else {
		rootObject()->setProperty("title", QVariant(""));
	}
	if (title.count() > 0) {
		rootObject()->setProperty("subtitle", QVariant(title.first()));
	}
	else {
		rootObject()->setProperty("subtitle", QVariant(""));
	}
}

void PlayerWidget::musicStateChanged(Phonon::State neu, Phonon::State) {
	if (neu == Phonon::StoppedState) {
		rootObject()->setProperty("playing", QVariant(false));
	}
	else if (neu == Phonon::PlayingState) {
		rootObject()->setProperty("playing", QVariant(true));
	}
}
#endif

void PlayerWidget::volumeChanged(int v) {
	rootObject()->setProperty("volume",QVariant(v));
#ifdef HAVE_QT4
	audioOutput->setVolume(1.0 * v / 100.0);
#endif
}

void PlayerWidget::selectionChanged(int field) {
	QString state = rootObject()->property("state").toString();
	if (state == "PLAYER") {
		rootObject()->setProperty("selected", QVariant((field % 4 + 4) % 4));
	} else if (state == "CLOCK") {
		rootObject()->setProperty("state", QVariant("PLAYER"));
	} else if (state == "STATIONLIST") {
		if (field > lastSelection) {
			QVariant returnedValue;
			QMetaObject::invokeMethod(rootObject(), "prevStation", Q_RETURN_ARG(QVariant, returnedValue));
		} else if (field < lastSelection) {
			QVariant returnedValue;
			QMetaObject::invokeMethod(rootObject(), "nextStation", Q_RETURN_ARG(QVariant, returnedValue));
		}
	} else {
		qDebug("Application in unknown state!");
	}
	lastState = state;
	lastSelection = field;
}

void PlayerWidget::select() {
	QVariant returnedValue;
	QMetaObject::invokeMethod(rootObject(), "click", Q_RETURN_ARG(QVariant, returnedValue));
}

QUrl PlayerWidget::urlFromPlaylist(QUrl url) {
	QUrl ret;
	// create custom temporary event loop on stack
	QEventLoop eventLoop;

	// "quit()" the event-loop, when the network request "finished()"
	QNetworkAccessManager mgr;
	QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

	// the HTTP request
	QNetworkRequest req( url);
	QNetworkReply *reply = mgr.get(req);
	eventLoop.exec(); // blocks stack until "finished()" has been called

	if (reply->error() == QNetworkReply::NoError) {
		QString strReply = (QString)reply->readAll();
		if (strReply.contains("[playlist]")) {
			// .pls
			QRegExp regexp("\bFile\\d+=(.*)\b");
			if (regexp.indexIn(strReply) != -1) {
				ret.setUrl(regexp.cap(1));
			}
		} else {
			// .m3u
			ret.setUrl(strReply.split('\n').at(0));
		}
	}
	else {
		qDebug() << "Failure" <<reply->errorString();
	}
	delete reply;
	return ret;
}
