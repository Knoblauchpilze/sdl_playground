
# include <SDL2/SDL_ttf.h>

# include <sdl_core/SdlException.hh>
# include <sdl_app_core/SdlApplication.hh>
# include <sdl_core/SdlWidget.hh>
# include <sdl_core/FontFactory.hh>
# include <sdl_graphic/LinearLayout.hh>
# include <sdl_graphic/GridLayout.hh>
# include <sdl_graphic/PictureWidget.hh>
# include <sdl_graphic/LabelWidget.hh>

int main(int argc, char* argv[]) {
  // Run the application.
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    utils::core::Logger::getInstance().logCritical(
      std::string("Could not initialize SDL lib"),
      std::string("main"),
      SDL_GetError()
    );
    return EXIT_FAILURE;
  }

  try {
    sdl::app::BasicSdlWindowShPtr app = std::make_shared<sdl::app::SdlApplication>(
      std::string("sdl_playground"),
      std::string("Sdl playground (but this is still SPARTA !)"),
      std::string("data/img/65px-Stop_hand.BMP"),
      640.0f,
      480.0f,
      60.0f,
      30.0f
    );

    // `root_widget`
    sdl::core::SdlWidgetShPtr root_widget = std::make_shared<sdl::core::SdlWidget>(
      std::string("root_widget"),
      utils::maths::Sizef(600.0f, 440.0f),
      nullptr,
      false,
      sdl::core::Palette::fromBackgroundColor(sdl::core::Color(255, 0, 0, SDL_ALPHA_OPAQUE))
    );
    root_widget->setRenderingArea(utils::maths::Boxf(320.0f, 240.0f, 600.0f, 440.0f));

    // `root_widget` layout
    sdl::graphic::GridLayoutShPtr layout = std::make_shared<sdl::graphic::GridLayout>(
      5u,
      4u,
      10.0f,
      root_widget.get()
    );
    // widget->setLayout(std::make_shared<sdl::graphic::LinearLayout>(
    //   sdl::graphic::LinearLayout::Direction::Vertical,
    //   5.0f,
    //   10.0f,
    //   widget.get()
    // ));

    // `left_widget`
    sdl::graphic::PictureWidget* left_widget = new sdl::graphic::PictureWidget(
      std::string("left_widget"),
      std::string("data/img/daybreak_Overwerk.bmp"),
      sdl::graphic::PictureWidget::Mode::Fit,
      // root_widget.get(),
      nullptr,
      false,
      sdl::core::Palette::fromBackgroundColor(sdl::core::Color(0, 255, 0, SDL_ALPHA_OPAQUE)),
      utils::maths::Sizef(100.0f, 100.0f)
    );
    left_widget->setMinSize(utils::maths::Sizef(50.0f, 5.0f));
    // left_widget->setSizePolicy(sdl::core::SizePolicy(
    //   sdl::core::SizePolicy::Preferred,
    //   sdl::core::SizePolicy::Preferred
    // ));

    // `middle_widget`
    sdl::core::SdlWidget* middle_widget = new sdl::core::SdlWidget(
      std::string("middle_widget"),
      utils::maths::Sizef(50.0f, 110.0f),
      // root_widget.get(),
      nullptr,
      false,
      sdl::core::Palette::fromBackgroundColor(sdl::core::Color(128, 128, 0, SDL_ALPHA_OPAQUE))
    );
    // middle_widget->setSizePolicy(sdl::core::SizePolicy(
    //   sdl::core::SizePolicy::Minimum,
    //   sdl::core::SizePolicy::Minimum
    // ));
    // middle_widget->setMaxSize(utils::maths::Sizef(120.0f, 120.0f));

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
    right_widget->setMaxSize(utils::maths::Sizef(180.0f, 60.0f));

    // `second_to_last_widget`
    // sdl::core::SdlWidget* widget5 = new sdl::core::SdlWidget(
    //   std::string("second_to_last_widget"),
    //   utils::maths::Sizef(20.0f, 20.0f),
    //   // root_widget.get(),
    //   nullptr,
    //   false,
    //   sdl::core::Palette::fromBackgroundColor(sdl::core::Color(0, 128, 255, SDL_ALPHA_OPAQUE / 2))
    // );

    // `last_widget`
    // sdl::core::SdlWidget* widget4 = new sdl::core::SdlWidget(
    //   std::string("last_widget"),
    //   utils::maths::Sizef(),
    //   // root_widget.get(),
    //   nullptr,
    //   false,
    //   sdl::core::Palette::fromBackgroundColor(sdl::core::Color(0, 128, 0, SDL_ALPHA_OPAQUE / 2))
    // );

    layout->setColumnsMinimumWidth(2.0f);
    layout->setRowsMinimumHeight(3.0f);
    layout->addItem(left_widget, 0, 0, 2, 1);
    layout->addItem(middle_widget, 1, 2, 1, 1);
    layout->addItem(right_widget, 3, 3, 1, 1);
    // layout->addItem(widget4, 4, 3, 1, 1);
    // layout->addItem(widget5, 0, 3, 1, 1);
    root_widget->setLayout(layout);

    // Setup application
    app->addWidget(root_widget);

    // Run it.
    app->run();
  }
  catch (const utils::core::CoreException& e) {
    utils::core::Logger::getInstance().logCritical(
      std::string("Caught internal exception while setting up application"),
      std::string("main"),
      e.what()
    );
  }
  catch (const std::exception& e) {
    utils::core::Logger::getInstance().logCritical(
      std::string("Caught exception while setting up application"),
      std::string("main"),
      e.what()
    );
  }
  catch (...) {
    utils::core::Logger::getInstance().logCritical(
      std::string("Unexpected error while setting up application"),
      std::string("main")
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
