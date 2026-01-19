#pragma once
#include "ECSConfig.h"
#include <functional>
#include <list>

namespace ECS {

    struct Event { virtual ~Event() = default; };

    class EventBus {
    public:
        template<typename TEvent>
        using Callback = std::function<void(const TEvent&)>;

        template<typename TEvent>
        void Subscribe(Callback<TEvent> callback) {
            auto typeIdx = std::type_index(typeid(TEvent));
            subscribers[typeIdx].push_back([callback](const Event& event) {
                callback(static_cast<const TEvent&>(event));
                });
        }

        template<typename TEvent, typename... Args>
        void Publish(Args&&... args) {
            TEvent event(std::forward<Args>(args)...);
            auto typeIdx = std::type_index(typeid(TEvent));
            if (subscribers.find(typeIdx) != subscribers.end()) {
                for (auto& callback : subscribers[typeIdx]) {
                    callback(event);
                }
            }
        }

    private:
        using Handler = std::function<void(const Event&)>;
        std::unordered_map<std::type_index, std::list<Handler>> subscribers;
    };
}