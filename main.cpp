
# include <SDL2/SDL_ttf.h>

# include <sdl_app_core/SdlApplication.hh>
# include <sdl_core/SdlWidget.hh>
# include <sdl_core/FontFactory.hh>
# include <sdl_graphic/LinearLayout.hh>
# include <sdl_graphic/GridLayout.hh>
# include <sdl_graphic/PictureWidget.hh>
# include <sdl_graphic/LabelWidget.hh>
# include <core_utils/StdLogger.hh>
# include <core_utils/LoggerLocator.hh>

int main(int argc, char* argv[]) {
  // Create the logger.
  utils::StdLogger logger;
  utils::LoggerLocator::provide(&logger);

  const std::string service("playground");
  const std::string module("main");

  // Run the application.
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    utils::LoggerLocator::getLogger().logMessage(
      utils::Level::Fatal,
      std::string("Could not initialize SDL lib"),
      module,
      service,
      SDL_GetError()
    );
    return EXIT_FAILURE;
  }

  // Create the application window.
  const std::string appName = std::string("sdl_playground");
  const std::string appTitle = std::string("Sdl playground (but this is still SPARTA !)");
  const std::string appIcon = std::string("data/img/65px-Stop_hand.BMP");
  const utils::Size<int> size(640, 480);

  try {
    sdl::app::SdlApplicationShPtr app = std::make_shared<sdl::app::SdlApplication>(appName, appTitle, appIcon, size, 60.0f, 30.0f);

    // `root_widget`
    sdl::core::SdlWidgetShPtr root_widget = std::make_shared<sdl::core::SdlWidget>(
      std::string("root_widget"),
      utils::Sizef(600.0f, 440.0f),
      nullptr,
      false,
      sdl::core::Palette::fromBackgroundColor(sdl::core::Color(255, 0, 0, SDL_ALPHA_OPAQUE))
    );
    root_widget->setRenderingArea(utils::Boxf(320.0f, 240.0f, 600.0f, 440.0f));

    // `root_widget` layout
    sdl::graphic::GridLayoutShPtr layout = std::make_shared<sdl::graphic::GridLayout>(5u, 4u, 10.0f, root_widget.get());
    // root_widget->setLayout(std::make_shared<sdl::graphic::LinearLayout>(sdl::graphic::LinearLayout::Direction::Vertical, 5.0f, 10.0f, widget.get()));

    // `left_widget`
    sdl::graphic::PictureWidget* left_widget = new sdl::graphic::PictureWidget(
      std::string("left_widget"),
      std::string("data/img/daybreak_Overwerk.bmp"),
      sdl::graphic::PictureWidget::Mode::Fit,
      // root_widget.get(),
      nullptr,
      false,
      sdl::core::Palette::fromBackgroundColor(sdl::core::Color(0, 255, 0, SDL_ALPHA_OPAQUE)),
      utils::Sizef(100.0f, 100.0f)
    );
    left_widget->setMinSize(utils::Sizef(50.0f, 5.0f));

    // `middle_widget`
    sdl::core::SdlWidget* middle_widget = new sdl::core::SdlWidget(
      std::string("middle_widget"),
      utils::Sizef(50.0f, 110.0f),
      // root_widget.get()
      nullptr,
      false,
      sdl::core::Palette::fromBackgroundColor(sdl::core::Color(128, 128, 0, SDL_ALPHA_OPAQUE))
    );

    // `right_widget`
    sdl::graphic::LabelWidget* right_widget = new sdl::graphic::LabelWidget(
      std::string("right_widget"),
      std::string("This is some bg text"),
      sdl::core::FontFactory::getInstance().createColoredFont(
        std::string("data/fonts/times.ttf"),
        sdl::core::Color(64, 64, 64, SDL_ALPHA_OPAQUE),
        20
      ),
      sdl::graphic::LabelWidget::HorizontalAlignment::Right,
      sdl::graphic::LabelWidget::VerticalAlignment::Center,
      // root_widget.get(),
      nullptr,
      true,
      sdl::core::Palette::fromBackgroundColor(sdl::core::Color(0, 0, 255, SDL_ALPHA_OPAQUE))
    );
    // right_widget->setSizePolicy(sdl::core::SizePolicy(
    //   sdl::core::SizePolicy::Minimum,
    //   sdl::core::SizePolicy::Minimum
    // ));
    right_widget->setMaxSize(utils::Sizef(180.0f, 60.0f));

    layout->setColumnsMinimumWidth(2.0f);
    layout->setRowsMinimumHeight(3.0f);
    layout->addItem(left_widget, 0, 0, 1, 1);
    layout->addItem(middle_widget, 1, 2, 1, 1);
    layout->addItem(right_widget, 3, 3, 1, 1);
    root_widget->setLayout(layout);

    // Setup application
    app->addWidget(root_widget);

    // Run it.
    app->run();
  }
  catch (const utils::CoreException& e) {
    utils::LoggerLocator::getLogger().logMessage(
      utils::Level::Critical,
      std::string("Caught internal exception while setting up application"),
      module,
      service,
      e.what()
    );
  }
  catch (const std::exception& e) {
    utils::LoggerLocator::getLogger().logMessage(
      utils::Level::Critical,
      std::string("Caught exception while setting up application"),
      module,
      service,
      e.what()
    );
  }
  catch (...) {
    utils::LoggerLocator::getLogger().logMessage(
      utils::Level::Critical,
      std::string("Unexpected error while setting up application"),
      module,
      service
    );
  }

  // Unload used fonts.
  sdl::core::FontFactory::getInstance().releaseFonts();

  // Unload the sdl and the ttf libs if needed.
  if (TTF_WasInit()) {
    TTF_Quit();
  }
  if (SDL_WasInit(0u)) {
    SDL_Quit();
  }

  // All is good.
  return EXIT_SUCCESS;
}
