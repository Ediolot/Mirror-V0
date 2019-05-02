//
// Created by jsier on 02/05/2019.
//

#include <iomanip>
#include <chrono>
#include "DateTime.h"
#include "../resources/Fonts.h"
#include "../resources/Colors.h"

DateTime::DateTime()
    : date("", Fonts::get(Fonts::Rid::DEFAULT_FONT), Colors::get(Colors::Rid::WHITE), 0, 0)
    , time("", Fonts::get(Fonts::Rid::DEFAULT_FONT), Colors::get(Colors::Rid::WHITE), 0, date.getHeight())
{
}

void DateTime::draw() {
    update(); // Shouldnt be here
    date.draw();
    time.draw();
}

void DateTime::update() {
    std::string dateStr;
    std::string timeStr;

    setDateTime(dateStr, timeStr);
    date.setText(dateStr);
    time.setText(timeStr);
}

void DateTime::setDateTime(std::string &dateStr, std::string &timeStr) {
    std::stringstream dateBuffer;
    std::stringstream timeBuffer;
    auto now = std::time(nullptr);
    auto tm = *std::localtime(&now);

    dateBuffer << std::put_time(&tm, "%d %b %Y");
    timeBuffer << std::put_time(&tm, "%H:%M:%S");
    dateStr = dateBuffer.str();
    timeStr = timeBuffer.str();
}
