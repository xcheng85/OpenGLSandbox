set(APPS_DIRS
    MCApplication
)

foreach(APP ${APPS_DIRS})
    message("adding app: " ${APP})
    add_subdirectory(${APP})
endforeach(APP)
