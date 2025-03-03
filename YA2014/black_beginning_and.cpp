//
// Created by rkolyan on 16.01.2025.
//

#include <string>
#include <iostream>
#include <regex>

//SUCCESS

enum chess {
    NOT_ATTACK = 0,
    WHITE_KING_ATTACK = 1,
    WHITE_KING_STANDING = 2,
    WHITE_ROOK_ATTACK = 3,
};

void set_white_king(int desk[8][8], int i, int j) {
    desk[i][j] = WHITE_KING_STANDING;
    if (i == 0) {
        if (j != 0 && j != 7) {
            desk[i + 1][j - 1] = WHITE_KING_ATTACK;
            desk[i + 1][j] = WHITE_KING_ATTACK;
            desk[i + 1][j + 1] = WHITE_KING_ATTACK;
            desk[i][j - 1] = WHITE_KING_ATTACK;
            desk[i][j + 1] = WHITE_KING_ATTACK;
        } else if (j == 0) {
            desk[i + 1][j + 1] = WHITE_KING_ATTACK;
            desk[i + 1][j] = WHITE_KING_ATTACK;
            desk[i][j + 1] = WHITE_KING_ATTACK;
        } else {
            desk[i + 1][j - 1] = WHITE_KING_ATTACK;
            desk[i + 1][j] = WHITE_KING_ATTACK;
            desk[i][j - 1] = WHITE_KING_ATTACK;
        }
    } else if (i == 7) {
        if (j != 0 && j != 7) {
            desk[i - 1][j - 1] = WHITE_KING_ATTACK;
            desk[i - 1][j] = WHITE_KING_ATTACK;
            desk[i - 1][j + 1] = WHITE_KING_ATTACK;
            desk[i][j - 1] = WHITE_KING_ATTACK;
            desk[i][j + 1] = WHITE_KING_ATTACK;
        } else if (j == 0) {
            desk[i - 1][j + 1] = WHITE_KING_ATTACK;
            desk[i - 1][j] = WHITE_KING_ATTACK;
            desk[i][j + 1] = WHITE_KING_ATTACK;
        } else {
            desk[i - 1][j - 1] = WHITE_KING_ATTACK;
            desk[i - 1][j] = WHITE_KING_ATTACK;
            desk[i][j - 1] = WHITE_KING_ATTACK;
        }
    } else if (j == 0){
        desk[i - 1][j] = WHITE_KING_ATTACK;
        desk[i - 1][j + 1] = WHITE_KING_ATTACK;
        desk[i][j + 1] = WHITE_KING_ATTACK;
        desk[i + 1][j + 1] = WHITE_KING_ATTACK;
        desk[i + 1][j] = WHITE_KING_ATTACK;
    } else if (j == 7) {
        desk[i - 1][j] = WHITE_KING_ATTACK;
        desk[i - 1][j - 1] = WHITE_KING_ATTACK;
        desk[i][j - 1] = WHITE_KING_ATTACK;
        desk[i + 1][j - 1] = WHITE_KING_ATTACK;
        desk[i + 1][j] = WHITE_KING_ATTACK;
    } else {
        desk[i - 1][j - 1] = WHITE_KING_ATTACK;
        desk[i - 1][j] = WHITE_KING_ATTACK;
        desk[i - 1][j + 1] = WHITE_KING_ATTACK;
        desk[i + 1][j - 1] = WHITE_KING_ATTACK;
        desk[i + 1][j] = WHITE_KING_ATTACK;
        desk[i + 1][j + 1] = WHITE_KING_ATTACK;
        desk[i][j - 1] = WHITE_KING_ATTACK;
        desk[i][j + 1] = WHITE_KING_ATTACK;
    }
}

void set_white_rook(int desk[8][8], int i, int j) {
    for (int i1 = i; i1 >= 0; i1--) {
        if (desk[i1][j] == WHITE_KING_STANDING)
            break;
        if (desk[i1][j] == NOT_ATTACK)
            desk[i1][j] = WHITE_ROOK_ATTACK;
    }
    for (int i1 = i; i1 <= 7; i1++) {
        if (desk[i1][j] == WHITE_KING_STANDING)
            break;
        if (desk[i1][j] == NOT_ATTACK)
            desk[i1][j] = WHITE_ROOK_ATTACK;
    }
    for (int j1 = j; j1 >= 0; j1--) {
        if (desk[i][j1] == WHITE_KING_STANDING)
            break;
        if (desk[i][j1] == NOT_ATTACK)
            desk[i][j1] = WHITE_ROOK_ATTACK;
    }
    for (int j1 = j; j1 <= 7; j1++) {
        if (desk[i][j1] == WHITE_KING_STANDING)
            break;
        if (desk[i][j1] == NOT_ATTACK)
            desk[i][j1] = WHITE_ROOK_ATTACK;
    }
    if (desk[i][j] == WHITE_ROOK_ATTACK)
        desk[i][j] = NOT_ATTACK;
}

