#include <iostream>
#include <vector>

//SUCCESS - М-да, жалко на эту задачу 5 минут, фигня

enum winner_t {
    GELLYFISH,
    FLOWER
};

winner_t find_winner(int gellyfish_hp, int flower_hp, int gellyfish_knight_hp, int flower_knight_hp) {
    /*
    Итак, 2 действия
    Если ход нечетный - бъет Гелифиш, он может либо забрать 1-цу у flower_hp, либо у flower_knight_hp
    Аналогично Flower, в свой ход
    Тогда если здоровье рыцаря больше здоровья владельца - лучше сразу бить по владельцу, иначе только по рыцарю, потому что если рыцарь будет побеждён, то будет побежден и игрок
    Игра зависит от того, кто начал первый ход и у кого наименьшее здоровье
    */
    int gellyfish_min = std::min(gellyfish_hp, gellyfish_knight_hp);
    int flower_min = std::min(flower_hp, flower_knight_hp);
    if (gellyfish_min >= flower_min) {
        return GELLYFISH;
    }
    return FLOWER;
}

int main(void) {
    unsigned int t;
    int gellyfish_hp, gellyfish_knight_hp, flower_hp, flower_knight_hp;
    std::cin >> t;
    for (unsigned int ti = 0; ti < t; ++ti) {
        std::cin >> gellyfish_hp >> flower_hp >> gellyfish_knight_hp >> flower_knight_hp;
        switch (find_winner(gellyfish_hp, flower_hp, gellyfish_knight_hp, flower_knight_hp))
        {
        case GELLYFISH:
            std::cout << "Gellyfish" << std::endl;
            break;
        
        default:
            std::cout << "Flower" << std::endl;
        }
    }
    return 0;
}