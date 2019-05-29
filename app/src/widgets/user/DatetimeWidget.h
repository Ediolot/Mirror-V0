//
// Created by jsier on 26/05/2019.
//

#ifndef MIRROR_APP_DATETIMEWIDGET_H
#define MIRROR_APP_DATETIMEWIDGET_H


#include "../BaseWidget.h"
#include "../../utils/RunOnceAsync.h"

class DatetimeWidget : public BaseWidget {
    inline static const std::string DEFAULT_VIEW = "../views/datetimeWidget.xml";
    inline static const std::string URL = "https://quota.glitch.me/random";
    RunOnceAsync runOnceAsync;

public:
    explicit DatetimeWidget(BaseWidget* parent = nullptr);
    virtual ~DatetimeWidget() = default;
    const std::string& getDefaultViewPath() const override;
    void updateControllerInter(UpdateRate rate) override;
};


#endif //MIRROR_APP_DATETIMEWIDGET_H
