#include "Position.h"
#include "Entity.h"
#include "UnitSection.h"
#include "Unit.h"
#include "Battleship.h"
#include "Submarine.h"
#include "Support.h"
#include "Controller.h"
#include <memory>
#include <vector>


int main(int argc, char *argv[]) {

    
    Position pos1(1,1);
    Position pos2(1,5);
    std::cout << pos1 << std::endl;
    Entity entity1(pos1, 'X');
    std::cout  << entity1 << std::endl;
    UnitSection unitSection1(pos1, 'C');
    std::cout << unitSection1 << std::endl;
    Unit* battleship = new Battleship(pos1, pos2);
    std::cout << battleship << std::endl;
    Position pos3(1,1);
    Position pos4(1,3);
    Unit * support = new Support(pos3, pos4);
    std::cout << support << std::endl;
    Position pos5(1,1);
    Position pos6(1,1);
    Unit * submarine = new Submarine(pos5, pos6);
    std::cout << submarine << std::endl;

    Controller player1(true);
    

    player1.addUnit('C', Position(1,1), Position(1,5));
    player1.addUnit('S', Position(2,1), Position(2,3));
    player1.addUnit('E', Position(3,1), Position(3,1));
    try{
    player1.addUnit('C', Position(1,1), Position(5,1));
    }catch(std::invalid_argument e){
        std::cout << "Piazzamento fallito" << std::endl;
    }
    //battleship1->damage(Position(1,1));
    //std::cout << battleship1 << std::endl;
    //std::cout << player1;

    Controller player2(false);
    

    player2.addUnit('C', Position(1,1), Position(1,5));
    player2.addUnit('S', Position(2,1), Position(2,3));
    player2.addUnit('E', Position(3,1), Position(3,1));
    try{
    player2.addUnit('C', Position(1,1), Position(5,1));
    }catch(std::invalid_argument e){
        std::cout << "Piazzamento fallito" << std::endl;
    }

    //std::cout <<player2;


    std::vector<Entity> result = player1.action('C', Position(1,1), Position(1,1));
    std::vector<Entity> result2 = player2.action('C', Position(1,1), Position(1,1));
    player1.mergeEntities(result);
    player1.mergeEntities(result2);
std::cout <<"PLAYER 1 \n" <<player1;
    std::cout<<"PLAYER 2 \n" << player2;
    result = player2.action('S', Position(2,1), Position(2,4));
    result2 = player1.action('S', Position(2,1), Position(2,4));
    player2.mergeEntities(result);
    player2.mergeEntities(result2);
std::cout<<"PLAYER 1 \n" <<player1;
    std::cout<<"PLAYER 2 \n" << player2;
result = player1.action('E', Position(3,1), Position(3,2));
    result2 = player2.action('E', Position(3,1), Position(3,2));
    player1.mergeEntities(result);
    player1.mergeEntities(result2);


    std::cout<<"PLAYER 1 \n" <<player1;
    std::cout <<"PLAYER 2 \n"<< player2;
    return 0;
}