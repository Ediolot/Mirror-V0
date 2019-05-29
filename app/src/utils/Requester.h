//
// Created by jsier on 29/05/2019.
//

#ifndef MIRROR_APP_REQUESTER_H
#define MIRROR_APP_REQUESTER_H

#include <string>
#include <json.h>
#include <allegro5/bitmap.h>

class Requester {
public:
    struct data {
        void *bytes;
        size_t len;
    };

    static void start();
    static void end();
    static ALLEGRO_BITMAP* dataToBitmap(const Requester::data& d, const std::string& extension = "");
    static std::string inferExtension(const std::string& url);

    explicit Requester(const std::string& url);
    virtual ~Requester();
    std::string asString() const;
    nlohmann::json asJson() const;
    const Requester::data& asBytes() const;
    ALLEGRO_BITMAP *asAlBitmap(std::string extension = "") const;

private:
    data d;
    std::string url;

    static size_t writeFunc(void *ptr, size_t size, size_t nmemb, data* requester);
};


#endif //MIRROR_APP_REQUESTER_H
