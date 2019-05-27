//
// Created by jsier on 27/05/2019.
//

#include "Properties.h"
#include "../utils/Utils.h"

using namespace Properties;

int Parser::base(XMLElement* element, const char* attribute, int defValue, int max, const char* strings[]) {
    if (!element) {
        return defValue;
    }
    const char* attributeStr = element->Attribute(attribute, nullptr);
    if (!attributeStr) {
        return defValue;
    }

    for (int i = 0; i < max; ++i) {
        if (strcmp(attributeStr, strings[i]) == 0) {
            return i;
        }
    }
    return defValue;
}

TYPE Parser::type(XMLElement* element, const char* attribute, TYPE defValue) {
    return (TYPE) Properties::Parser::base(element, attribute, defValue, N_ELEMENTS_TYPE, Strings::type);
}

ALIGN Parser::align(XMLElement* element, const char* attribute, ALIGN defValue) {
    return (ALIGN) Properties::Parser::base(element, attribute, defValue, N_ELEMENTS_ALIGN, Strings::align);
}

Fonts::Size Parser::fontSize(XMLElement* element, const char* attribute, Fonts::Size defValue) {
    return (Fonts::Size) Properties::Parser::base(element, attribute, defValue, Fonts::N_FONTS_SIZES, Strings::fontSize);
}

Fonts::Rid Parser::fontFamily(XMLElement* element, const char* attribute, Fonts::Rid defValue) {
    return (Fonts::Rid) Properties::Parser::base(element, attribute, defValue, Fonts::N_FONTS, Strings::fontFamily);
}

SCALE_TYPE Parser::scaleType(XMLElement* element, const char* attribute, SCALE_TYPE defValue) {
    return (SCALE_TYPE) Properties::Parser::base(element, attribute, defValue, N_ELEMENTS_SCALE_TYPE, Strings::scaleType);
}

Value Properties::Parser::value(XMLElement *element, const char *attribute, const Value& defValue) {
    double value = defValue.getDouble();
    Value::Type type = defValue.getType();

    if (!element) {
        return Value(value, type);
    }
    const char* attributeStr = element->Attribute(attribute, nullptr);
    if (!attributeStr) {
        return Value(value, type);
    }
    int len = strlen(attributeStr);
    value = strtod(attributeStr, nullptr);
    if (len > 3 && attributeStr[len - 1] == 'x' && attributeStr[len - 2] == 'p') {
        type = Value::Type::NUMERIC;
    } else {
        type = Value::Type::PERCENT;
        value /= 100.0;
    }
    return Value(value, type);
}

int Properties::Parser::integer(XMLElement *element, const char *attribute, int defValue) {
    if (!element) {
        return defValue;
    }
    const char* attributeStr = element->Attribute(attribute, nullptr);
    if (!attributeStr) {
        return defValue;
    }
    return strtol(attributeStr, nullptr, 10);
}

std::string Properties::Parser::string(XMLElement *element, const char *attribute, const std::string &defStr) {
    if (!element) {
        return defStr;
    }
    const char* attributeStr = element->Attribute(attribute, nullptr);
    if (!attributeStr) {
        return defStr;
    }
    return std::string(attributeStr);
}

ALLEGRO_COLOR Properties::Parser::color(XMLElement *element, const char *attribute, const ALLEGRO_COLOR defColor) {
    if (!element) {
        return defColor;
    }
    const char* attributeStr = element->Attribute(attribute, nullptr);
    if (!attributeStr) {
        return defColor;
    }
    auto colorsStr = Utils::splitString(attributeStr);
    if (colorsStr.size() != 3) {
        return defColor;
    }
    int r = strtol(colorsStr[0].c_str(), nullptr, 10);
    int g = strtol(colorsStr[1].c_str(), nullptr, 10);
    int b = strtol(colorsStr[2].c_str(), nullptr, 10);
    return al_map_rgb(r, g, b);
}