//
// Created by jsier on 27/05/2019.
//

#ifndef MIRROR_APP_WEATHERWIDGET_H
#define MIRROR_APP_WEATHERWIDGET_H


#include "../BaseWidget.h"


class WeatherWidget : public BaseWidget {
    inline static const std::string DEFAULT_VIEW = "../views/weatherWidget.xml";
    inline static const std::string CITY_ID = "3128760";

public:
    explicit WeatherWidget(BaseWidget* parent = nullptr);
    virtual ~WeatherWidget() = default;
    const std::string& getDefaultViewPath() const override;
    void updateView() override;
    void updateControllerInter(UpdateRate rate) override;
};


#endif //MIRROR_APP_WEATHERWIDGET_H
