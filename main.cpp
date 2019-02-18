
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

    // Root widget
    sdl::core::SdlWidgetShPtr widget = std::make_shared<sdl::core::SdlWidget>(
      std::string("root_widget"),
      sdl::core::Boxf(320.0f, 240.0f, 600.0f, 440.0f),
      nullptr,
      false,
      sdl::core::Palette()//SDL_Color{255, 0, 0, SDL_ALPHA_OPAQUE}
    );
    widget->setLayout(std::make_shared<sdl::graphic::LinearLayout>(
      sdl::graphic::LinearLayout::Direction::Horizontal,
      5.0f,
      10.0f,
      widget.get()
    ));

    // Left widget
    // sdl::core::SdlWidget* widget2 = new sdl::core::SdlWidget(
    //   std::string("left_widget"),
    //   sdl::core::Boxf(),
    //   widget.get(),
    //   false,
    //   SDL_Color{0, 255, 0, SDL_ALPHA_OPAQUE / 2}
    // );
    sdl::graphic::PictureWidget* widget2 = new sdl::graphic::PictureWidget(
      std::string("left_widget"),
      std::string("data/img/daybreak_Overwerk.bmp"),
      sdl::graphic::PictureWidget::Mode::Fit,
      widget.get(),
      false,
      sdl::core::Palette()//SDL_Color{0, 255, 0, SDL_ALPHA_OPAQUE}
    );
    widget2->setLayout(std::make_shared<sdl::graphic::LinearLayout>(
      sdl::graphic::LinearLayout::Direction::Vertical,
      5.0f,
      10.0f,
      widget2
    ));

    sdl::core::SdlWidget* widget21 = new sdl::core::SdlWidget(
      std::string("widget21"),
      sdl::core::Boxf(),
      widget2,
      false,
      sdl::core::Palette()//SDL_Color{64, 64, 64, SDL_ALPHA_OPAQUE}
    );
    sdl::core::SdlWidget* widget22 = new sdl::core::SdlWidget(
      std::string("widget22"),
      sdl::core::Boxf(),
      widget2,
      false,
      sdl::core::Palette()//SDL_Color{64, 64, 64, SDL_ALPHA_OPAQUE / 2}
    );
    sdl::core::SdlWidget* widget23 = new sdl::core::SdlWidget(
      std::string("widget23"),
      sdl::core::Boxf(),
      widget2,
      false,
      sdl::core::Palette()//SDL_Color{64, 64, 64, SDL_ALPHA_TRANSPARENT}
    );
    sdl::core::SdlWidget* widget24 = new sdl::core::SdlWidget(
      std::string("widget24"),
      sdl::core::Boxf(),
      widget2,
      true,
      sdl::core::Palette()//SDL_Color{64, 64, 64, SDL_ALPHA_OPAQUE}
    );

    // Right widget
    // sdl::core::SdlWidget* widget3 = new sdl::core::SdlWidget(
    //   std::string("right_widget"),
    //   sdl::core::Boxf(),
    //   widget.get(),
    //   false,
    //   SDL_Color{0, 0, 255, SDL_ALPHA_OPAQUE}
    // );
    // sdl::graphic::PictureWidget* widget3 = new sdl::graphic::PictureWidget(
    //   std::string("right_widget"),
    //   std::string("data/img/daybreak_Overwerk.bmp"),
    //   sdl::graphic::PictureWidget::Mode::Crop,
    //   widget.get(),
    //   false,
    //   SDL_Color{0, 0, 255, SDL_ALPHA_OPAQUE}
    // );
    sdl::graphic::LabelWidget* widget3 = new sdl::graphic::LabelWidget(
      std::string("right_widget"),
      std::string("This is some bg text"),
      sdl::core::FontFactory::getInstance().createColoredFont(
        std::string("data/fonts/times.ttf"),
        SDL_Color{64, 64, 64, SDL_ALPHA_OPAQUE / 4},
        20
      ),
      sdl::graphic::LabelWidget::HorizontalAlignment::Right,
      sdl::graphic::LabelWidget::VerticalAlignment::Center,
      widget.get(),
      true,
      sdl::core::Palette()//SDL_Color{0, 0, 255, SDL_ALPHA_OPAQUE}
    );
    widget3->setLayout(std::make_shared<sdl::graphic::LinearLayout>(
      sdl::graphic::LinearLayout::Direction::Vertical,
      5.0f,
      10.0f,
      widget3
    ));

    // sdl::core::SdlWidget* widget31 = new sdl::core::SdlWidget(
    //   std::string("widget31"),
    //   sdl::core::Boxf(),
    //   widget3,
    //   false,
    //   SDL_Color{64, 64, 64, SDL_ALPHA_OPAQUE}
    // );
    // sdl::core::SdlWidget* widget32 = new sdl::core::SdlWidget(
    //   std::string("widget32"),
    //   sdl::core::Boxf(),
    //   widget3,
    //   false,
    //   SDL_Color{64, 64, 64, SDL_ALPHA_OPAQUE / 2}
    // );
    // sdl::core::SdlWidget* widget33 = new sdl::core::SdlWidget(
    //   std::string("widget33"),
    //   sdl::core::Boxf(),
    //   widget3,
    //   false,
    //   SDL_Color{64, 64, 64, SDL_ALPHA_TRANSPARENT}
    // );
    // sdl::core::SdlWidget* widget34 = new sdl::core::SdlWidget(
    //   std::string("widget34"),
    //   sdl::core::Boxf(),
    //   widget3,
    //   true,
    //   SDL_Color{64, 64, 64, SDL_ALPHA_OPAQUE}
    // );

    // sdl::graphic::PictureWidget* widget4 = new sdl::graphic::PictureWidget(
    //   std::string("widget4"),
    //   std::string("data/img/daybreak_Overwerk.bmp"),
    //   sdl::graphic::PictureWidget::Mode::Crop,
    //   widget3,
    //   false,
    //   SDL_Color{64, 64, 64, SDL_ALPHA_OPAQUE}
    // );
    // sdl::graphic::PictureWidget* widget5 = new sdl::graphic::PictureWidget(
    //   std::string("widget5"),
    //   std::string("data/img/daybreak_Overwerk.bmp"),
    //   sdl::graphic::PictureWidget::Mode::Crop,
    //   widget3,
    //   false,
    //   SDL_Color{64, 64, 64, SDL_ALPHA_OPAQUE / 2}
    // );
    // sdl::graphic::PictureWidget* widget6 = new sdl::graphic::PictureWidget(
    //   std::string("widget6"),
    //   std::string("data/img/daybreak_Overwerk.bmp"),
    //   sdl::graphic::PictureWidget::Mode::Crop,
    //   widget3,
    //   false,
    //   SDL_Color{64, 64, 64, SDL_ALPHA_TRANSPARENT}
    // );
    // sdl::graphic::PictureWidget* widget7 = new sdl::graphic::PictureWidget(
    //   std::string("widget7"),
    //   std::string("data/img/daybreak_Overwerk.bmp"),
    //   sdl::graphic::PictureWidget::Mode::Crop,
    //   widget3,
    //   true,
    //   SDL_Color{64, 64, 64, SDL_ALPHA_OPAQUE}
    // );

    sdl::graphic::LabelWidget* widget31 = new sdl::graphic::LabelWidget(
      std::string("widget31"),
      std::string("This is some text"),
      sdl::core::FontFactory::getInstance().createColoredFont(
        std::string("data/fonts/times.ttf"),
        SDL_Color{0, 0, 0, SDL_ALPHA_OPAQUE},
        20
      ),
      sdl::graphic::LabelWidget::HorizontalAlignment::Center,
      sdl::graphic::LabelWidget::VerticalAlignment::Center,
      widget3,
      false,
      sdl::core::Palette()//SDL_Color{64, 64, 64, SDL_ALPHA_OPAQUE}
    );
    sdl::graphic::LabelWidget* widget32 = new sdl::graphic::LabelWidget(
      std::string("widget32"),
      std::string("This is some text"),
      sdl::core::FontFactory::getInstance().createColoredFont(
        std::string("data/fonts/times.ttf"),
        SDL_Color{0, 0, 0, SDL_ALPHA_OPAQUE},
        20
      ),
      sdl::graphic::LabelWidget::HorizontalAlignment::Center,
      sdl::graphic::LabelWidget::VerticalAlignment::Center,
      widget3,
      false,
      sdl::core::Palette()//SDL_Color{64, 64, 64, SDL_ALPHA_OPAQUE / 2}
    );
    sdl::graphic::LabelWidget* widget33 = new sdl::graphic::LabelWidget(
      std::string("widget33"),
      std::string("This is some text"),
      sdl::core::FontFactory::getInstance().createColoredFont(
        std::string("data/fonts/times.ttf"),
        SDL_Color{0, 0, 0, SDL_ALPHA_OPAQUE},
        20
      ),
      sdl::graphic::LabelWidget::HorizontalAlignment::Center,
      sdl::graphic::LabelWidget::VerticalAlignment::Center,
      widget3,
      false,
      sdl::core::Palette()//SDL_Color{64, 64, 64, SDL_ALPHA_TRANSPARENT}
    );
    sdl::graphic::LabelWidget* widget34 = new sdl::graphic::LabelWidget(
      std::string("widget34"),
      std::string("This is some text"),
      sdl::core::FontFactory::getInstance().createColoredFont(
        std::string("data/fonts/times.ttf"),
        SDL_Color{0, 0, 0, SDL_ALPHA_OPAQUE / 2},
        20
      ),
      sdl::graphic::LabelWidget::HorizontalAlignment::Center,
      sdl::graphic::LabelWidget::VerticalAlignment::Center,
      widget3,
      false,
      sdl::core::Palette()//SDL_Color{64, 64, 64, SDL_ALPHA_OPAQUE}
    );

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
