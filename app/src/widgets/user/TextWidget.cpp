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
    , txt("Default text")
    , fontFamily(Fonts::DEFAULT_FONT)
    , fontSize(Fonts::Size::PX16)
    , alignment(Properties::ALIGN::LEFT)
    , mtx()
{}

void TextWidget::parseViewOptions(XMLElement *element) {
    BaseWidget::parseViewOptions(element);

    txt = Properties::Parser::string(element, "text", txt);
    fontSize = Properties::Parser::fontSize(element, "font-size", fontSize);
    fontFamily = Properties::Parser::fontFamily(element, "font-family", fontFamily);
    alignment = Properties::Parser::align(element, "text-align", alignment);
}

const std::string& TextWidget::getDefaultViewPath() const {
    return DEFAULT_VIEW;
}

void TextWidget::updateView() {
    BaseWidget::updateView();

    mtx.lock();
    std::string txt = this->txt;
    mtx.unlock();

    double x = rX;
    double y = rY;
    int allegro_align = ALLEGRO_ALIGN_LEFT;
    if (alignment == 1) { // RIGHT
        x += rWidth;
        allegro_align = ALLEGRO_ALIGN_RIGHT;
    }
    else if (alignment == 2) { // CENTER
        x += rWidth / 2;
        allegro_align = ALLEGRO_ALIGN_CENTER;
    }

    ALLEGRO_USTR *ustr = al_ustr_newf("%s", txt.c_str());
    draw_multiline(x, y, ustr, allegro_align);
}

void TextWidget::setText(const std::string &newTxt) {
    mtx.lock();
    txt = newTxt;
    mtx.unlock();
}

// --------------------------------------------------------------------------------------------------------------------
// https://github.com/liballeg/allegro5/blob/b2775688eea461d8417c769b1158d76c87e5f495/addons/font/text.c

const void TextWidget::draw_multiline(double x, double y, ALLEGRO_USTR *ustr, int flags) {
    const ALLEGRO_FONT* font = Fonts::get(fontFamily, fontSize);
    const ALLEGRO_COLOR color = Colors::get(Colors::WHITE);

    double lineHeight =  al_get_font_line_height(font);
    const ALLEGRO_USTR *hardLine, *softLine;
    ALLEGRO_USTR_INFO hardLineInfo, softLineInfo;
    int hardLinePos = 0, softLinePos = 0;
    int lines = 0;

    /* For every "hard" line separated by a newline character... */
    hardLine = ustr_split_next(ustr, &hardLineInfo, &hardLinePos, "\n");

    while (hardLine) {
        /* For every "soft" line in the "hard" line... */
        softLinePos = 0;
        softLine = get_next_soft_line(hardLine, &softLineInfo, &softLinePos, font, rWidth);

        /* No soft line here because it's an empty hard line. */
        if (!softLine) {
            /* Call the callback with empty string to indicate an empty line. */
            double drawY  = y + (lineHeight * lines);
            al_draw_ustr(font, color, x, drawY, flags, al_ustr_empty_string());
            lines++;
        }
        while(softLine) {
            /* Call the callback on the next soft line. */
            double drawY  = y + (lineHeight * lines);
            al_draw_ustr(font, color, x, drawY, flags, softLine);
            lines++;

            softLine = get_next_soft_line(hardLine, &softLineInfo, &softLinePos, font, rWidth);
        }
        hardLine = ustr_split_next(ustr, &hardLineInfo, &hardLinePos, "\n");
    }
}

const ALLEGRO_USTR *
TextWidget::get_next_soft_line(const ALLEGRO_USTR *ustr, ALLEGRO_USTR_INFO *info, int *pos, const ALLEGRO_FONT *font,
                               float max_width) {

    const ALLEGRO_USTR *result = NULL;
    const char *whitespace = " \t";
    int old_end = 0;
    int end = 0;
    int size = al_ustr_size(ustr);
    bool first_word = true;

    if (*pos >= size) {
        return NULL;
    }

    end = *pos;
    old_end = end;
    do {
        /* On to the next word. */
        end = al_ustr_find_set_cstr(ustr, end, whitespace);
        if (end < 0)
            end = size;

        /* Reference to the line that is being built. */
        result = al_ref_ustr(info, ustr, *pos, end);

        /* Check if the line is too long. If it is, return a soft line. */
        if (al_get_ustr_width(font, result) > max_width) {
            /* Corner case: a single word may not even fit the line.
             * In that case, return the word/line anyway as the "soft line",
             * the user can set a clip rectangle to cut it. */

            if (first_word) {
                /* Set pos to character AFTER end to allow easy iteration. */
                al_ustr_next(ustr, &end);
                *pos = end;
                return result;
            }
            else {
                /* Not first word, return old end position without the new word */
                result = al_ref_ustr(info, ustr, *pos, old_end);
                /* Set pos to character AFTER end to allow easy iteration. */
                al_ustr_next(ustr, &old_end);
                *pos = old_end;
                return result;
            }
        }
        first_word = false;
        old_end    = end;
        /* Skip the character at end which normally is whitespace. */
        al_ustr_next(ustr, &end);
    } while (end < size);

    /* If we get here the whole ustr will fit.*/
    result = al_ref_ustr(info, ustr, *pos, size);
    *pos = size;
    return result;
}

const ALLEGRO_USTR *
TextWidget::ustr_split_next(const ALLEGRO_USTR *ustr, ALLEGRO_USTR_INFO *info, int *pos, const char *delimiter) {
    const ALLEGRO_USTR *result;
    int end, size;

    size = al_ustr_size(ustr);
    if (*pos >= size) {
        return NULL;
    }

    end = al_ustr_find_set_cstr(ustr, *pos, delimiter);
    if (end == -1)
        end = size;

    result = al_ref_ustr(info, ustr, *pos, end);
    /* Set pos to character AFTER delimiter */
    al_ustr_next(ustr, &end);
    (*pos) = end;
    return result;
}
