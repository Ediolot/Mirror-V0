//
// Created by jsier on 27/05/2019.
//

#include "NewsWidget.h"
#include "../../utils/Utils.h"

using namespace nlohmann;

NewsWidget::NewsWidget(BaseWidget *parent)
    : BaseWidget(parent)
    , titles()
    , authors()
    , runOnceAsync()
{
    for (int i = 0; i < N_ARTICLES; ++i) {
        titles[i] = "";
        authors[i] = "";
    }
}

const std::string &NewsWidget::getDefaultViewPath() const {
    return DEFAULT_VIEW;
}

void NewsWidget::updateView() {
    BaseWidget::updateView();
}

void NewsWidget::updateControllerInter(BaseWidget::UpdateRate rate) {
    BaseWidget::updateControllerInter(rate);

    if (rateIs(rate, UpdateRate::EACH_MINUTE)) {
        runOnceAsync.run([&](){
            json data = Utils::requestJSON(URL);
            if (!data.empty()) {
                for (int i = 0; i < N_ARTICLES; ++i) {
                    std::string title, author;
                    try {
                        title = data["articles"][i]["title"];
                        author = data["articles"][i].is_null() ? "" : data["articles"][i]["author"];
                    } catch (...) {}
                    titles[i] = title;
                    authors[i] = author;
                    std::cout << title << " " << author << std::endl;
                }
            }
        });
    }
}
