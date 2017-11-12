#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <unordered_map>
#include <functional>
#include "SFML/Window/Event.hpp"
#include "Configurator.h"
#include "CSingleInstanceChecker.h"

class MainWindow : sf::RenderWindow
{
public:
    MainWindow();
    ~MainWindow();

    /*
     * Main loop function.
     * This function will render the screen
     * @Return [int] : the application status once closed
     */
    int exec();

    /*
     * Add callback to the event loop
     * @param eventType : Type of event the callback will be called (mouse, keyboard, etc)
     * @param callback : callback binding to execute on that event
     */
    void addEvent( sf::Event::EventType const& eventType, std::function<void( sf::Event const& )> const& callback );

protected:
    void onCreate() override;

private:
    CSingleInstanceChecker Instance;
    CConfigurator ConfigurationFile;

    // Event loop members
    std::unordered_map<sf::Event::EventType, std::vector<std::function<void(sf::Event const&)>>> m_EventCallbacks;
};

