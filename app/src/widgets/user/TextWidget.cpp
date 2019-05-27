//
// Created by jsier on 17/05/2019.
//

#include <iostream>
#include <cmath>
#include <algorithm>
#include "TextWidget.h"
#include "../../resourceLoaders/Fonts.h"
#include "../../resourceLoaders/Colors.h"
#include "../../utils/Utils.h"

TextWidget::TextWidget(BaseWidget *parent)
    : BaseWidget(parent)
    , txt("")
    , fontId(Fonts::DEFAULT_FONT)
    , alignment(ALLEGRO_ALIGN_LEFT)
{}

TextWidget::~TextWidget() {

}

void TextWidget::parseViewOptions(XMLElement *element) {
    BaseWidget::parseViewOptions(element);

    txt = toString(element->FirstChildElement("text"), "value");
    fontSize = (Fonts::Size)toInt(element->FirstChildElement("font"), "size", 16);
    alignment = (Fonts::Size)toInt(element->FirstChildElement("text-align"), "value", 0);
    std::string fontFamilyStr = toString(element->FirstChildElement("font"), "family", "default");
    setFontFromStr(fontFamilyStr);
}

void TextWidget::updateViewOptions(XMLElement *element) {
    BaseWidget::updateViewOptions(element);

    txt = toString(element, "text", txt);
    fontSize = (Fonts::Size)toInt(element, "font-size", 16);
    alignment = (Fonts::Size)toInt(element, "text-align", alignment);
    std::string fontFamilyStr = toString(element, "font-family", "default");
    setFontFromStr(fontFamilyStr);
}

const std::string& TextWidget::getDefaultViewPath() const {
    return DEFAULT_VIEW;
}

void TextWidget::updateView() {
    BaseWidget::updateView();

    const ALLEGRO_FONT* font = Fonts::get(fontId, fontSize);
    std::string remaining = txt;


    double height = al_get_font_line_height(font);
    int maxLines = (int)std::floor(rHeight / height);
    int line = 0;

    if (maxLines < 1) {
        return;
    }

    while (line < (maxLines - 1) && !remaining.empty()) {
        remaining = drawTextLine(rX, rY + line * height, remaining);
        line++;
    }

    if (!remaining.empty()) {
        remaining = drawTextLine(rX, rY + line * height, remaining, "...");
    }
}

std::string TextWidget::drawTextLine(double x, double y, std::string s, const std::string& end) const {
    double width = al_get_text_width(Fonts::get(fontId, fontSize), s.c_str());

    int len = std::floor(s.size() * rWidth / width);
    std::string sub;

    do  {
        sub = Utils::substrUTF8(s, 0, len);
        Utils::trim(sub);
        width = al_get_text_width(Fonts::get(fontId, fontSize), sub.c_str());
        len--;
    } while (width > rWidth);

    s = len > s.size() ? "" : Utils::substrUTF8(s, len + 1, s.size() - len);
    Utils::trim(s);

    if (!s.empty() && !end.empty()) {
        s = Utils::substrUTF8(sub, sub.size() - end.size(), end.size()) + s;
        Utils::trim(s);
        sub = Utils::substrUTF8(sub, 0, sub.size() - end.size()) + end;
    }

    int allegro_align = ALLEGRO_ALIGN_LEFT;
    if (alignment == 1) { // RIGHT
        x += rWidth;
        allegro_align = ALLEGRO_ALIGN_RIGHT;
    }
    else if (alignment == 2) { // CENTER
        x += rWidth / 2;
        allegro_align = ALLEGRO_ALIGN_CENTER;
    }
    al_draw_text(Fonts::get(fontId, fontSize), Colors::get(Colors::WHITE), x, y, allegro_align, sub.c_str());
    return s;
}

void TextWidget::setText(const std::string &txt) {
    this->txt = txt;
}

void TextWidget::setFontFromStr(const std::string &family) {
    //if (family == ...) {
    //    return;
    //}

    // font = Fonts::DEFAULT_FONT;
}
