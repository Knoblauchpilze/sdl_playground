
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
# include <sdl_graphic/SelectorWidget.hh>
# include <sdl_graphic/ComboBox.hh>
# include <sdl_graphic/TabWidget.hh>
# include <sdl_graphic/TextBox.hh>

# define ROOT_WIDGET

# define GRID_LAYOUT
// # define IDEAL_CASE

# define LEFT_WIDGET
# define RIGHT_WIDGET
# define MIDDLE_WIDGET
# define SUB_MIDDLE_WIDGET
# define SUB_LEFT_WIDGET
# define INTER_LEFT_WIDGET
# define SUB_RIGHT_WIDGET

// # define MENU_BAR_DOCK_WIDGET
// # define TOP_DOCK_WIDGET

// # define RIGHT_DOCK_WIDGET
// # define TAB_WIDGET
// # define TAB_WIDGET_2

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
  const utils::Sizei size(640, 480);

  sdl::app::SdlApplicationShPtr app = nullptr;

  try {
    app = std::make_shared<sdl::app::SdlApplication>(appName, appTitle, appIcon, size, true, 50.0f, 60.0f);

    // `root_widget`
# ifdef ROOT_WIDGET
    sdl::graphic::PictureWidget* root_widget = new sdl::graphic::PictureWidget(
      std::string("root_widget"),
      std::string("data/img/wp_not_so_awesome.bmp"),
      sdl::graphic::PictureWidget::Mode::Fit,
      nullptr,
      sdl::core::engine::Color::NamedColor::Green
    );
    app->setCentralWidget(root_widget);
#  ifdef GRID_LAYOUT
    sdl::graphic::GridLayoutShPtr layout = std::make_shared<sdl::graphic::GridLayout>(
      std::string("grid_layout_for_root"),
      root_widget,
      5u,
      4u,
      10.0f
    );
    layout->allowLog(false);
#  else
    sdl::graphic::LinearLayoutShPtr layout = std::make_shared<sdl::graphic::LinearLayout>(
      std::string("linear_layout_for_root"),
      root_widget,
      sdl::graphic::LinearLayout::Direction::Vertical,
      5.0f,
      10.0f
    );
#  endif
# endif

# ifdef MENU_BAR_DOCK_WIDGET
    sdl::graphic::PictureWidget* menu_bar = new sdl::graphic::PictureWidget(
      std::string("menu_bar"),
      std::string("data/img/menu_bar.bmp"),
      sdl::graphic::PictureWidget::Mode::Fit,
      nullptr,
      sdl::core::engine::Color::NamedColor::Magenta,
      utils::Sizef()
    );
    app->setMenuBar(menu_bar);
# endif
# ifdef TOP_DOCK_WIDGET
    sdl::graphic::ComboBox* top_dock_widget = new sdl::graphic::ComboBox(
      std::string("top_dock_widget"),
      sdl::graphic::ComboBox::InsertPolicy::InsertAtCurrent,
      nullptr,
      utils::Sizef()
    );
    app->addDockWidget(top_dock_widget, sdl::app::DockWidgetArea::TopArea);
    top_dock_widget->insertItem(std::string("Julia"), std::string("data/img/julia.bmp"));
    top_dock_widget->insertItem(std::string("romanesco"), std::string("data/img/romanesco.bmp"));
    top_dock_widget->insertItem(std::string("Big Benoit"), std::string("data/img/mandelbrot.bmp"));
# endif
# ifdef RIGHT_DOCK_WIDGET
#  ifndef ROOT_WIDGET
    sdl::graphic::TabWidget* right_dock_widget = new sdl::graphic::TabWidget(
      std::string("right_dock_widget"),
      nullptr,
      sdl::graphic::TabWidget::TabPosition::North
    );
    app->setCentralWidget(right_dock_widget);
#  endif

#  ifdef TAB_WIDGET
    sdl::graphic::PictureWidget* tab = new sdl::graphic::PictureWidget(
      std::string("moon"),
      std::string("data/img/fullmoon.bmp"),
      sdl::graphic::PictureWidget::Mode::Fit,
      nullptr,
      sdl::core::engine::Color::NamedColor::Purple,
      utils::Sizef()
    );
#  ifdef ROOT_WIDGET
    app->addDockWidget(tab, sdl::app::DockWidgetArea::RightArea);
#  else
    right_dock_widget->insertTab(0, tab, std::string("Test"));
#  endif
#  endif
#  ifdef TAB_WIDGET_2
    sdl::graphic::PictureWidget* tab2 = new sdl::graphic::PictureWidget(
      std::string("gany"),
      std::string("data/img/ganymede.bmp"),
      sdl::graphic::PictureWidget::Mode::Fit,
      nullptr,
      sdl::core::engine::Color::NamedColor::CorneFlowerBlue,
      utils::Sizef()
    );
#  ifdef ROOT_WIDGET
    app->addDockWidget(tab2, sdl::app::DockWidgetArea::RightArea);
#  else
    right_dock_widget->insertTab(0, tab2);
#  endif
#  endif
# endif

    // `left_widget`
# ifdef ROOT_WIDGET
#  ifdef LEFT_WIDGET
    sdl::graphic::PictureWidget* left_widget = new sdl::graphic::PictureWidget(
      std::string("left_widget"),
      std::string("data/img/daybreak_Overwerk.bmp"),
      sdl::graphic::PictureWidget::Mode::Fit,
      root_widget,
      sdl::core::engine::Color::NamedColor::Green,
#   ifdef IDEAL_CASE
      utils::Sizef()
#   else
      utils::Sizef(100.0f, 100.0f)
#   endif
    );
#  endif

    // `middle_widget`
#  ifdef MIDDLE_WIDGET
    sdl::core::SdlWidget* middle_widget = new sdl::core::SdlWidget(
      std::string("middle_widget"),
#   ifdef IDEAL_CASE
      utils::Sizef(),
#   else
      utils::Sizef(50.0f, 110.0f),
#   endif
      root_widget,
      sdl::core::engine::Color::fromRGBA(0.5f, 0.5f, 0.0f, 0.75f)
    );
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
      root_widget,
      sdl::core::engine::Color::NamedColor::Cyan
    );
