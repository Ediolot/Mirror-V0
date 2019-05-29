//
// Created by jsier on 29/05/2019.
//

#include <allegro5/allegro_primitives.h>
#include <cmath>
#include "SolarSystemWidget.h"

SolarSystemWidget::SolarSystemWidget(BaseWidget *parent) : BaseWidget(parent) {

}

const std::string &SolarSystemWidget::getDefaultViewPath() const {
    return DEFAULT_VIEW;
}

void SolarSystemWidget::updateView() {
    BaseWidget::updateView();

    double minSize = std::max(rWidth < rHeight ? rWidth : rHeight, 1000.0);
    double cx = rX + rWidth / 2;
    double cy = rY + rHeight / 2;
    double sunRadius = minSize * 0.05;

    al_draw_filled_circle(cx, cy,sunRadius, Colors::get(Colors::GOLDEN_YELLOW));
    for (Planet& planet : PLANETS) {
        planet.draw(cx, cy, minSize);
    }
}

void SolarSystemWidget::updateControllerRT(double elapsed) {
    BaseWidget::updateControllerRT(elapsed);

    for (Planet& planet : PLANETS) {
        planet.update(elapsed);
    }
}

Planet::Planet(double speed,
               double radius,
               double orbitRadius,
               Colors::Rid colorTop,
               Colors::Rid colorBottom,
               Colors::Rid colorRings,
               bool jupyterSpot)
    : speed(speed)
    , anglePos(0)
    , mtx()
    , radius(radius)
    , orbitRadius(orbitRadius)
    , rings(true)
    , jupyterSpot(jupyterSpot)
    , colorBottom(colorBottom)
    , colorTop(colorTop)
    , colorRings(colorRings)
{}

Planet::Planet(double speed,
               double radius,
               double orbitRadius,
               Colors::Rid colorTop,
               Colors::Rid colorBottom,
               bool jupyterSpot)
    : speed(speed)
    , anglePos(0)
    , mtx()
    , radius(radius)
    , orbitRadius(orbitRadius)
    , rings(false)
    , jupyterSpot(jupyterSpot)
    , colorBottom(colorBottom)
    , colorTop(colorTop)
    , colorRings()
{}

void Planet::draw(double cx, double cy, double refSize) {
    double orbRadius = refSize * orbitRadius;
    double planetRadius = refSize * radius;
    mtx.lock();
    double x = cx + orbRadius * std::cos(anglePos);
    double y = cy + orbRadius * std::sin(anglePos);
    mtx.unlock();

    al_draw_circle(cx, cy, orbRadius, Colors::get(Colors::GREY), 2);
    al_draw_filled_pieslice(x, y, planetRadius, 0, -3.15, Colors::get(colorTop));
    al_draw_filled_pieslice(x, y, planetRadius, 0, +3.14, Colors::get(colorBottom));

    if (rings) {
        al_draw_circle(x, y, planetRadius + 5, Colors::get(colorRings), 2);
    }

    if (jupyterSpot) {
        al_draw_filled_ellipse(
                x + planetRadius * 0.5,
                y + planetRadius * 0.3,
                planetRadius * 0.2,
                planetRadius * 0.12,
                Colors::get(Colors::RUBY));
    }
}

void Planet::update(double elapsed) {
    mtx.lock();
    anglePos += speed * elapsed;
    mtx.unlock();
}


