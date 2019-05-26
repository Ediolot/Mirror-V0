//
// Created by jsier on 17/05/2019.
//

#ifndef MIRROR_APP_MAINACTIVITY_H
#define MIRROR_APP_MAINACTIVITY_H


#include "../BaseActivity.h"

class MainActivity : public BaseActivity {
public:
    inline static const std::string DEFAULT_VIEW = "../views/activity/mainActivity.xml";

public:
    explicit MainActivity();
    const std::string& getDefaultViewPath() const override;
};


#endif //MIRROR_APP_MAINACTIVITY_H
