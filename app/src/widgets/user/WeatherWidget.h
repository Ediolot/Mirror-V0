//
// Created by jsier on 27/05/2019.
//

#ifndef MIRROR_APP_WEATHERWIDGET_H
#define MIRROR_APP_WEATHERWIDGET_H


#include "../BaseWidget.h"
#include "../../utils/RunOnceAsync.h"


class WeatherWidget : public BaseWidget {
    inline static const std::string DEFAULT_VIEW = "../views/weatherWidget.xml";
    inline static const std::string URL = "http://api.openweathermap.org/data/2.5/forecast?id=3128760&appid=c4aeec5a95e4ef1db4c115086f5eeb5a&units=metric";
    inline static const int N_PREDS = 5;
    RunOnceAsync runOnceAsync;

public:
    explicit WeatherWidget(BaseWidget* parent = nullptr);
    virtual ~WeatherWidget() = default;
    const std::string& getDefaultViewPath() const override;
    void updateView() override;
    void updateControllerInter(UpdateRate rate) override;
};


#endif //MIRROR_APP_WEATHERWIDGET_H
