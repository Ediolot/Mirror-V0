//
// Created by jsier on 27/05/2019.
//

#include "NewsWidget.h"
#include "../../utils/Utils.h"
#include "TextWidget.h"
#include "ImageWidget.h"
#include "../../utils/Requester.h"

using namespace nlohmann;

NewsWidget::NewsWidget(BaseWidget *parent)
    : BaseWidget(parent)
    , runOnceAsync()
    , imagesNeedUpdate(false)
{}

const std::string &NewsWidget::getDefaultViewPath() const {
    return DEFAULT_VIEW;
}

void NewsWidget::updateControllerInter(BaseWidget::UpdateRate rate) {
    BaseWidget::updateControllerInter(rate);

    if (rateIs(rate, UpdateRate::EACH_HOUR)) {
        runOnceAsync.run([=](){
            json data = Requester(URL).asJson();
            if (data.empty()) {
                return;
            }

            for (int i = 0; i < N_ARTICLES; ++i) {
                std::string title, author, urlImage;
                try {
                    title = data["articles"][i]["title"];
                    author = data["articles"][i].is_null() ? "" : data["articles"][i]["author"];
                    urlImage = data["articles"][i].is_null() ? "" : data["articles"][i]["urlToImage"];
                } catch (...) {}

                auto titleWidget = (TextWidget*)getChild("title" + std::to_string(i + 1));
                auto imageWidget = (ImageWidget*)getChild("image" + std::to_string(i + 1));

                titleWidget->setText(title);
                if (!urlImage.empty()) {
                    ALLEGRO_BITMAP* bmp = Requester(urlImage).asAlBitmap();
                    if (bmp) {
                        imageWidget->setImage(bmp);
                    }
                }
            }
            imagesNeedUpdate.store(true);
        });
    }
}

void NewsWidget::updateView() {
    BaseWidget::updateView();

    if (imagesNeedUpdate.load()) {
        // Bitmaps that are not in the main thread are orphans memory bitmaps that need
        // to be converted into video bitmaps
        al_convert_memory_bitmaps();
        imagesNeedUpdate.store(false);
    }
}
