#include "easylogging++.h"
#include "MainWindow.h"


INITIALIZE_EASYLOGGINGPP


int main(int argc, char **argv) {
    Window window;
    window.run();

    LOG(INFO) << "Exited.";

    return EXIT_SUCCESS;
}
