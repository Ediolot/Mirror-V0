//
// Created by jsier on 27/05/2019.
//

#include "WeatherWidget.h"
#include "../../utils/Utils.h"

using namespace nlohmann;

WeatherWidget::WeatherWidget(BaseWidget *parent) : BaseWidget(parent) {

}

const std::string &WeatherWidget::getDefaultViewPath() const {
    return DEFAULT_VIEW;
}

void WeatherWidget::updateView() {
    BaseWidget::updateView();
}

void WeatherWidget::updateControllerInter(BaseWidget::UpdateRate rate) {
    BaseWidget::updateControllerInter(rate);


    if (rateIs(rate, UpdateRate::EACH_MINUTE)) {
        std::string url_weather = "http://api.openweathermap.org/data/2.5/forecast?id=3128760&appid=c4aeec5a95e4ef1db4c115086f5eeb5a&units=metric";
        //json data = Utils::requestJSON(url_weather);
        //if (!data.empty()) {

        //}
    }
}
