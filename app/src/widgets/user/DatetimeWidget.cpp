//
// Created by jsier on 26/05/2019.
//

#include <ctime>
#include <iostream>
#include "DatetimeWidget.h"
#include "TextWidget.h"
#include "../../utils/Utils.h"

using namespace nlohmann;

DatetimeWidget::DatetimeWidget(BaseWidget *parent)
    : BaseWidget(parent)
    , date("")
    , time("")
    , quote("")
{}

const std::string &DatetimeWidget::getDefaultViewPath() const {
    return DEFAULT_VIEW;
}

void DatetimeWidget::updateView() {
    BaseWidget::updateView();

    ((TextWidget*)getChild("date"))->setText(date);
    ((TextWidget*)getChild("time"))->setText(time);
    ((TextWidget*)getChild("quote"))->setText(quote);
}

void DatetimeWidget::updateControllerInter(UpdateRate rate) {
    BaseWidget::updateControllerInter(rate);

    if (rateIs(rate, UpdateRate::EACH_TICK)) {
        std::time_t t = std::time(nullptr);
        char mbstr[100];
        if (std::strftime(mbstr, sizeof(mbstr), "%H : %M : %S", std::localtime(&t))) {
            time = mbstr;
        }
        if (std::strftime(mbstr, sizeof(mbstr), "%d / %b / %y", std::localtime(&t))) {
            date = mbstr;
        }
    }

    if (rateIs(rate, UpdateRate::EACH_MINUTE)) {
        std::string newQuote;
        do {
            json data = Utils::requestJSON("https://quota.glitch.me/random");
            try {
                std::string quoteText = data["quoteText"];
                std::string quoteAuthor = data["quoteAuthor"];
                newQuote = "‘" + quoteText + "’ - " + quoteAuthor;
            } catch (...) {}
        } while (quote.size() > 40 * 3);

        if (!newQuote.empty()) {
            quote = newQuote;
        }
    }
}
