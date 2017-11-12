#include "stdafx.h"
#include "MainWindow.h"
#include "Logger.h"
#include "Constants.h"


MainWindow::MainWindow() : RenderWindow(), Instance( APP_GUID )
{
    if (Instance.check())
    {
        create( sf::VideoMode( 0, 0 ), "", std::stoi(ConfigurationFile[CConfigurator::VIDEO_VideoMode]) );
    }
}


MainWindow::~MainWindow()
{
    LOG_TRACE("Destroyed main window");
}

int MainWindow::exec()
{
    using Clock = std::chrono::high_resolution_clock;
    using nanoseconds = std::chrono::nanoseconds;

    const long long nanosecond_per_frame = (1000 * 1000 * 1000) / 60;
    long long nano_behinds = 0;
    sf::Event event;

    while (isOpen())
    {
        auto t1 = Clock::now();

        while (pollEvent( event ))
        {
            LOG_TRACE(L"Event type got : %d", event.type);

            switch (event.type)
            {
            case sf::Event::Closed:
                this->close();
                break;
            case sf::Event::Resized: 
                break;
            case sf::Event::LostFocus: 
                break;
            case sf::Event::GainedFocus: 
                break;
            case sf::Event::TextEntered: 
                break;
            case sf::Event::KeyPressed: 
                break;
            case sf::Event::KeyReleased: 
                break;
            case sf::Event::MouseWheelMoved: 
                break;
            case sf::Event::MouseWheelScrolled: 
                break;
            case sf::Event::MouseButtonPressed: 
                break;
            case sf::Event::MouseButtonReleased: 
                break;
            case sf::Event::MouseMoved: 
                break;
            case sf::Event::MouseEntered: 
                break;
            case sf::Event::MouseLeft: 
                break;
            case sf::Event::JoystickButtonPressed: 
                break;
            case sf::Event::JoystickButtonReleased: 
                break;
            case sf::Event::JoystickMoved: 
                break;
            case sf::Event::JoystickConnected: 
                break;
            case sf::Event::JoystickDisconnected: 
                break;
            case sf::Event::TouchBegan: 
                break;
            case sf::Event::TouchMoved: 
                break;
            case sf::Event::TouchEnded: 
                break;
            case sf::Event::SensorChanged: 
                break;
            case sf::Event::Count: 
                break;
            default:
                LOG_ERROR(L"Invalid event type : %d", event.type);
                break;
            }
        }

        clear();

        // Should render things here

        display();

        auto t2 = Clock::now();

        auto timeElapsed = std::chrono::duration_cast<nanoseconds>(t2 - t1).count();

        if (nanosecond_per_frame - nano_behinds < timeElapsed)
        {
            LOG_WARN(L"Can't keep up !!! Behind %d nanoseconds", timeElapsed  - nanosecond_per_frame);
            //nano_behinds = timeElapsed - nanosecond_per_frame - nano_behinds;
        }
        else
        {
            std::this_thread::sleep_for( nanoseconds( nanosecond_per_frame - timeElapsed ) );
        }
    }

    return 0;
}

void MainWindow::addEvent( sf::Event::EventType const & eventType, std::function<void( sf::Event const& )> const & callback )
{
    m_EventCallbacks[eventType].push_back( callback );
}

void MainWindow::onCreate()
{
    this->setVerticalSyncEnabled(std::stoi(ConfigurationFile[CConfigurator::VIDEO_VSync]) == 1 );

    this->setSize( sf::Vector2u(std::stoi(ConfigurationFile[CConfigurator::VIDEO_ResolutionX]), std::stoi(ConfigurationFile[CConfigurator::VIDEO_ResolutionY]) ) );

    // This one should be fixed.
    this->setTitle( "My game template" );

    LOG_TRACE( "Created main window" );
}
