#pragma once

#include <termios.h>
#include <unistd.h>
#include <sys/select.h>

bool kbhit() {
    termios oldt{}, newt{};
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    timeval tv{0, 0};
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    select(STDIN_FILENO + 1, &fds, nullptr, nullptr, &tv);

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return FD_ISSET(STDIN_FILENO, &fds);
}

char getch_noblock() {
    return kbhit() ? getchar() : 0;
}
