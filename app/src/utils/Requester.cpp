//
// Created by jsier on 29/05/2019.
//

#include <curl/curl.h>
#include <iostream>
#include <allegro5/file.h>
#include <allegro5/allegro_memfile.h>
#include "Requester.h"

void Requester::start() {
    curl_global_init(CURL_GLOBAL_DEFAULT);
}

void Requester::end() {
    curl_global_cleanup();
}

Requester::Requester(const std::string& url)
    : d({nullptr, 0})
{
    CURL *curl;
    CURLcode res;
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, Requester::writeFunc);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &this->d);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        if (res != CURLE_OK) {
            free(d.bytes);
            d.bytes = nullptr;
            d.len = 0;
        }
        std::cout << "Response: " << res << std::endl;
    }
}

Requester::~Requester() {
    free(d.bytes);
}

size_t Requester::writeFunc(void *ptr, size_t size, size_t nmemb, Requester::data *requester) {
    size_t new_len = requester->len + size * nmemb;
    requester->bytes = realloc(requester->bytes, new_len+1);

    if (!requester->bytes) {
        std::cerr << "realloc() failed" << std::endl;
        return size * nmemb;
    }

    memcpy((char*)requester->bytes + requester->len, ptr, size * nmemb);
    requester->len = new_len;

    return size * nmemb;
}

std::string Requester::asString() const {
    return std::string((char*)d.bytes, d.len);
}

const Requester::data& Requester::asBytes() const {
    return d;
}

nlohmann::json Requester::asJson() const {
    nlohmann::json data;
    try {
        data = nlohmann::json::parse(asString());
    } catch (...) {
        return nlohmann::json("");
    }
    return data;
}

ALLEGRO_BITMAP *Requester::asAlBitmap(const std::string& extension) const {
    if (d.len == 0 || d.bytes == nullptr) {
        return nullptr;
    }

    ALLEGRO_FILE *f = al_open_memfile(d.bytes, d.len, "r");
    ALLEGRO_BITMAP *bitmap = al_load_bitmap_f(f, extension.c_str());
    al_fclose(f);

    return bitmap;
}