std::string check_array(const int *arr, int size) {
    bool not_attack_flag = false;
    for (int i = 1; i < size; i++) {
        if (arr[i] == WHITE_KING_STANDING)
            return "Strange";
        if (arr[i] == NOT_ATTACK) {
            not_attack_flag = true;
        }
    }
    if (not_attack_flag && arr[0] == WHITE_ROOK_ATTACK)
        return "Check";
    if (not_attack_flag)
        return "Normal";
    if (arr[0] == NOT_ATTACK)
        return "Stalemate";
    return "Checkmate";
}

std::string check_black_position(int desk[8][8], int i, int j) {
    int arr[9];
    arr[0] = desk[i][j];
    if ( i == 0 ) {
        if (j == 0) {
            arr[1] = desk[i][j + 1];
            arr[2] = desk[i + 1][j + 1];
            arr[3] = desk[i + 1][j];
            return check_array(arr, 4);
        } else if (j == 7) {
            arr[1] = desk[i][j - 1];
            arr[2] = desk[i + 1][j - 1];
            arr[3] = desk[i + 1][j];
            return check_array(arr, 4);
        } else {
            arr[1] = desk[i][j + 1];
            arr[2] = desk[i + 1][j + 1];
            arr[3] = desk[i + 1][j];
            arr[4] = desk[i][j - 1];
            arr[5] = desk[i + 1][j - 1];
            return check_array(arr, 6);
        }
    } else if (i == 7) {
        if (j == 0) {
            arr[1] = desk[i][j + 1];
            arr[2] = desk[i - 1][j + 1];
            arr[3] = desk[i - 1][j];
            return check_array(arr, 4);
        } else if (j == 7) {
            arr[1] = desk[i][j - 1];
            arr[2] = desk[i - 1][j - 1];
            arr[3] = desk[i - 1][j];
            return check_array(arr, 4);
        } else {
            arr[1] = desk[i][j + 1];
            arr[2] = desk[i - 1][j + 1];
            arr[3] = desk[i - 1][j];
            arr[4] = desk[i][j - 1];
            arr[5] = desk[i - 1][j - 1];
            return check_array(arr, 6);
        }
    } else if (j == 0) {
        arr[1] = desk[i - 1][j];
        arr[2] = desk[i - 1][j + 1];
        arr[3] = desk[i][j + 1];
        arr[4] = desk[i + 1][j + 1];
        arr[5] = desk[i + 1][j];
        return check_array(arr, 6);
    } else if (j == 7) {
        arr[1] = desk[i - 1][j];
        arr[2] = desk[i - 1][j - 1];
        arr[3] = desk[i][j - 1];
        arr[4] = desk[i + 1][j - 1];
        arr[5] = desk[i + 1][j];
        return check_array(arr, 6);
    }
    arr[1] = desk[i - 1][j + 1];
    arr[2] = desk[i][j + 1];
    arr[3] = desk[i + 1][j + 1];
    arr[4] = desk[i + 1][j];
    arr[5] = desk[i + 1][j - 1];
    arr[6] = desk[i][j - 1];
    arr[7] = desk[i - 1][j - 1];
    arr[8] = desk[i - 1][j];
    return check_array(arr, 9);
}

int main(int argc, char **argv) {
    //1)Создаем матрицу размером 8 на 8
    int desk[8][8] = {NOT_ATTACK}, i = 0, j = 0;
    std::string str;
    std::getline(std::cin, str);
    std::regex regex(R"([a-h][1-8])");
    auto str_begin = std::sregex_iterator(str.begin(), str.end(), regex);
    auto word = str_begin;
    //Белый король - окружение = 1, сам король = 2;
    i = word->str()[0] - 'a';
    j = word->str()[1] - '1';
    set_white_king(desk, i, j);
    word++;
    i = word->str()[0] - 'a';
    j = word->str()[1] - '1';
    set_white_rook(desk, i, j);
    word++;
    i = word->str()[0] - 'a';
    j = word->str()[1] - '1';
    std::cout << check_black_position(desk, i, j);
}