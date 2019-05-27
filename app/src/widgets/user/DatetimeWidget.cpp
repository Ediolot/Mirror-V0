//
// Created by jsier on 26/05/2019.
//

#include <ctime>
#include <iostream>
#include "DatetimeWidget.h"
#include "TextWidget.h"

DatetimeWidget::DatetimeWidget(BaseWidget *parent) : BaseWidget(parent) {

}

DatetimeWidget::~DatetimeWidget() {

}

const std::string &DatetimeWidget::getDefaultViewPath() const {
    return DEFAULT_VIEW;
}

void DatetimeWidget::parseViewOptions(XMLElement *element) {
    BaseWidget::parseViewOptions(element);
}

void DatetimeWidget::updateViewOptions(XMLElement *element) {
    BaseWidget::updateViewOptions(element);
}

void DatetimeWidget::updateView() {
    BaseWidget::updateView();

    ((TextWidget*)getChild(0))->setText(date);
    ((TextWidget*)getChild(1))->setText(time);
}

void DatetimeWidget::updateControllerInter(UpdateRate rate) {
    BaseWidget::updateControllerInter(rate);

    if (!rateIs(rate, UpdateRate::EACH_SECOND)) {
        return;
    }

    std::time_t t = std::time(nullptr);
    char mbstr[100];
    if (std::strftime(mbstr, sizeof(mbstr), "%H : %M : %S", std::localtime(&t))) {
        time = mbstr;
    }
    if (std::strftime(mbstr, sizeof(mbstr), "%d / %b / %y", std::localtime(&t))) {
        date = mbstr;
    }
}
