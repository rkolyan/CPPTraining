//
// Created by rkolyan on 11.04.2024.
//

#include <iostream>
#include <sstream>

void parse_chess_positions(const std::string &unparsed, int arr[3][2]) {
    std::stringstream stream(unparsed);
    std::string position;
    int i = 0;
    while (std::getline(stream, position, ' ')) {
        arr[i][0] = position[0] - 'a';
        arr[i][1] = position[1] - '1';
    }
}

enum Situation {
    STRANGE,
    NORMAL,
    CHECK,
    STALEMATE,
    CHECKMATE
};

enum Figure {
    WHITE_KING = 0,
    WHITE_ROOK = 1,
    BLACK_KING = 2,
};

Situation getSituation(const int arr[3][2]) {
    //1)Если белый король находится рядом с
    if (abs(arr[WHITE_KING][0] - arr[BLACK_KING][0]) <= 1 && abs(arr[WHITE_KING][1] - arr[WHITE_KING][1]) <= 1) {
        return STRANGE;
    } else if (arr[WHITE_KING][0] == arr[BLACK_KING][0] && arr[WHITE_KING][0] == arr[WHITE_ROOK][0]) {
        auto diff1 = arr[BLACK_KING][1] - arr[WHITE_KING][1];
        auto diff2 = arr[BLACK_KING][1] - arr[WHITE_ROOK][1];
        if (diff1 / abs(diff1) == diff2 / abs(diff2) && abs(diff2) > abs(diff1))
            return NORMAL;
        else
            return CHECK;
    } else if (arr[WHITE_KING][1] == arr[BLACK_KING][1] && arr[WHITE_KING][1] == arr[WHITE_ROOK][1]) {
        auto diff1 = arr[BLACK_KING][0] - arr[WHITE_KING][0];
        auto diff2 = arr[BLACK_KING][0] - arr[WHITE_ROOK][0];
        if (diff1 / abs(diff1) == diff2 / abs(diff2) && abs(diff2) > abs(diff1))
            return NORMAL;
        else
            return CHECK;
    } else if (arr[BLACK_KING][0] == 0 && arr[BLACK_KING][1] == 0) {
        /*
        if((arr[WHITE_KING][0] == 0 && arr[WHITE_KING][1] == 2 && arr[WHITE_ROOK][0] == 1 && arr[WHITE_ROOK][1] >= 1) ||
              (arr[WHITE_KING][1] == 0 && arr[WHITE_KING][0] == 2 && arr[WHITE_ROOK][1] == 1 && arr[WHITE_ROOK][0] >= 1))
            return STALEMATE;
        else if (true) {
            //Тут либо пат, либо мат, либо normal
        }
         */
        if (arr[WHITE_KING][0] == 0 && arr[WHITE_KING][1] == 2) {
            //TODO: Допиши, а то впадлу
        }
    } else if (arr[BLACK_KING][0] == 0 && arr[BLACK_KING][1] == 7 &&
            (arr[WHITE_KING][0] == 0 && arr[WHITE_KING][1] == 5 && arr[WHITE_ROOK][0] == 1 && arr[WHITE_ROOK][1] <= 6 || arr[WHITE_KING][1] == 7 && arr[WHITE_KING][0] == 2 && arr[WHITE_ROOK][1] == 6 && arr[WHITE_ROOK][0] >= 1)) {
        return STALEMATE;
    } else if (arr[BLACK_KING][0] == 7 && arr[BLACK_KING][1] == 0 &&
               (arr[WHITE_KING][0] == 5 && arr[WHITE_KING][1] == 0 && arr[WHITE_ROOK][1] == 1 && arr[WHITE_ROOK][0] <= 6 || arr[WHITE_KING][0] == 7 && arr[WHITE_KING][1] == 2 && arr[WHITE_ROOK][0] == 6 && arr[WHITE_ROOK][1] >= 1)) {
        return STALEMATE;
    } else if (arr[BLACK_KING][0] == 7 && arr[BLACK_KING][1] == 7 &&
            (arr[WHITE_KING][0] == 7 && arr[WHITE_KING][1] == 5 && arr[WHITE_KING]))
}

int main(void) {
    std::string unparsed;
    char positions[3][2];
    std::getline(std::cin, unparsed);
    parse_chess_positions(unparsed, positions);

}