#  endif

    // `sub_middle_widget`
#  ifdef SUB_MIDDLE_WIDGET
    sdl::graphic::SelectorWidget* sub_middle_widget = new sdl::graphic::SelectorWidget(
      std::string("sub_middle_widget"),
      root_widget,
      true,
      sdl::core::engine::Color::NamedColor::Green
    );
#  endif

    // `sub_left_widget`
#  ifdef SUB_LEFT_WIDGET
    sdl::graphic::SelectorWidget* sub_left_widget = new sdl::graphic::SelectorWidget(
      std::string("sub_left_widget"),
      root_widget,
      true,
      sdl::core::engine::Color::NamedColor::Green
    );
#  endif

   // `inter_left_widget`
#  ifdef INTER_LEFT_WIDGET
    sdl::graphic::ComboBox* inter_left_widget = new sdl::graphic::ComboBox(
      std::string("inter_left_widget"),
      sdl::graphic::ComboBox::InsertPolicy::InsertAtBottom,
      root_widget,
#   ifdef LEFT_WIDGET
      utils::Sizef()
#   else
      utils::Sizef(100.0f, 100.0f)
#   endif
    );
    inter_left_widget->insertItem(std::string("Energy"), std::string("data/img/resource_left_widget.bmp"));
    inter_left_widget->insertItem(std::string("Metal"), std::string("data/img/resource_1left_widgetbmp"));
    inter_left_widget->insertItem(std::string("Crystal"), std::string("data/img/resourceleft_widget2.bmp"));
    inter_left_widget->insertItem(std::string("Deuterium"), std::string("data/img/resource_3.bmp"));
    inter_left_widget->insertItem(std::string("Antimatter"));
#  endif

  // `sub_right_widget`
