set(QT_VERSION 5)
find_package(Qt5 COMPONENTS WebEngineWidgets)
if (Qt5WebEngineWidgets_FOUND)
	set(GC1530_RESOURCE resourcesGC1530.qrc)
	qt5_add_resources(GC1530_RESOURCE_ADDED ${GC1530_RESOURCE})

	add_library(GC1530 SHARED
        	GC1530.cpp
        	GC1530.hpp
			MainPage.cpp MainPage.hpp MainPage.ui
        	WebView.cpp WebView.hpp
        	${GC1530_RESOURCE_ADDED}
            )

	add_dependencies(GC1530 FairWindSdk)
	add_dependencies(GC1530 QGeoView)
	target_link_libraries(GC1530 PRIVATE Qt5::Widgets Qt5::WebEngineWidgets Qt5::Network ${LIBQGEOVIEW} ${LIBFAIRWINDSDK})
	target_compile_options(GC1530 PRIVATE ${COMPILE_OPTIONS})

	add_custom_command(
        TARGET GC1530
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:GC1530>
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/apps/$<TARGET_FILE_NAME:GC1530>
	)
else()
        message("Qt5WebEngineWidgets not available.")
endif()
