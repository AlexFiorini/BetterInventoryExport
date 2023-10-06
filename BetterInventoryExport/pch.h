#pragma once

#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS
#include "bakkesmod/plugin/bakkesmodplugin.h"

#include <string>
#include <vector>
#include <functional>
#include <memory>

template <typename T, typename std::enable_if<std::is_base_of<ObjectWrapper, T>::value>::type*>

void GameWrapper::HookEventWithCallerPost(std::string eventName,
    std::function<void(T caller, void* params, std::string eventName)> callback)
{
    auto wrapped_callback = [callback](ActorWrapper caller, void* params, std::string eventName)
        {
            callback(T(caller.memory_address), params, eventName);
        };
    HookEventWithCaller<ActorWrapper>(eventName, wrapped_callback);
}