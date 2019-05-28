//
// Created by jsier on 27/05/2019.
//

#ifndef MIRROR_APP_NEWSWIDGET_H
#define MIRROR_APP_NEWSWIDGET_H


#include "../BaseWidget.h"
#include "../../utils/RunOnceAsync.h"


class NewsWidget : public BaseWidget {
    inline static const std::string DEFAULT_VIEW = "../views/newsWidget.xml";
    inline static const std::string URL = "https://newsapi.org/v2/top-headlines?sources=google-news&apiKey=60c3f9243fdd46b19de6718608a13fd3";
    inline static const int N_ARTICLES = 4;
    RunOnceAsync runOnceAsync;

    std::string titles[N_ARTICLES];
    std::string authors[N_ARTICLES];

public:
    explicit NewsWidget(BaseWidget* parent = nullptr);
    virtual ~NewsWidget() = default;
    const std::string& getDefaultViewPath() const override;
    void updateView() override;
    void updateControllerInter(UpdateRate rate) override;
};


#endif //MIRROR_APP_NEWSWIDGET_H
