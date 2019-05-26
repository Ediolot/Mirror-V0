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

    double rX;
    double rY;
    double rWidth;
    double rHeight;

public:
    explicit BaseWidget(BaseWidget* parent = nullptr);
    virtual ~BaseWidget();

    virtual const std::string& getDefaultViewPath() const = 0;
    void loadView(const std::string& xmlView);
    void loadDefaultView();
    void clearView();

    virtual void updateView();

    void setWidth(double value, Value::Type type = Value::Type::NUMERIC);
    void setHeight(double value, Value::Type type = Value::Type::NUMERIC);

protected:
    virtual void parseViewOptions(XMLElement *element);
    virtual void updateViewOptions(XMLElement *element);

    Value toValue(XMLElement *element, const char* attribute, double defaultValue = 0, Value::Type defaultType = Value::Type::NUMERIC) const;
    Value toValue(XMLElement *element, const char* attribute, const Value& defaultValue) const;
    std::string toString(XMLElement *element, const char *attribute, const std::string& defaultValue = "") const;
    int toInt(XMLElement *element, const char *attribute, int defaultValue = 0) const;
};


#endif //MIRROR_APP_BASECOMPONENT_H
