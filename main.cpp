#include <QApplication>
#include <QPushButton>
#include <QSettings>
#include <QSplashScreen>

#include <FairWindSdk/FairWind.hpp>
#include <FairWindSdk/settings/FairComboBox.hpp>
#include <FairWindSdk/settings/FairLineEdit.hpp>
#include <FairWindSdk/settings/FairCheckBox.hpp>
#include <FairWindSdk/settings/DisplaysBrowser.hpp>
#include <FairWindSdk/settings/LayersBrowser.hpp>
#include <ui/settings/connections/Connections.hpp>
#include <ui/settings/generic/Generic.hpp>
#include <ui/settings/applications/Applications.hpp>

#include <ui/settings/generic/Generic.hpp>

#include "ui/MainWindow.hpp"

/*
 * main
 * FairWind++ starting point
 */
int main(int argc, char *argv[]) {

    // Enable OpenGL shared contexts
    QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts );

    // Enable DPI scaling
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    // Enable high DPI support
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

    // Create the application

    QApplication app(argc, argv);
    // Get the splash screen logo
    QPixmap pixmap(":/resources/images/other/splash_logo.png");
    // Create a splash screen containing the logo
    QSplashScreen splash(pixmap);
    // Show the logo
    splash.show();

    // Get the FairWind singleton
    auto fairWind = fairwind::FairWind::getInstance();

    // Register settings pages inside the FairWind singleton
    fairWind->registerSettingsTab(new fairwind::ui::settings::generic::Generic());
    fairWind->registerSettingsTab(new fairwind::ui::settings::connections::Connections());
    fairWind->registerSettingsTab(new fairwind::ui::settings::applications::Applications());

    // Register the settings widgets inside the FairWind singleton
    fairWind->registerSettings(new fairwind::ui::settings::FairComboBox());
    fairWind->registerSettings(new fairwind::ui::settings::FairLineEdit());
    fairWind->registerSettings(new fairwind::ui::settings::FairCheckBox());
    fairWind->registerSettings(new fairwind::ui::settings::DisplaysBrowser());
    fairWind->registerSettings(new fairwind::ui::settings::LayersBrowser());

    splash.showMessage("Loading Applications ...", 500, Qt::white);

    // Set apps path
    fairWind->setApplicationDirPath(QApplication::applicationDirPath().left(1));
    // Load the apps inside the FairWind singleton itself
    fairWind->loadApps();

    splash.showMessage("Loading Settings ...", 500, Qt::white);

    // Load the configuration inside the FairWind singleton itself
    fairWind->loadConfig();

    splash.showMessage("Loading Organization Name", 500, Qt::white);

    // Set organisation name
    QCoreApplication::setOrganizationName("uniparthenope");

    // Set the window icon
    app.setWindowIcon(QIcon(QPixmap::fromImage(QImage(":/resources/images/icons/fairwind_icon.png"))));

    // Create a new MainWindow object
    fairwind::ui::MainWindow w;

    // Register the main window
    fairWind->setMainWindow(&w);

    // Close the splash screen presenting the MainWindow UI
    splash.finish(&w);
    return QApplication::exec();
}