#  ifdef SUB_RIGHT_WIDGET
    sdl::graphic::TextBox* sub_right_widget = new sdl::graphic::TextBox(
      std::string("sub_right_widget"),
      root_widget,
      utils::Sizef()
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
#   ifdef INTER_LEFT_WIDGET
#    ifdef LEFT_WIDGET
    layout->addItem(inter_left_widget, 0, 1, 2, 1);
#    else
    layout->addItem(inter_left_widget, 0, 0, 1, 1);
#    endif
#   ifdef SUB_RIGHT_WIDGET
    // sub_right_widget->setPalette(sub_right_widget->getPalette());
    layout->addItem(sub_right_widget,  3, 1, 2, 2);
#   endif
#   endif
#  else
#   ifdef INTER_LEFT_WIDGET
    layout->addItem(inter_left_widget);
#   endif
#   ifdef LEFT_WIDGET
    layout->addItem(left_widget);
#   endif
#   ifdef MIDDLE_WIDGET
    layout->addItem(middle_widget);
#   endif
#   ifdef RIGHT_WIDGET
    layout->addItem(right_widget);
#   endif
#   ifdef SUB_MIDDLE_WIDGET
    layout->addItem(sub_middle_widget);
#   endif
#   ifdef SUB_LEFT_WIDGET
    layout->addItem(sub_left_widget);
#   endif
#   ifdef SUB_RIGHT_WIDGET
    layout->addItem(sub_right_widget);
#   endif
#  endif
    root_widget->setLayout(layout);

#  ifdef LEFT_WIDGET
#   ifdef IDEAL_CASE
    left_widget->setImagePath(std::string("data/img/daybreak_Overwerk.bmp"));
#   else
    left_widget->setMinSize(utils::Sizef(1.0f, 5.0f));
#   endif
#  endif
#  ifdef MIDDLE_WIDGET
#   if !defined(IDEAL_CASE) || !defined(GRID_LAYOUT)
    middle_widget->setSizePolicy(sdl::core::SizePolicy(sdl::core::SizePolicy::Expanding, sdl::core::SizePolicy::Fixed));
#   endif
#  endif
#  ifdef RIGHT_WIDGET
#   if !defined(IDEAL_CASE) || !defined(GRID_LAYOUT)
    right_widget->setMaxSize(utils::Sizef(180.0f, 60.0f));
    // right_widget->setSizePolicy(sdl::core::SizePolicy(
    //   sdl::core::SizePolicy::Minimum,
    //   sdl::core::SizePolicy::Expanding
    // ));
#   endif
#  endif
#  ifdef SUB_MIDDLE_WIDGET
#   ifdef IDEAL_CASE
    sub_middle_widget->setImagePath(std::string("data/img/wp_awesome.bmp"));
#   else
    sub_middle_widget->setMinSize(utils::Sizef(390.0f, 70.0f));
#   endif
#  endif
#  ifdef SUB_MIDDLE_WIDGET
    sdl::core::SdlWidget* child1 = new sdl::core::SdlWidget(std::string("child1"), utils::Sizef(), sub_middle_widget, sdl::core::engine::Color::NamedColor::Orange);
    sdl::core::SdlWidget* child2 = new sdl::core::SdlWidget(std::string("child2"), utils::Sizef(), sub_middle_widget, sdl::core::engine::Color::NamedColor::Magenta);
    sub_middle_widget->insertWidget(child1, 0);
    sub_middle_widget->insertWidget(child2, 0); 
#  endif
#  ifdef SUB_LEFT_WIDGET
    sdl::graphic::PictureWidget* img1 = new sdl::graphic::PictureWidget(std::string("img1"), std::string("data/img/1.bmp"), sdl::graphic::PictureWidget::Mode::Fit, sub_left_widget, sdl::core::engine::Color::NamedColor::Green);
    sdl::graphic::PictureWidget* img3 = new sdl::graphic::PictureWidget(std::string("img3"), std::string("data/img/3.bmp"), sdl::graphic::PictureWidget::Mode::Fit, sub_left_widget, sdl::core::engine::Color::NamedColor::Green);
    sdl::graphic::PictureWidget* img7 = new sdl::graphic::PictureWidget(std::string("img7"), std::string("data/img/7.bmp"), sdl::graphic::PictureWidget::Mode::Fit, sub_left_widget, sdl::core::engine::Color::NamedColor::Green);
    sub_left_widget->insertWidget(img1, 0);
    sub_left_widget->insertWidget(img3, 1);
    sub_left_widget->insertWidget(img7, 1);
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
