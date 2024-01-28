
#include <functional>
#include <unordered_map>
#include <map>
#include <execution>
#include <algorithm>
#include <deque>
#include "Drawable.hpp"
#include <SDL_events.h>
#include <SDL_render.h>
#include "Global.cpp"
#pragma once



struct Scene
{
    using EventType = decltype(SDL_Event::type);
    using EventHandler = std::function<void(SDL_Event)>;
    using HandlerIter = std::unordered_multimap<EventType,EventHandler>::const_iterator;
    using LayerIndex = float;
    using Renderable = std::reference_wrapper<Drawable>;
    using RenderLayer = std::deque<Renderable>;

protected:

    bool keepRunning = true;

    /// @brief Current event being processed by play()
    SDL_Event curEvent;

    /// @brief Make sure your event handler captures your scene so that you can access stuff
    std::unordered_multimap<EventType,EventHandler> eventHandlers ;

    std::map<LayerIndex, RenderLayer> renderLayers ;

    /// @brief Called first when play() is called @pure
    virtual void begin () = 0;

    /// @brief Called after play() finishes
    virtual void end () = 0;

    /// @brief Handles all pending events using the eventHandlers
    void processInput() {
        while (SDL_PollEvent(&curEvent)) {
            const auto [begin, end] = eventHandlers.equal_range(curEvent.type);
            for (auto iter=begin; iter!=end; iter++) {
                iter->second(curEvent);
            }
        }
    }

    /// @brief Function to do generic calculations like physics
    virtual void doStuff() = 0;

    /// @brief Function to render the entire scene out
    void drawScene() {
        SDL_SetRenderDrawColor(screen, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(screen);
        for (auto& [index,layer] : renderLayers) {
            std::for_each(
                std::execution::par,
                layer.cbegin(), layer.cend(),
                [](const Renderable& s) {
                    s.get().draw();
                }
            );
        }
        SDL_RenderPresent(screen);
    }

public:

    Scene() :
        eventHandlers(),
        renderLayers()
    {}

    const HandlerIter bindEvent (const EventType& key, const EventHandler& func) {
        return eventHandlers.insert(std::pair<EventType,EventHandler>{key, func});
    }

    void unbindEvent (const HandlerIter& iter) {
        eventHandlers.erase(iter);
    }

    /// @brief Adds an object that inherits from Drawable (and implements draw) to the scene on the given layer
    /// @param layer Number to index the drawable, highest is on top
    /// @param obj Object REFERENCE, meaning the program will error if this object doesnt exist
    /// @throws SEGFAULT if `obj` doesn't exist while play() is executing
    void addDrawable (const LayerIndex& layer, Drawable& obj) {        
        renderLayers[layer].push_back(obj); // Implicitly constructs a Renderable
    }

    void play () {
        begin();
        while (keepRunning) {
            processInput();
            doStuff();
            drawScene();
        }
        end();
    }

    void stop () {
        keepRunning = false;
    }

};
