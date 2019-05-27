//
// Created by jsier on 27/05/2019.
//

#ifndef MIRROR_APP_PROPERTIES_H
#define MIRROR_APP_PROPERTIES_H

#include <string>
#include <allegro5/color.h>
#include "../external/tinyxml2/tinyxml2.h"
#include "../utils/Value.h"
#include "../resourceLoaders/Colors.h"
#include "../resourceLoaders/Fonts.h"

using namespace tinyxml2;

namespace Properties {
    enum TYPE {
        NONE = 0, TEXT, IMAGE, DATETIME,
        N_ELEMENTS_TYPE
    };
    enum ALIGN {
        LEFT = 0, RIGHT, CENTER, TOP, BOTTOM,
        N_ELEMENTS_ALIGN
    };
    enum SCALE_TYPE {
        SCALE_ALL = 0, SCALE_FIT, SCALE_EXPAND,
        N_ELEMENTS_SCALE_TYPE
    };

    namespace Strings {
        inline const char* type[N_ELEMENTS_TYPE] = {"none", "text", "image", "datetime"};
        inline const char* align[N_ELEMENTS_ALIGN] = {"left", "right", "center", "top", "bottom"};
        inline const char* fontSize[Fonts::N_FONTS_SIZES] = {"tiny", "small", "normal", "big", "large", "huge", "enormous"};
        inline const char* scaleType[N_ELEMENTS_SCALE_TYPE] = {"scale_all", "scale_fit", "scale_expand"};
    }

    namespace Parser {
        int base(XMLElement* element, const char* attribute, int defValue, int max, const char* strings[]);

        Value value(XMLElement *element, const char* attribute, const Value& defValue);
        int integer(XMLElement *element, const char *attribute, int defValue = 0);
        std::string string(XMLElement *element, const char *attribute, const std::string& defStr = "");
        ALLEGRO_COLOR color(XMLElement *element, const char *attribute, const ALLEGRO_COLOR defColor = Colors::get(Colors::WHITE));

        TYPE type(XMLElement* element, const char* attribute, TYPE defValue);
        ALIGN align(XMLElement* element, const char* attribute, ALIGN defValue);
        Fonts::Size fontSize(XMLElement* element, const char* attribute, Fonts::Size defValue);
        SCALE_TYPE scaleType(XMLElement* element, const char* attribute, SCALE_TYPE defValue);
    }
}


#endif //MIRROR_APP_PROPERTIES_H
