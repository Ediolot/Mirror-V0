//
// Created by jsier on 26/05/2019.
//

#include <ctime>
#include <iostream>
#include "DatetimeWidget.h"
#include "TextWidget.h"
#include "../../utils/Utils.h"
#include "../../utils/Requester.h"

using namespace nlohmann;

DatetimeWidget::DatetimeWidget(BaseWidget *parent)
    : BaseWidget(parent)
    , runOnceAsync()
{}

const std::string &DatetimeWidget::getDefaultViewPath() const {
    return DEFAULT_VIEW;
}

void DatetimeWidget::updateControllerInter(UpdateRate rate) {
    BaseWidget::updateControllerInter(rate);

    auto timeWidget = (TextWidget*)getChild("time");
    auto dateWidget = (TextWidget*)getChild("date");
    auto quoteWidget = (TextWidget*)getChild("quote");

    if (rateIs(rate, UpdateRate::EACH_TICK)) {
        std::time_t t = std::time(nullptr);
        char mbstr[128];
        if (std::strftime(mbstr, sizeof(mbstr), "%H : %M : %S", std::localtime(&t))) {
            timeWidget->setText(mbstr);
        }
        if (std::strftime(mbstr, sizeof(mbstr), "%d / %b / %y", std::localtime(&t))) {
            dateWidget->setText(mbstr);
        }
    }

    if (rateIs(rate, UpdateRate::EACH_MINUTE)) {
        runOnceAsync.run([=](){
            std::string quote;
            do {
                json data = Requester(URL).asJson();
                try {
                    std::string quoteText = data["quoteText"];
                    std::string quoteAuthor = data["quoteAuthor"];
                    quote = "‘" + quoteText + "’ - " + quoteAuthor;
                } catch (...) {}
            } while (quote.size() > 40 * 3);

            if (!quote.empty()) {
                quoteWidget->setText(quote);
            }
        });
    }
}
