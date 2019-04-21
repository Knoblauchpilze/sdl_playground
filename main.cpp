
# include <core_utils/StdLogger.hh>
# include <core_utils/LoggerLocator.hh>
# include <sdl_engine/SdlEngine.hh>

# include <sdl_app_core/SdlApplication.hh>
# include <sdl_core/SdlWidget.hh>
# include <sdl_engine/FontFactory.hh>
# include <sdl_graphic/LinearLayout.hh>
# include <sdl_graphic/GridLayout.hh>
# include <sdl_graphic/PictureWidget.hh>
# include <sdl_graphic/LabelWidget.hh>

# define ROOT_WIDGET

# define GRID_LAYOUT
// # define IDEAL_CASE

// # define LEFT_WIDGET
// # define MIDDLE_WIDGET
// # define SUB_MIDDLE_WIDGET
// # define SUB_LEFT_WIDGET

int main(int /*argc*/, char** /*argv[]*/) {
  // Create the logger.
  utils::StdLogger logger;
  utils::LoggerLocator::provide(&logger);

  const std::string service("playground");
  const std::string module("main");

  // Create the application window parameters.
  const std::string appName = std::string("sdl_playground");
  const std::string appTitle = std::string("Sdl playground (but this is still SPARTA !)");
  const std::string appIcon = std::string("data/img/65px-Stop_hand.BMP");
  const utils::Size<int> size(640, 480);

  sdl::app::SdlApplicationShPtr app = nullptr;

  try {
    app = std::make_shared<sdl::app::SdlApplication>(appName, appTitle, appIcon, size, 50.0f, 60.0f);

    // `root_widget`
# ifdef ROOT_WIDGET
    sdl::core::SdlWidgetShPtr root_widget = std::make_shared<sdl::core::SdlWidget>(std::string("root_widget"), utils::Sizef(600.0f, 440.0f), nullptr, sdl::core::engine::Color::NamedColor::Red);
    app->addWidget(root_widget);
    root_widget->setRenderingArea(utils::Boxf(320.0f, 240.0f, 600.0f, 440.0f));

#  ifdef GRID_LAYOUT
    sdl::graphic::GridLayoutShPtr layout = std::make_shared<sdl::graphic::GridLayout>(5u, 4u, 10.0f, root_widget.get());
#  else
    root_widget->setLayout(std::make_shared<sdl::graphic::LinearLayout>(sdl::graphic::LinearLayout::Direction::Horizontal, 5.0f, 10.0f, root_widget.get()));
#  endif
# endif

    // `left_widget`
# ifdef ROOT_WIDGET
#  ifdef LEFT_WIDGET
    sdl::graphic::PictureWidget* left_widget = new sdl::graphic::PictureWidget(std::string("left_widget"), std::string("data/img/daybreak_Overwerk.bmp"), sdl::graphic::PictureWidget::Mode::Fit,
#   ifdef GRID_LAYOUT
      nullptr,
#   else
      root_widget.get(),
#   endif
      sdl::core::engine::Color::NamedColor::Green,
#   ifdef IDEAL_CASE
      utils::Sizef()
#   else
      utils::Sizef(100.0f, 100.0f)
#   endif
    );
#   ifdef IDEAL_CASE
    left_widget->setImagePath(std::string("data/img/daybreak_Overwerk.bmp"));
#   else
    left_widget->setMinSize(utils::Sizef(1.0f, 5.0f));
#   endif
#  endif

    // `middle_widget`
#  ifdef MIDDLE_WIDGET
    sdl::core::SdlWidget* middle_widget = new sdl::core::SdlWidget(std::string("middle_widget"),
#   ifdef IDEAL_CASE
      utils::Sizef(),
#   else
      utils::Sizef(50.0f, 110.0f),
#   endif
#   ifdef GRID_LAYOUT
      nullptr,
#   else
      root_widget.get(),
#   endif
      sdl::core::engine::Color::fromRGB(0.5f, 0.5f, 0.0f)
    );
    middle_widget->setSizePolicy(sdl::core::SizePolicy(sdl::core::SizePolicy::Expanding, sdl::core::SizePolicy::Fixed));
#  endif

    // `right_widget`
#  ifdef RIGHT_WIDGET
    sdl::graphic::LabelWidget* right_widget = new sdl::graphic::LabelWidget(
      std::string("right_widget"),
      std::string("This is some bg text"),
      std::string("data/fonts/times.ttf"),
      15,
      sdl::graphic::LabelWidget::HorizontalAlignment::Right,
      sdl::graphic::LabelWidget::VerticalAlignment::Center,
#   ifdef GRID_LAYOUT
      nullptr,
#   else
      root_widget.get(),
#   endif
      sdl::core::engine::Color::NamedColor::Cyan
    );
    right_widget->setSizePolicy(sdl::core::SizePolicy(
      sdl::core::SizePolicy::Minimum,
      sdl::core::SizePolicy::Expanding
    ));
#   ifndef IDEAL_CASE
    right_widget->setMaxSize(utils::Sizef(180.0f, 60.0f));
#   endif
#  endif

    // `sub_middle_widget`
#  ifdef SUB_MIDDLE_WIDGET
    sdl::graphic::PictureWidget* sub_middle_widget = new sdl::graphic::PictureWidget(
      std::string("sub_middle_widget"),
      std::string("data/img/wp_awesome.bmp"),
      sdl::graphic::PictureWidget::Mode::Fit,
#   ifdef GRID_LAYOUT
      nullptr,
#   else
      root_widget.get(),
#   endif
      sdl::core::engine::Color::NamedColor::Green
    );
#   ifdef IDEAL_CASE
    sub_middle_widget->setImagePath(std::string("data/img/wp_awesome.bmp"));
#   else
    sub_middle_widget->setMinSize(utils::Sizef(390.0f, 70.0f));
#   endif
#  endif

    // `sub_left_widget`
#  ifdef SUB_LEFT_WIDGET
    sdl::graphic::PictureWidget* sub_left_widget = new sdl::graphic::PictureWidget(
      std::string("sub_left_widget"),
      std::string("data/img/wp_awesome.bmp"),
      sdl::graphic::PictureWidget::Mode::Fit,
#   ifdef GRID_LAYOUT
      nullptr,
#   else
      root_widget.get(),
#   endif
      sdl::core::engine::Color::NamedColor::Green
    );
#  endif

#  ifdef GRID_LAYOUT
    layout->setColumnsMinimumWidth(10.0f);
    layout->setRowsMinimumHeight(20.0f);
#   ifdef LEFT_WIDGET
    layout->addItem(left_widget,       0, 0, 1, 1);
#   endif
#   ifdef MIDDLE_WIDGET
    layout->addItem(middle_widget,     1, 2, 1, 1);
#   endif
#   ifdef RIGHT_WIDGET
    layout->addItem(right_widget,      3, 3, 1, 1);
#   endif
#   ifdef SUB_MIDDLE_WIDGET
    layout->addItem(sub_middle_widget, 3, 0, 1, 2);
#   endif
#   ifdef SUB_LEFT_WIDGET
    layout->addItem(sub_left_widget,   0, 3, 2, 1);
#   endif
    root_widget->setLayout(layout);
#  endif
# endif

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

  app.reset();

  // All is good.
  return EXIT_SUCCESS;
}
