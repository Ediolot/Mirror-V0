//
// Created by jsier on 17/05/2019.
//

#ifndef MIRROR_APP_BASECOMPONENT_H
#define MIRROR_APP_BASECOMPONENT_H

#include <string>
#include <vector>
#include "../external/tinyxml2/tinyxml2.h"
#include "../utils/Value.h"

using namespace tinyxml2;

class BaseWidget {
protected:
    BaseWidget *parent;
    std::vector<BaseWidget*> children;

    Value x;
    Value y;
    Value width;
    Value height;
    Value padding;

public:
    explicit BaseWidget(const std::string& xmlView, BaseWidget* parent = nullptr);
    virtual ~BaseWidget();

    void loadView(const std::string& xmlView);
    void clearView();

protected:
    virtual void parseOtherViewOptions(XMLElement *options);

    Value toValue(XMLElement *options, const char* node, const char* attribute, double defaultValue = 0, Value::Type defaultType = Value::Type::NUMERIC) const;
    std::string toString(XMLElement *options, const char* node, const std::string& defaultValue = "") const;
};


#endif //MIRROR_APP_BASECOMPONENT_H
