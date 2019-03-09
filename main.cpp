
# include <iostream>
# include <SDL2/SDL_ttf.h>

# include <sdl_core/SdlException.hh>
# include <sdl_app_core/SdlApplication.hh>
# include <sdl_core/SdlWidget.hh>
# include <sdl_core/FontFactory.hh>
# include <sdl_graphic/LinearLayout.hh>
# include <sdl_graphic/GridLayout.hh>
# include <sdl_graphic/PictureWidget.hh>
# include <sdl_graphic/SelectorWidget.hh>
# include <sdl_graphic/LabelWidget.hh>

int main(int argc, char* argv[]) {
  // Run the application.
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    std::cerr << "[MAIN] Could not initialize sdl video mode (err: \"" << SDL_GetError() << "\")" << std::endl;
    return EXIT_FAILURE;
  }

  try {
    sdl::core::BasicSdlWindowShPtr app = std::make_shared<sdl::core::SdlApplication>(
      std::string("Sdl playground (but this is still SPARTA !)"),
      std::string("data/img/65px-Stop_hand.BMP"),
      640.0f,
      480.0f,
      60.0f,
      30.0f
    );

    // `root_widget`
    sdl::core::SdlWidgetShPtr widget = std::make_shared<sdl::core::SdlWidget>(
      std::string("root_widget"),
      sdl::utils::Sizef(600.0f, 440.0f),
      nullptr,
      false,
      sdl::core::Palette::fromBackgroundColor(sdl::core::Color(255, 0, 0, SDL_ALPHA_OPAQUE))
    );
    widget->setRenderingArea(sdl::utils::Boxf(320.0f, 240.0f, 600.0f, 440.0f));

    // `root_widget` layout
    sdl::graphic::GridLayoutShPtr layout = std::make_shared<sdl::graphic::GridLayout>(
      5u,
      4u,
      10.0f,
      widget.get()
    );
    // widget->setLayout(std::make_shared<sdl::graphic::LinearLayout>(
    //   sdl::graphic::LinearLayout::Direction::Vertical,
    //   5.0f,
    //   10.0f,
    //   widget.get()
    // ));

    // `left_widget`
    sdl::graphic::PictureWidget* widget2 = new sdl::graphic::PictureWidget(
      std::string("left_widget"),
      std::string("data/img/daybreak_Overwerk.bmp"),
      sdl::graphic::PictureWidget::Mode::Fit,
      nullptr,//widget.get(),
      false,
      sdl::core::Palette::fromBackgroundColor(sdl::core::Color(0, 255, 0, SDL_ALPHA_OPAQUE)),
      sdl::utils::Sizef(100.0f, 100.0f)
    );
    widget2->setMinSize(sdl::utils::Sizef(50.0f, 5.0f));
    // widget2->setSizePolicy(sdl::core::SizePolicy(
    //   sdl::core::SizePolicy::Expanding,
    //   sdl::core::SizePolicy::Expanding
    // ));

    // `middle_widget`
    sdl::core::SdlWidget* widget1 = new sdl::core::SdlWidget(
      std::string("middle_widget"),
      sdl::utils::Sizef(50.0f, 110.0f),
      nullptr,//widget.get(),
      false,
      sdl::core::Palette::fromBackgroundColor(sdl::core::Color(128, 128, 0, SDL_ALPHA_OPAQUE))
    );
    // widget1->setSizePolicy(sdl::core::SizePolicy(
    //   sdl::core::SizePolicy::Minimum,
    //   sdl::core::SizePolicy::Minimum
    // ));
    // widget1->setMaxSize(sdl::utils::Sizef(120.0f, 120.0f));

    // `right_widget`
    sdl::graphic::LabelWidget* widget3 = new sdl::graphic::LabelWidget(
      std::string("right_widget"),
      std::string("This is some bg text"),
      sdl::core::FontFactory::getInstance().createColoredFont(
        std::string("data/fonts/times.ttf"),
        sdl::core::Color(64, 64, 64, SDL_ALPHA_OPAQUE),
        20
      ),
      sdl::graphic::LabelWidget::HorizontalAlignment::Right,
      sdl::graphic::LabelWidget::VerticalAlignment::Center,
      nullptr,//widget.get(),
      true,
      sdl::core::Palette::fromBackgroundColor(sdl::core::Color(0, 0, 255, SDL_ALPHA_OPAQUE))
    );
    // widget3->setSizePolicy(sdl::core::SizePolicy(
    //   sdl::core::SizePolicy::Minimum,
    //   sdl::core::SizePolicy::Minimum
    // ));
    widget3->setMaxSize(sdl::utils::Sizef(180.0f, 60.0f));

    // `second_to_last_widget`
    sdl::core::SdlWidget* widget5 = new sdl::core::SdlWidget(
      std::string("second_to_last_widget"),
      sdl::utils::Sizef(20.0f, 20.0f),
      nullptr,//widget.get(),
      false,
      sdl::core::Palette::fromBackgroundColor(sdl::core::Color(0, 128, 255, SDL_ALPHA_OPAQUE / 2))
    );

    // `last_widget`
    sdl::core::SdlWidget* widget4 = new sdl::core::SdlWidget(
      std::string("last_widget"),
      sdl::utils::Sizef(),
      nullptr,//widget.get(),
      false,
      sdl::core::Palette::fromBackgroundColor(sdl::core::Color(0, 128, 0, SDL_ALPHA_OPAQUE / 2))
    );
    // widget4->setSizePolicy(sdl::core::SizePolicy(
    //   sdl::core::SizePolicy::Expand,
    //   sdl::core::SizePolicy::Expand
    // ));

    layout->setColumnsMinimumWidth(2.0f);
    layout->setRowsMinimumHeight(3.0f);
    layout->addItem(widget2, 0, 0, 1, 1);
    layout->addItem(widget1, 1, 2, 1, 1);
    layout->addItem(widget3, 3, 3, 1, 1);
    layout->addItem(widget4, 4, 3, 1, 1);
    layout->addItem(widget5, 0, 3, 1, 1);
    widget->setLayout(layout);

    // Setup application
    app->addWidget(widget);

    // Run it.
    app->run();
  }
  catch (const sdl::core::SdlException& e) {
    std::cerr << "[MAIN] Caught internal exception:" << std::endl << e.what() << std::endl;
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
