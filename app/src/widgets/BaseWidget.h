//
// Created by jsier on 17/05/2019.
//

#ifndef MIRROR_APP_BASECOMPONENT_H
#define MIRROR_APP_BASECOMPONENT_H

#include <string>
#include <vector>
#include "../external/tinyxml2/tinyxml2.h"
#include "../utils/Value.h"
#include "Properties.h"

using namespace tinyxml2;

class BaseWidget {
protected:
    std::string id;
    BaseWidget *parent;
    std::vector<BaseWidget*> children;

    Value x;
    Value y;
    Value width;
    Value height;
    Value padding;
    ALLEGRO_COLOR background;
    Properties::ALIGN vAlign;
    Properties::ALIGN hAlign;

    double rX;
    double rY;
    double rWidth;
    double rHeight;

public:
    enum UpdateRate {
        NONE,
        EACH_TICK,
        EACH_SECOND,
        EACH_MINUTE,
        EACH_HOUR,
        EACH_12HOUR,
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

    const std::string& getId() const;

    void setWidth(double value, Value::Type type = Value::Type::NUMERIC);
    void setHeight(double value, Value::Type type = Value::Type::NUMERIC);

    BaseWidget* getChild(const std::string& childId);

protected:
    virtual void parseViewOptions(XMLElement *element);

    bool rateIs(UpdateRate rate, UpdateRate reference) const;
};


#endif //MIRROR_APP_BASECOMPONENT_H
