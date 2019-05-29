//
// Created by jsier on 29/05/2019.
//

#ifndef MIRROR_APP_SOLARSYSTEMWIDGET_H
#define MIRROR_APP_SOLARSYSTEMWIDGET_H

#include <mutex>
#include "../BaseWidget.h"

class Planet {
    double speed;
    double anglePos;
    std::mutex mtx;

    // Style
    double radius;
    double orbitRadius;
    bool rings;
    bool jupyterSpot;
    Colors::Rid colorBottom;
    Colors::Rid colorTop;
    Colors::Rid colorRings;

public:
    Planet(double speed, double radius, double orbitRadius, Colors::Rid colorTop, Colors::Rid colorBottom,  Colors::Rid colorRings, bool jupyterSpot = false);
    Planet(double speed, double radius, double orbitRadius, Colors::Rid colorTop, Colors::Rid colorBottom, bool jupyterSpot = false);

    void draw(double cx, double cy, double refSize);
    void update(double elapsed);
};

// ---------------------------------------------------------------------------------------------------------------------

class SolarSystemWidget : public BaseWidget {
    inline static const std::string DEFAULT_VIEW = "";
    inline static const double BASE_SPEED = 0.1;
    inline static Planet PLANETS[] = {
            Planet(BASE_SPEED * 1.60, 0.005, 0.07, Colors::CASPER, Colors::SPUN_PEARL),                            // Mercury
            Planet(BASE_SPEED * 1.17, 0.009, 0.10, Colors::KOURNIKOVA, Colors::APACHE),                            // Venus
            Planet(BASE_SPEED * 1.00, 0.010, 0.13, Colors::SUMMER_SKY, Colors::PELOROUS),                          // Earth
            Planet(BASE_SPEED * 0.80, 0.008, 0.16, Colors::RUBY, Colors::CARDINAL),                                // Mars
            Planet(BASE_SPEED * 0.43, 0.025, 0.23, Colors::FALLOW, Colors::MEDIUM_WOOD, true),                     // Jupyter
            Planet(BASE_SPEED * 0.33, 0.023, 0.30, Colors::GOLDEN_TAINOI, Colors::ROB_ROY, Colors::PALE_TAUPE),    // Saturn
            Planet(BASE_SPEED * 0.23, 0.016, 0.37, Colors::BERMUDA, Colors::TRADE_WIND, Colors::JELLY_BEAN),       // Uranus
            Planet(BASE_SPEED * 0.17, 0.016, 0.44, Colors::VICKING, Colors::SUMMER_SKY),                           // Neptune
    };

public:
    explicit SolarSystemWidget(BaseWidget* parent = nullptr);
    virtual ~SolarSystemWidget() = default;
    const std::string& getDefaultViewPath() const override;
    void updateView() override;
    void updateControllerRT(double elapsed) override;
};

#endif //MIRROR_APP_SOLARSYSTEMWIDGET_H
