#include "PlayerWidget.h"

#include <QGraphicsItem>
#include <QQmlContext>
#include <QQuickItem>
#include <QNetworkRequest>
#include <QUrl>

#include "StationObject.h"
#include "QmlControl.h"
#include "StationModel.h"

PlayerWidget::PlayerWidget() {
	qmlRegisterType<QmlControl>("QmlControl", 1, 0, "Control");
	qmlRegisterType<StationModel>("StationModel",1,0,"StationModel");
	// 	setWindowFlags(Qt::FramelessWindowHint);
	setSource(QUrl("qrc:/qml/Player.qml"));
// 	setWindowState(Qt::WindowFullScreen);
	player = new QMediaPlayer;
	connect(rootObject(), SIGNAL(playClicked()), this, SLOT(playPressed()));
	connect(rootObject(), SIGNAL(stationChanged(QString, QString, QString)), this, SLOT(stationSelected(QString, QString, QString)));
	connect(player, SIGNAL(currentMediaChanged(QMediaContent)), this, SLOT(mediaDataChanged(QMediaContent)));

	StationModel stations;
	stations.addStation(StationObject( "1.FM Chillout Lounge", "http://tcl.1.fm/tcl128k?MSWMExt=.asf", ""));
	stations.addStation(StationObject( "1LIVE", "http://1live.akacast.akamaistream.net/7/706/119434/v1/gnl.akacast.akamaistream.net/1live", "http://www.einslive.de/codebase/img/content/1Live_Logo.jpg"));
	stations.addStation(StationObject( "1LIVE diggi",  "http://1live-diggi.akacast.akamaistream.net/7/965/119435/v1/gnl.akacast.akamaistream.net/1live-diggi",  "http://www.einslive.de/codebase/img/content/1Live_Logo.jpg"));
	stations.addStation(StationObject( "89.0 RTL",  "http://mp3.89.0rtl.de/listen.pls",  ""));
	stations.addStation(StationObject( "Antenne 1",  "http://stream.antenne1.de/stream2/livestream.mp3",  "http://static.antenne1.de/content/pictures/tpl/logo-antenne1.png"));
	stations.addStation(StationObject( "Antenne Bayern",  "http://www.antenne.de/webradio/antenne.wmx",  "http://www.webradio.de/internetradio/images/logo_aby_gross.jpg"));
	stations.addStation(StationObject( "Antenne Bayern 80er Kulthits",  "http://www.antenne.de/webradio/channels/80er-kulthits.wmx",  ""));
	stations.addStation(StationObject( "Antenne Bayern Chillout",  "http://www.antenne.de/webradio/channels/chillout.wmx",  ""));
	stations.addStation(StationObject( "Antenne Bayern Top 40",  "http://www.antenne.de/webradio/channels/top-40.wmx",  ""));
	stations.addStation(StationObject( "B5 Aktuell",  "http://streams.br-online.de/b5aktuell_2.m3u",  ""));
	stations.addStation(StationObject( "Bayern 1",  "http://streams.br-online.de/bayern1_2.m3u",  ""));
	stations.addStation(StationObject( "Bayern 3",  "http://streams.br-online.de/bayern3_2.m3u",  ""));
	stations.addStation(StationObject( "bigFM",  "http://srv05.bigstreams.de/bigfm-mp3-96",  "http://static.bigfm.de/content/pictures/tpl/bigfm.png"));
	stations.addStation(StationObject( "Blackbeats.FM",  "http://blackbeats.fm/listen.m3u",  "http://blackbeats.fm/images/logo.png"));
	stations.addStation(StationObject( "Bremen Eins",  "http://httpmedia.radiobremen.de/bremeneins.m3u",  ""));
	stations.addStation(StationObject( "Bremen Vier",  "http://httpmedia.radiobremen.de/bremenvier.m3u",  ""));
	stations.addStation(StationObject( "BR Puls",  "http://streams.br-online.de/jugend-radio_2.m3u",  ""));
	stations.addStation(StationObject( "Dasding",  "http://mp3-live.dasding.de/dasding_m.m3u",  "http://www.dasding.de/-/id=434098/property=detail/m6io9h/index.jpg"));
	stations.addStation(StationObject( "delta radio",  "http://streams.deltaradio.de/delta-live/mp3-128/wwwchipde",  "http://www.deltaradio.de/images/DELTA/logo.png"));
	stations.addStation(StationObject( "Deluxe Lounge Radio",  "http://deluxetelevision.com/livestreams/radio/DELUXE_LOUNGE_RADIO.pls",  ""));
	stations.addStation(StationObject( "detektor.fm",  "http://detektor.fm/stream/mp3/musik/",  "http://detektor.fm/download/?file=/images/uploads/downloads/detektor-logo-final.png"));
	stations.addStation(StationObject( "Deutschlandfunk",  "http://www.dradio.de/streaming/dlf.m3u",  "http://www.deutschlandradio.de/media/files/1/1a471d2a0586a7aec12cd3199d4b675fv2.png"));
	stations.addStation(StationObject( "Deutschlandradio Kultur",  "http://www.dradio.de/streaming/dkultur.m3u",  ""));
	stations.addStation(StationObject( "DRadio Wissen",  "http://www.dradio.de/streaming/dradiowissen.m3u",  ""));
	stations.addStation(StationObject( "egoFM",  "http://edge.live.mp3.mdn.newmedia.nacamar.net/ps-egofm_128/livestream.mp3",  "http://www.egofm.de/templates/egofm/img/logo.png"));
	stations.addStation(StationObject( "Electro Radio",  "http://www.electroradio.ch/stream.wpl",  ""));
	stations.addStation(StationObject( "Energy Berlin",  "http://energyradio.de/berlin",  "http://static3.energy.de/fileadmin/images/layout/ci/logo/logo_121_140_on_brightground.png.pagespeed.ce.HUJqn3wPEa.png"));
	stations.addStation(StationObject( "Energy Bremen",  "http://energyradio.de/bremen",  "http://static3.energy.de/fileadmin/images/layout/ci/logo/logo_121_140_on_brightground.png.pagespeed.ce.HUJqn3wPEa.png"));
	stations.addStation(StationObject( "Energy Hamburg",  "http://energyradio.de/hamburg",  "http://static3.energy.de/fileadmin/images/layout/ci/logo/logo_121_140_on_brightground.png.pagespeed.ce.HUJqn3wPEa.png"));
	stations.addStation(StationObject( "Energy München",  "http://www.energyradio.de/muenchen",  "http://static3.energy.de/fileadmin/images/layout/ci/logo/logo_121_140_on_brightground.png.pagespeed.ce.HUJqn3wPEa.png"));
	stations.addStation(StationObject( "Energy Stuttgart",  "http://energyradio.de/stuttgart",  "http://static3.energy.de/fileadmin/images/layout/ci/logo/logo_121_140_on_brightground.png.pagespeed.ce.HUJqn3wPEa.png"));
	stations.addStation(StationObject( "ffn",  "http://player.ffn.de/tunein_ffn.pls",  "http://www.ffn.de/fileadmin/templates/img/ffn_logo.jpg"));
	stations.addStation(StationObject( "FM4",  "http://mp3stream1.apasf.apa.at:8000/listen.pls",  ""));
	stations.addStation(StationObject( "Fritz",  "http://www.fritz.de/live.m3u",  "https://upload.wikimedia.org/wikipedia/de/thumb/3/3b/Rbb-fritz-logo.svg/602px-Rbb-fritz-logo.svg.png"));
	stations.addStation(StationObject( "Hit-Radio Antenne",  "http://stream.antenne.com/hra-nds/mp3-128/IMDADevice/",  "http://cdn.antenne.com/static/img/ant-logo-004.png"));
	stations.addStation(StationObject( "Hit Radio FFH",  "http://streams.ffh.de/radioffh/mp3/hqlivestream.m3u",  "http://static.ffh.de/fileadmin/templates/www.ffh.de/images/logo.png"));
	stations.addStation(StationObject( "hr3",  "http://metafiles.gl-systemhaus.de/hr/hr3_1.asx",  ""));
	stations.addStation(StationObject( "Kiss FM",  "http://stream.kissfm.de/kissfm/mp3-128/internetradio/",  "http://static.kissfm.de/images/logo.png"));
	stations.addStation(StationObject( "Klassik Radio",  "http://edge.live.mp3.mdn.newmedia.nacamar.net/klassikradio128/livestream.mp3",  ""));
	stations.addStation(StationObject( "MDR Jump",  "http://www.jumpradio.de/static/webchannel/jump_live_channel_high.m3u",  "http://www.jumpradio.de/service/kontakt/logi100_v-modIndexStandard_zc-fc76ae11.jpg?version=30207"));
	stations.addStation(StationObject( "N-JOY",  "http://ndrstream.ic.llnwd.net/stream/ndrstream_n-joy_hi_mp3",  "http://www.n-joy.de/resources/images/logo.png"));
	stations.addStation(StationObject( "NDR2",  "http://ndrstream.ic.llnwd.net/stream/ndrstream_ndr2_hi_mp3",  ""));
	stations.addStation(StationObject( "Oldie 95",  "http://mp3.oldie95.c.nmdn.net/oldie95/livestream80.mp3",  ""));
	stations.addStation(StationObject( "Ostseewelle Hit-Radio",  "http://edge.live.mp3.mdn.newmedia.nacamar.net/ostseewellelive/livestream.mp3",  "http://www.ostseewelle.de/wp-content/themes/sight/images/logo.png"));
	stations.addStation(StationObject( "Planet Radio",  "http://streams.planetradio.de/planetradio/mp3/hqlivestream.m3u",  "http://static.planetradio.de/fileadmin/templates/www.planetradio.de/images/logo.png"));
	stations.addStation(StationObject( "R.SH",  "http://streams.rsh.de/rsh-live/mp3-128/wwwchipde",  "http://www.rsh.de/images/RSH/logo.png"));
	stations.addStation(StationObject( "radioeins",  "http://www.radioeins.de/live.m3u",  ""));
	stations.addStation(StationObject( "Radio Gong 96,3",  "http://www.radiogong.de/live/high_q.m3u",  "http://www.radiogong.de/sites/default/files/insight_logo.png"));
	stations.addStation(StationObject( "Radio Hamburg",  "http://mp3.radiohamburg.c.nmdn.net/radiohamburg/livestream192.mp3",  "http://www.radiohamburg.de/var/data/titelanzeige/default-radiohh-100x66.jpg"));
	stations.addStation(StationObject( "Rock Antenne",  "http://www.rockantenne.de/webradio/rockantenne.m3u",  "http://www.rockantenne.de/imda/logos/600x600/ROCK-ANTENNE.png"));
	stations.addStation(StationObject( "Sport1.fm 24/7",  "http://77.67.34.11/SPORT1FM_24_7.mp3",  ""));
	stations.addStation(StationObject( "Sport1.fm Einzelspielkanal 1",  "http://stream.sport1.fm/api/livestream-redirect/SPORT1FM_Einzel1.mp3",  ""));
	stations.addStation(StationObject( "Sport1.fm Einzelspielkanal 2",  "http://stream.sport1.fm/api/livestream-redirect/SPORT1FM_Einzel2.mp3",  ""));
	stations.addStation(StationObject( "Sport1.fm Einzelspielkanal 3",  "http://stream.sport1.fm/api/livestream-redirect/SPORT1FM_Einzel3.mp3",  ""));
	stations.addStation(StationObject( "Sport1.fm Einzelspielkanal 4",  "http://stream.sport1.fm/api/livestream-redirect/SPORT1FM_Einzel4.mp3",  ""));
	stations.addStation(StationObject( "Sport1.fm Einzelspielkanal 5",  "http://stream.sport1.fm/api/livestream-redirect/SPORT1FM_Einzel5.mp3",  ""));
	stations.addStation(StationObject( "Sport1.fm Einzelspielkanal 6",  "http://stream.sport1.fm/api/livestream-redirect/SPORT1FM_Einzel6.mp3",  ""));
	stations.addStation(StationObject( "SWR1 Baden-Württemberg",  "http://mp3-live.swr.de/swr1bw_m.m3u",  ""));
	stations.addStation(StationObject( "SWR3",  "http://mp3-live.swr3.de/swr3_m.m3u",  "http://www.swr3.de/-/id=404778/property=thumbnail/width=260/height=156/pubVersion=15/1ygku8j/index.jpg"));
	stations.addStation(StationObject( "TechnoBase.FM",  "http://listen.technobase.fm/tunein-dsl-pls",  ""));
	stations.addStation(StationObject( "Top 100 Station",  "http://www.top100station.de/switch/r3472.pls",  ""));
	stations.addStation(StationObject( "UnserDing",  "http://streaming01.sr-online.de/unserding_1.m3u",  ""));
	stations.addStation(StationObject( "WDR 2",  "http://www.wdr.de/wdrlive/media/wdr2.m3u",  ""));
	stations.addStation(StationObject( "WDR 4",  "http://www.wdr.de/wdrlive/media/wdr4.m3u",  ""));
	stations.addStation(StationObject( "You FM",  "http://metafiles.gl-systemhaus.de/hr/youfm_2.m3u",  "http://www.you-fm.de/images/logo-youfm-3.jpg"));
	rootContext()->setContextProperty("stationModel", &stations);
// 	rootObject()->setProperty("stations", stations);
}

PlayerWidget::~PlayerWidget() {
}

void PlayerWidget::playPressed() {
	player->play();
}

void PlayerWidget::stationSelected(QString name, QString url, QString cover) {
	QUrl u = QUrl(url);
	QNetworkRequest req = QNetworkRequest(u);
	player->setMedia(u);
}

void PlayerWidget::mediaDataChanged(const QMediaContent& media) {
	
}

void PlayerWidget::volumeChanged(int v) {
	rootObject()->setProperty("volume",QVariant(v));
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
