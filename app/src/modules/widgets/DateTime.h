//
// Created by jsier on 02/05/2019.
//

#ifndef MIRROR_APP_DATETIME_H
#define MIRROR_APP_DATETIME_H


#include "basic/Widget.h"
#include "basic/Text.h"

class DateTime : public Widget {
    Text date;
    Text time;

public:
    explicit DateTime(const Widget* parent = nullptr, int x = 0, int y = 0, Size size = Size(-1, -1), Size minSize = Size(-1, -1));
    void draw() override;
    void update() override;

private:
    void setDateTime(std::string &date, std::string &time);
};


#endif //MIRROR_APP_DATETIME_H
