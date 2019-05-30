//
// Created by jsier on 27/05/2019.
//

#include "WeatherWidget.h"
#include "../../utils/Utils.h"
#include "../../utils/Requester.h"
#include "TextWidget.h"
#include "ImageWidget.h"
#include "../../resourceLoaders/Images.h"

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

            for (int i = 0; i < N_PREDS; ++i) {
                long int epoch = data["list"][i]["dt"];
                double temp = data["list"][i]["main"]["temp"];
                double humi = data["list"][i]["main"]["humidity"];
                double wind = data["list"][i]["wind"]["speed"];
                std::string desc = data["list"][i]["weather"][0]["description"];
                int condition = data["list"][i]["weather"][0]["id"];
                desc[0] = toupper(desc[0]);

                ((TextWidget*)getChild("temp" + std::to_string(i + 1)))->setText(std::to_string((int)temp) + "ºC");
                ((TextWidget*)getChild("hum"  + std::to_string(i + 1)))->setText(std::to_string((int)humi) + "% H");
                ((TextWidget*)getChild("wind" + std::to_string(i + 1)))->setText(std::to_string((int)wind) + " Kmh");
                ((TextWidget*)getChild("cond" + std::to_string(i + 1)))->setText(desc);

                time_t tepoch = static_cast<time_t>(epoch);
                auto tm = gmtime(&tepoch);
                std::string mday = std::to_string(tm->tm_mday);
                std::string mhour = std::to_string(tm->tm_hour);
                int hour = tm->tm_hour;

                time_t rawtime;
                time(&rawtime);
                auto nw = gmtime(&rawtime);
                std::string mday_now = std::to_string(nw->tm_mday);
                std::string mhour_now = std::to_string(nw->tm_hour);

                std::string day = (mday == mday_now) ? "Today" : "Tomorrow";
                std::string time = mhour + ":00";
                ((TextWidget*)getChild("day" + std::to_string(i + 1)))->setText(day);
                ((TextWidget*)getChild("time" + std::to_string(i + 1)))->setText(time);

                bool night = hour >= 20 || hour < 8;
                auto icon = (ImageWidget*)getChild("image" + std::to_string(i + 1));
                Images::Rid rid = Images::WEATHER_SUN_AND_CLOUDS;

                if (condition >= 701 && condition <= 781) {
                    rid = Images::WEATHER_CLOUDS;
                }
                if (condition == 800 || condition == 801) {
                    rid = night ? Images::WEATHER_NIGHT : Images::WEATHER_SUN;
                }
                if (condition == 802 || condition == 803) {
                    rid = night ? Images::WEATHER_NIGHT_AND_CLOUDS : Images::WEATHER_SUN_AND_CLOUDS;
                }
                if (condition == 804) {
                    rid = Images::WEATHER_CLOUDS;
                }
                if (condition >= 600 && condition <= 602) {
                    rid = Images::WEATHER_SNOWY;
                }
                if (condition >= 611 && condition <= 622) {
                    rid = Images::WEATHER_SNOWY_RAINY;
                }
                if (condition >= 300 && condition <= 531) {
                    rid = Images::WEATHER_RAINY;
                }
                if (condition >= 200 && condition <= 232) {
                    rid = Images::WEATHER_RAINY_THUNDER;
                }

                icon->setImage(Images::get(rid), false);
            }
        });
    }
}
