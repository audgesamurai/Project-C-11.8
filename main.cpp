#include <iostream>
#include <string>
using namespace std;

class DiskMover {
private:
    enum Stage { MOVE_FIRST_HALF, MOVE_BIG_ONE, MOVE_SECOND_HALF, DONE };

    int num;
    int from;
    int to;
    int temp;
    Stage step;

    DiskMover* firstHalf = nullptr;
    DiskMover* secondHalf = nullptr;

public:
    DiskMover(int n, int start, int end)
        : num(n), from(start), to(end), step(MOVE_FIRST_HALF) {
        temp = 6 - from - to;
        if (num == 1) {
            step = MOVE_BIG_ONE;
        }
    }

    ~DiskMover() {
        delete firstHalf;
        delete secondHalf;
    }

    bool has_more_moves() {
        return step != DONE;
    }

    string next_move() {
        if (num == 1) {
            step = DONE;
            return "Move 1 disk from peg " + to_string(from) + " to peg " + to_string(to);
        }

        if (step == MOVE_FIRST_HALF) {
            if (firstHalf == nullptr) {
                firstHalf = new DiskMover(num - 1, from, temp);
            }

            if (firstHalf->has_more_moves()) {
                return firstHalf->next_move();
            } else {
                step = MOVE_BIG_ONE;
            }
        }

        if (step == MOVE_BIG_ONE) {
            step = MOVE_SECOND_HALF;
            return "Move disk " + to_string(num) + " from peg " + to_string(from) + " to peg " + to_string(to);
        }

        if (step == MOVE_SECOND_HALF) {
            if (secondHalf == nullptr) {
                secondHalf = new DiskMover(num - 1, temp, to);
            }

            if (secondHalf->has_more_moves()) {
                return secondHalf->next_move();
            } else {
                step = DONE;
            }
        }

        return "";
    }
};

int main() {
    DiskMover hanoi(4, 1, 3);

    while (hanoi.has_more_moves()) {
        cout << hanoi.next_move() << endl;
    }

    return 0;
}

