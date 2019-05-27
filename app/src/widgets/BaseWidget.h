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
    int id;
    BaseWidget *parent;
    std::vector<BaseWidget*> children;

    Value x;
    Value y;
    Value width;
    Value height;
    Value padding;
    int backgroundR;
    int backgroundG;
    int backgroundB;

    double rX;
    double rY;
    double rWidth;
    double rHeight;

    int vAlign;
    int hAlign;

public:
    enum UpdateRate {
        NONE,
        REAL_TIME,
        EACH_TICK,
        EACH_SECOND,
        EACH_MINUTE,
        EACH_HOUR,
    };

    explicit BaseWidget(BaseWidget* parent = nullptr);
    virtual ~BaseWidget();

    virtual const std::string& getDefaultViewPath() const = 0;
    void loadView(const std::string& xmlView);
    void loadDefaultView();
    void clearView();

    virtual void updateView();
    virtual void updateControllerRT(double elapsed); // Real time
    virtual void updateControllerInter(UpdateRate rate); // Interval

    int getId() const;

    void setWidth(double value, Value::Type type = Value::Type::NUMERIC);
    void setHeight(double value, Value::Type type = Value::Type::NUMERIC);

    BaseWidget* getChild(int id);

protected:
    virtual void parseViewOptions(XMLElement *element);
    virtual void updateViewOptions(XMLElement *element);

    Value toValue(XMLElement *element, const char* attribute, double defaultValue = 0, Value::Type defaultType = Value::Type::NUMERIC) const;
    Value toValue(XMLElement *element, const char* attribute, const Value& defaultValue) const;
    std::string toString(XMLElement *element, const char *attribute, const std::string& defaultValue = "") const;
    int toInt(XMLElement *element, const char *attribute, int defaultValue = 0) const;

    bool rateIs(UpdateRate rate, UpdateRate reference) const;
};


#endif //MIRROR_APP_BASECOMPONENT_H
