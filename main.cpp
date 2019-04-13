
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
    app = std::make_shared<sdl::app::SdlApplication>(appName, appTitle, appIcon, size, 60.0f, 30.0f);

    // `root_widget`
# define ROOT_WIDGET
# ifdef ROOT_WIDGET
    sdl::core::SdlWidgetShPtr root_widget = std::make_shared<sdl::core::SdlWidget>(
      std::string("root_widget"),
      utils::Sizef(600.0f, 440.0f),
      nullptr,
      false,
      sdl::core::engine::Color::NamedColor::Red
    );
    root_widget->setRenderingArea(utils::Boxf(320.0f, 240.0f, 600.0f, 440.0f));
# endif

    // `root_widget` layout
# define GRID_LAYOUT
# ifdef ROOT_WIDGET
# ifdef GRID_LAYOUT
    sdl::graphic::GridLayoutShPtr layout = std::make_shared<sdl::graphic::GridLayout>(5u, 4u, 10.0f, root_widget.get());
# else
    root_widget->setLayout(std::make_shared<sdl::graphic::LinearLayout>(sdl::graphic::LinearLayout::Direction::Horizontal, 5.0f, 10.0f, root_widget.get()));
# endif
# endif

    // `left_widget`
# ifdef ROOT_WIDGET
# define OTHER_WIDGETS
# ifdef OTHER_WIDGETS
    sdl::graphic::PictureWidget* left_widget = new sdl::graphic::PictureWidget(
      std::string("left_widget"),
      std::string("data/img/daybreak_Overwerk.bmp"),
      sdl::graphic::PictureWidget::Mode::Fit,
# ifdef GRID_LAYOUT
      nullptr,
# else
      root_widget.get(),
# endif
      false,
      sdl::core::engine::Color::NamedColor::Green,
# ifdef IDEAL_CASE
      utils::Sizef()
# else
      utils::Sizef(100.0f, 100.0f)
# endif
    );
# ifndef IDEAL_CASE
    left_widget->setMinSize(utils::Sizef(1.0f, 5.0f));
# endif

    // `middle_widget`
    sdl::core::SdlWidget* middle_widget = new sdl::core::SdlWidget(
      std::string("middle_widget"),
# ifdef IDEAL_CASE
      utils::Sizef(),
# else
      utils::Sizef(50.0f, 110.0f),
# endif
# ifdef GRID_LAYOUT
      nullptr,
# else
      root_widget.get(),
# endif
      false,
      sdl::core::engine::Color::fromRGB(0.5f, 0.5f, 0.0f)
    );
    middle_widget->setSizePolicy(sdl::core::SizePolicy(
      sdl::core::SizePolicy::Expanding,
      sdl::core::SizePolicy::Fixed
    ));

    // `right_widget`
    sdl::graphic::LabelWidget* right_widget = new sdl::graphic::LabelWidget(
      std::string("right_widget"),
      std::string("This is some bg text"),
      std::string("data/fonts/times.ttf"),
      15,
      sdl::graphic::LabelWidget::HorizontalAlignment::Right,
      sdl::graphic::LabelWidget::VerticalAlignment::Center,
# ifdef GRID_LAYOUT
      nullptr,
# else
      root_widget.get(),
# endif
      true,
      sdl::core::engine::Color::NamedColor::Blue
    );
    right_widget->setSizePolicy(sdl::core::SizePolicy(
      sdl::core::SizePolicy::Minimum,
      sdl::core::SizePolicy::Expanding
    ));
# ifndef IDEAL_CASE
    right_widget->setMaxSize(utils::Sizef(180.0f, 60.0f));
# endif

    // `sub_middle_widget`
    sdl::graphic::PictureWidget* sub_middle_widget = new sdl::graphic::PictureWidget(
      std::string("sub_middle_widget"),
      std::string("data/img/wp_awesome.bmp"),
      sdl::graphic::PictureWidget::Mode::Fit,
# ifdef GRID_LAYOUT
      nullptr,
# else
      root_widget.get(),
# endif
      false,
      sdl::core::engine::Color::NamedColor::Green
    );
# ifndef IDEAL_CASE
    sub_middle_widget->setMinSize(utils::Sizef(390.0f, 70.0f));
# endif

    // `sub_left_widget`
// # define SUB_LEFT_WIDGET
# ifdef SUB_LEFT_WIDGET
    sdl::graphic::PictureWidget* sub_left_widget = new sdl::graphic::PictureWidget(
      std::string("sub_left_widget"),
      std::string("data/img/wp_awesome.bmp"),
      sdl::graphic::PictureWidget::Mode::Fit,
# ifdef GRID_LAYOUT
      nullptr,
# else
      root_widget.get(),
# endif
      false,
      sdl::core::engine::Color::NamedColor::Green
    );
# endif
# endif

# ifdef GRID_LAYOUT
    layout->setColumnsMinimumWidth(10.0f);
    layout->setRowsMinimumHeight(20.0f);
#  ifdef OTHER_WIDGETS
    layout->addItem(left_widget,       0, 0, 1, 1);
    layout->addItem(middle_widget,     1, 2, 1, 1);
    layout->addItem(right_widget,      3, 3, 1, 1);
    layout->addItem(sub_middle_widget, 3, 0, 1, 2);
# ifdef SUB_LEFT_WIDGET
    layout->addItem(sub_left_widget,   0, 3, 2, 1);
# endif
#  endif
    root_widget->setLayout(layout);
# endif
# endif

    // Setup application
# ifdef ROOT_WIDGET
    app->addWidget(root_widget);
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
