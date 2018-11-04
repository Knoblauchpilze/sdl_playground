
# include <iostream>
# include <SDL2/SDL_ttf.h>

# include <sdl_core/SdlException.hh>
# include <sdl_app_core/SdlApplication.hh>
# include <sdl_core/SdlWidget.hh>
# include <sdl_graphic/LinearLayout.hh>
# include <sdl_graphic/GridLayout.hh>

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
      640,
      480,
      6.0f,
      3.0f
    );

    sdl::core::SdlWidgetShPtr widget = std::make_shared<sdl::core::SdlWidget>(
      std::string("Best widget in da place"),
      sdl::core::Boxf(320.0f, 240.0f, 400.0f, 200.0f),
      nullptr,
      SDL_Color{255, 128, 0, SDL_ALPHA_OPAQUE}
    );
    widget->setLayout(std::make_shared<sdl::graphic::LinearLayout>(
      sdl::graphic::LinearLayout::Direction::Horizontal,
      0.0f,
      10.0f,
      widget.get()
    ));

    sdl::core::SdlWidgetShPtr widget2 = std::make_shared<sdl::core::SdlWidget>(
      std::string("Second best widget in da place"),
      sdl::core::Boxf(),
      widget.get(),
      SDL_Color{128, 255, 0, SDL_ALPHA_OPAQUE}
    );


    sdl::core::SdlWidgetShPtr widget3 = std::make_shared<sdl::core::SdlWidget>(
      std::string("Not the best widget in da place"),
      sdl::core::Boxf(),
      widget.get(),
      SDL_Color{0, 255, 255, SDL_ALPHA_OPAQUE}
    );
    widget3->setLayout(std::make_shared<sdl::graphic::GridLayout>(
      3u,
      3u,
      5.0f,
      widget3.get()
    ));

    sdl::core::SdlWidgetShPtr widget4 = std::make_shared<sdl::core::SdlWidget>(
      std::string("Child of a widget which is not the best in da place"),
      sdl::core::Boxf(),
      widget.get(),
      SDL_Color{255, 255, 255, SDL_ALPHA_OPAQUE}
    );
    sdl::core::SdlWidgetShPtr widget5 = std::make_shared<sdl::core::SdlWidget>(
      std::string("Another child of a not so awesome widget in da place"),
      sdl::core::Boxf(),
      widget.get(),
      SDL_Color{255, 0, 255, SDL_ALPHA_OPAQUE}
    );
    sdl::core::SdlWidgetShPtr widget6 = std::make_shared<sdl::core::SdlWidget>(
      std::string("Clearly no the best child of a widget which is not the best in da place"),
      sdl::core::Boxf(),
      widget.get(),
      SDL_Color{0, 128, 255, SDL_ALPHA_OPAQUE}
    );

    widget3->addWidget(widget4, 0u, 0u, 1u, 1u);
    widget3->addWidget(widget5, 1u, 1u, 1u, 1u);
    widget3->addWidget(widget6, 2u, 2u, 1u, 1u);

    widget->addWidget(widget2);
    widget->addWidget(widget3);

    app->addWidget(widget);

    app->run();

    std::cout << "[MAIN] App stopped" << std::endl;
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
