#include "mapwidget.h"



MapWidget::MapWidget(MarbleWidget *parent) :
    MarbleWidget(parent)
{

    setMapThemeId("earth/openstreetmap/openstreetmap.dgml");
    setShowCrosshairs(false);
    setShowOverviewMap(false);
    setShowOtherPlaces(false);
    setShowScaleBar(false);
    GeoDataCoordinates coor(105.64723294, 21.00480599, 0, Marble::GeoDataCoordinates::Degree);
    model()->setHome(coor, 2357);
    model()->setWorkOffline(true);

    goHome();
}
