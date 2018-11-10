
# include <iostream>
# include <SDL2/SDL_ttf.h>

# include <sdl_core/SdlException.hh>
# include <sdl_app_core/SdlApplication.hh>
# include <sdl_core/SdlWidget.hh>
# include <sdl_graphic/LinearLayout.hh>
# include <sdl_graphic/GridLayout.hh>
# include <sdl_graphic/PictureContainer.hh>
# include <sdl_graphic/SelectorWidget.hh>

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
      1900,
      1060,
      6.0f,
      3.0f
    );

    // Root widget
    sdl::core::SdlWidgetShPtr widget = std::make_shared<sdl::core::SdlWidget>(
      std::string("root_widget"),
      sdl::core::Boxf(950.0f, 530.0f, 1900.0f, 1060.0f),
      nullptr,
      SDL_Color{255, 128, 0, SDL_ALPHA_OPAQUE}
    );
    widget->setLayout(std::make_shared<sdl::graphic::LinearLayout>(
      sdl::graphic::LinearLayout::Direction::Horizontal,
      0.0f,
      10.0f,
      widget.get()
    ));

    // Left widget
    sdl::core::SdlWidget* widget2 = new sdl::core::SdlWidget(
      std::string("left_widget"),
      sdl::core::Boxf(),
      widget.get(),
      SDL_Color{128, 255, 0, SDL_ALPHA_OPAQUE}
    );

    // Right widget
    sdl::graphic::SelectorWidget* widget3 = new sdl::graphic::SelectorWidget(
      std::string("selector_widget"),
      widget.get(),
      SDL_Color{0, 255, 255, SDL_ALPHA_OPAQUE}
    );

    // Internal selector widgets.
    for (int i = 216 ; i < 449 ; ++i) {
      sdl::graphic::PictureContainer* widgetI = new sdl::graphic::PictureContainer(
        std::string("selector_internal_") + std::to_string(i),
        std::string("data/img/155_named/") + std::to_string(i) + ".bmp",
        sdl::graphic::PictureContainer::Mode::Fit,
        widget3,
        SDL_Color{255, 255, 255, SDL_ALPHA_OPAQUE}
      );
    }
    sdl::graphic::PictureContainer* widget4 = new sdl::graphic::PictureContainer(
      std::string("selector_internal_1"),
      std::string("data/img/mini.bmp"),
      sdl::graphic::PictureContainer::Mode::Crop,
      widget3,
      SDL_Color{255, 255, 255, SDL_ALPHA_OPAQUE}
    );
    // sdl::graphic::PictureContainer* widget5 = new sdl::graphic::PictureContainer(
    //   std::string("selector_internal_2"),
    //   std::string("data/img/daybreak_Overwerk.bmp"),
    //   sdl::graphic::PictureContainer::Mode::Fit,
    //   widget3,
    //   SDL_Color{255, 0, 255, SDL_ALPHA_OPAQUE}
    // );

    widget3->setActiveWidget(0);

    // Setup application
    app->addWidget(widget);

    // Run it.
    app->run();
  }
  catch (const sdl::core::SdlException& e) {
    std::cerr << "[MAIN] Caught internal exception:" << std::endl << e.what() << std::endl;
  }

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
