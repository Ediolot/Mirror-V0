//
// Created by jsier on 26/05/2019.
//

#ifndef MIRROR_APP_DATETIMEWIDGET_H
#define MIRROR_APP_DATETIMEWIDGET_H


#include "../BaseWidget.h"

class DatetimeWidget : public BaseWidget {
    inline static const std::string DEFAULT_VIEW = "../views/datetimeWidget.xml";
    std::string date;
    std::string time;
    std::string quote;

public:
    explicit DatetimeWidget(BaseWidget* parent = nullptr);
    virtual ~DatetimeWidget();
    const std::string& getDefaultViewPath() const override;
    void updateView() override;
    void updateControllerInter(UpdateRate rate) override;

protected:
    void parseViewOptions(XMLElement *element) override;
    void updateViewOptions(XMLElement *element) override;
};


#endif //MIRROR_APP_DATETIMEWIDGET_H
