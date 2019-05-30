//
// Created by jsier on 27/05/2019.
//

#include "WeatherWidget.h"
#include "../../utils/Utils.h"
#include "../../utils/Requester.h"

using namespace nlohmann;

WeatherWidget::WeatherWidget(BaseWidget *parent)
    : BaseWidget(parent)
    , runOnceAsync()
{}

const std::string &WeatherWidget::getDefaultViewPath() const {
    return DEFAULT_VIEW;
}

void WeatherWidget::updateView() {
    BaseWidget::updateView();
}

void WeatherWidget::updateControllerInter(BaseWidget::UpdateRate rate) {
    BaseWidget::updateControllerInter(rate);


    if (rateIs(rate, UpdateRate::EACH_MINUTE)) {
        runOnceAsync.run([=](){
            json data = Requester(URL).asJson();
            if (data.empty()) {
                return;
            }
        });
    }
}
