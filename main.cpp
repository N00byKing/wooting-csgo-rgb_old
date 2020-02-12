#include <cmath>
#include <chrono>
#include <cstdio>
#include <thread>
#include <iostream>

#include <napi.h>
#include <json/json.h>

#include "wooting-rgb-sdk.h"

Napi::Number wooting_handle_event(const Napi::CallbackInfo& info) {
    wooting_rgb_kbd_connected();
    Napi::Env env = info.Env();

    Json::Value root;
    Json::Reader reader;
    std::string ding = info[0].As<Napi::String>().Utf8Value();
    printf(ding.c_str());
    reader.parse(info[0].As<Napi::String>().Utf8Value(), root);

    //Initial Reset
    for (int i = 0; i <= 16; i++) {
        for (int j = 0; j <= 5; j++) {
            wooting_rgb_array_set_single(j, i, 0, 0, 0);
        }   
    }

    //Team Parse
    std::string team = root["player"].get("team", "").asString();
    if (team == "CT") {
        for (int i = 14; i <= 16; i++) {
            for (int j = 0; j <= 5; j++) {
                wooting_rgb_array_set_single(j, i, 29, 138, 184);
            }
        }
    } else if (team == "T") {
        for (int i = 14; i <= 16; i++) {
            for (int j = 0; j <= 5; j++) {
                wooting_rgb_array_set_single(j, i, 222, 127, 62);
            }
        }
    }

    //Health Parse
    int hp = std::stoi(root["player"]["state"].get("health", "100").asString());
    int x = hp / 10;
    for (int i = 0; i < x; i++) {
        wooting_rgb_array_set_single(1, i + 1, 255, 0, 0);
    }

    //Kill Parse
    int kills = std::stoi(root["player"]["state"].get("round_kills", "0").asString());
    int killsHS = std::stoi(root["player"]["state"].get("round_killhs", "0").asString());
    if (kills > 5) {
        kills = 5;
    }
    if (killsHS > 5) {
        killsHS = 5;
    }
    while (kills > 0) {
        if (killsHS > 0) {
            wooting_rgb_array_set_single(kills, 0, 0, 255, 0);
            killsHS--;
        } else {
            wooting_rgb_array_set_single(kills, 0, 0, 0, 255);
        }
        kills--;
    }

    wooting_rgb_array_update_keyboard();

    return Napi::Number::New(env, 0);
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set(
        Napi::String::New(env, "wooting_handle_event"),
        Napi::Function::New(env, wooting_handle_event));
    return exports;
}

NODE_API_MODULE(addon, Init)
