#ifndef INPUT_H
#define INPUT_H

#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

class Input {
public:
    Input() {
        tcgetattr(STDIN_FILENO, &oldTerm);
        newTerm = oldTerm;
        newTerm.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newTerm);

        oldFlags = fcntl(STDIN_FILENO, F_GETFL, 0);
        fcntl(STDIN_FILENO, F_SETFL, oldFlags | O_NONBLOCK);
    }

    ~Input() {
        tcsetattr(STDIN_FILENO, TCSANOW, &oldTerm);
        fcntl(STDIN_FILENO, F_SETFL, oldFlags);
    }

    bool kbhit() {
        char ch;
        int n = read(STDIN_FILENO, &ch, 1);

        if(n == 1){
            lastChar = ch;
            return true;
        }

        return false;
    }

    char getch() const {
        return lastChar;
    }

private:
    termios oldTerm;
    termios newTerm;
    int oldFlags;
    char lastChar = '\0';
};

#endif