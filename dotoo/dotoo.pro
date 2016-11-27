TEMPLATE    = subdirs
CONFIG      += ordered

# Define subdir projects
SUBDIRS     = \
            src \               # Contains all common source code.
            clientapp \         # QtWidgets project for client application.
            serverapp \         # QtCore application for server backend.
            qhttpserver \       # QHttpServer: See https://github.com/nikhilm/qhttpserver
            tests \             # Contains tests for src project.


# Define dependencies to ensure right build order:
clientapp.depends = src
serverapp.depends = src
serverapp.depends = qhttpserver
tests.depends = src
