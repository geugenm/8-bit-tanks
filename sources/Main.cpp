#include "easylogging++.h"
#include "MainWindow.h"


INITIALIZE_EASYLOGGINGPP


int main(int argc, char **argv) {
    LOG(INFO) << "Launched with '" << argc << "' parameter(s): " << argv[0];

    MainWindow window;
    window.run();

    LOG(INFO) << "Exited.";

    return EXIT_SUCCESS;
}
