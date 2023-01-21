#include "Controller.h"

Controller::Controller(const bool & isFirstPlayer) {
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            enemyEntitiesMatrix[i][j] = nullptr;
        }
    }
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            unitsMatrix[i][j] = nullptr;
        }
    }
    listeningForActions = !isFirstPlayer;
}
std::vector<Entity> Controller::action(const char &type,  const Position & iSource, const Position & iTarget){
    if (listeningForActions){

 
    if (type=='C'){
        listeningForActions = !listeningForActions;
        if(unitsMatrix[iTarget.getIntY()-1][iTarget.getX()-1]){
            unitsMatrix[iTarget.getIntY()-1][iTarget.getX()-1]->damage(iTarget);
            removeDeadUnits();
            
            return std::vector<Entity> {Entity(iTarget, 'X')};
        }
        return std::vector<Entity> {Entity(iTarget, 'O')};
    }else if (type == 'S'){
        return std::vector<Entity> {};
    }
    else if (type == 'E'){
        std::vector<Entity> result;
        Position a(iTarget.getX()-2, iTarget.getIntY()-2);
        Position b(iTarget.getX()+2, iTarget.getIntY()+2);
        for(int i = 0; i< units.size(); i++){
            if(units[i]->getBow().isInside(a,b) || units[i]->getStern().isInside(a,b)){
                std::vector<UnitSection> sections = units[i]->getUnitSections();
                for(int j = 0; i < sections.size(); j++){
                    if(sections[i].getPos().isInside(a,b)){
                        if (sections[i].isAlive()){
                            result.push_back(Entity(sections[i].getPos(), 'Y'));
                        }else{
                            result.push_back(Entity(sections[i].getPos(), 'y'));
                        }
                    }
                }
            }
        }
        listeningForActions = !listeningForActions;
        return result;

    }else{
        throw std::invalid_argument("Invalid type");
    }

        listeningForActions = !listeningForActions;
         return std::vector<Entity> {};
    }else{
    
        if(!unitsMatrix[iSource.getIntY()-1][iSource.getX()-1]){
            throw std::invalid_argument("You picked a non existing unit");
        }
        char type = unitsMatrix[iSource.getIntY()-1][iSource.getX()-1]->getId();
        if (type == 'C'){
            
        }
        else if (type == 'S'){

            Position stern = unitsMatrix[iSource.getIntY()-1][iSource.getX()-1]->getStern();
            Position bow = unitsMatrix[iSource.getIntY()-1][iSource.getX()-1]->getBow();
            Position middle = unitsMatrix[iSource.getIntY()-1][iSource.getX()-1]->getMiddle();
            int xOffset = iTarget.getX()-middle.getX();
            int yOffset = iTarget.getIntY()-middle.getIntY();
            Position destStern(stern.getX()+xOffset, stern.getIntY()+yOffset);
            Position destBow(bow.getX()+xOffset, bow.getIntY()+yOffset);
            if(checkUnitPlacement(unitsMatrix[iSource.getIntY()-1][iSource.getX()-1], destStern, destBow)){
               unitsMatrix[iSource.getIntY()-1][iSource.getX()-1]->move(iTarget, unitsMatrix);
            }else{
                throw std::invalid_argument("There's already another unit there!");
            }
        }else if (type == 'E'){
            if (unitsMatrix[iTarget.getIntY()-1][iTarget.getX()-1] && unitsMatrix[iTarget.getIntY()-1][iTarget.getX()-1]!=unitsMatrix[iSource.getIntY()-1][iSource.getX()-1]){
                throw std::invalid_argument("There's already another unit there!");
            }else{
                unitsMatrix[iSource.getIntY()-1][iSource.getX()-1]->move(iTarget, unitsMatrix);
            }
        }else {
            throw std::invalid_argument("Invalid type");
        }


        listeningForActions = !listeningForActions;
        return std::vector<Entity> {};
    }
}

void Controller::removeDeadUnits() {
    for (int i = 0; i < units.size(); i++) {
        if (units[i]->getArmor() == 0) {
            std::cout << "Removed Unit: " << units[i] << "\n";

            if (units.size() == 1) {
                dead = true;
                return;
            }
            for (int j = 0; j < units[i]->getDimension(); j++) {
                if (units[i]->isVertical()) {
                    unitsMatrix[units[i]->getStern().getIntY() - 1 + j]
                               [units[i]->getStern().getX() - 1] = nullptr;
                } else {
                    unitsMatrix[units[i]->getStern().getIntY() - 1]
                               [units[i]->getStern().getX() - 1 + j] = nullptr;
                }
            }
            units.erase(units.begin() + i);

            return;
        }
    }
}

bool Controller::isDead() { return dead; }
bool Controller::checkUnitPlacement(std::shared_ptr<Unit>  initialUnit, const Position &a,
                                    const Position &b) const {
    Position smaller = (a < b) ? a : b;
    if (a.getX() == b.getX()) {
        for (int i = 0; i < a.distanceTo(b) + 1; i++) {
            if (unitsMatrix[smaller.getIntY() + i - 1][smaller.getX() - 1] && unitsMatrix[smaller.getIntY() + i - 1][smaller.getX() - 1] != initialUnit) {
                return false;
            }
        }
    } else if (a.getIntY() == b.getIntY()) {
        for (int i = 0; i < a.distanceTo(b) + 1; i++) {
            if (unitsMatrix[smaller.getIntY() - 1][smaller.getX() - 1 + i] && unitsMatrix[smaller.getIntY() - 1][smaller.getX() - 1 + i]!= initialUnit) {
                return false;
            }
        }
    } else {
        throw std::invalid_argument("The positions are not aligned");
    }

    return true;
}

void Controller::addUnit(const char &type, const Position &iStern,
                         const Position &iBow) {
    if (!checkUnitPlacement(nullptr, iBow, iStern)) {
        throw std::invalid_argument("The unit overlaps with another unit");
    }

    std::shared_ptr<Unit> iUnit = nullptr;
    if (type == 'C') {
        iUnit = std::make_shared<Battleship>(iStern, iBow);
    } else if (type == 'S') {
        iUnit = std::make_shared<Support>(iStern, iBow);
    } else if (type == 'E') {
        iUnit = std::make_shared<Submarine>(iStern, iBow);
    } else {
        throw std::invalid_argument("Invalid type");
    }
    units.push_back(iUnit);
    Position buffer = iUnit->getStern();
    for (int i = 0; i < iUnit->getDimension(); i++) {
        if (iUnit->isVertical()) {
            unitsMatrix[buffer.getIntY() - 1 + i][buffer.getX() - 1] = iUnit;
        } else {
            unitsMatrix[buffer.getIntY() - 1][buffer.getX() - 1 + i] = iUnit;
        }
    }
}

Controller::~Controller() {}

void Controller::mergeEntities(
    std::vector<Entity> iEnemyEntities) {
    for (int i = 0; i < iEnemyEntities.size(); i++) {
        if (enemyEntitiesMatrix[iEnemyEntities[i].getPos().getIntY() - 1]
                               [iEnemyEntities[i].getPos().getX() - 1] !=
            nullptr) {
            enemyEntitiesMatrix[iEnemyEntities[i].getPos().getIntY() - 1]
                               [iEnemyEntities[i].getPos().getX() - 1]
                                   ->setId(iEnemyEntities[i].getId());

        } else {
            std::shared_ptr<Entity> sharedPtr(new Entity(iEnemyEntities[i]));
            enemyEntities.push_back(sharedPtr);
            enemyEntitiesMatrix[sharedPtr->getPos().getIntY() - 1]
                               [sharedPtr->getPos().getX() - 1] = sharedPtr;
        }
    }
}

std::string columns[] = {" ",   "  1 ", " 2 ", " 3 ", " 4 ", " 5 ", " 6 ",
                         " 7 ", " 8 ",  " 9 ", " 10", " 11", " 12"};

void Controller::print(std::ostream &os) {
    for (int i = 0; i < 13; i++) {
        if (i == 0) {
            os << "  ╔═══╦═══╦═══╦═══╦═══╦═══╦═══╦═══╦═══╦═══╦═══╦═══╗";
            os << "        ";
            os << "  ╔═══╦═══╦═══╦═══╦═══╦═══╦═══╦═══╦═══╦═══╦═══╦═══╗\n";
        } else if (i < 12) {
            os << "\n  ╠═══╬═══╬═══╬═══╬═══╬═══╬═══╬═══╬═══╬═══╬═══╬═══╣";
            os << "        ";
            os << "  ╠═══╬═══╬═══╬═══╬═══╬═══╬═══╬═══╬═══╬═══╬═══╬═══╣\n";
        } else {
            os << "\n  ╚═══╩═══╩═══╩═══╩═══╩═══╩═══╩═══╩═══╩═══╩═══╩═══╝";
            os << "        ";
            os << "  ╚═══╩═══╩═══╩═══╩═══╩═══╩═══╩═══╩═══╩═══╩═══╩═══╝\n";
            for (int j = 0; j < 13; j++) {
                os << columns[j] << " ";
            }
            os << "        ";
            for (int j = 0; j < 13; j++) {
                os << columns[j] << " ";
            }
        }
        if (i < 12) {
            os << rows[i] << " ";
            for (int j = 0; j < 12; j++) {
                os << "║ ";
                if (unitsMatrix[i][j]) {
                    os << (char)(unitsMatrix[i][j]->isHitAt(
                                     Position(j + 1, i + 1))
                                     ? unitsMatrix[i][j]->getId()
                                     : unitsMatrix[i][j]->getId() + 32);
                } else {
                    os << " ";
                }
                os << " ";
                if (j == 11) {
                    os << "║";
                }
            }
            os << "        ";
            os << rows[i] << " ";
            for (int j = 0; j < 12; j++) {
                os << "║ ";
                if (enemyEntitiesMatrix[i][j]) {
                    os << enemyEntitiesMatrix[i][j]->getId();
                } else {
                    os << " ";
                }
                os << " ";
                if (j == 11) {
                    os << "║";
                }
            }
        }
    }
}

std::ostream &operator<<(std::ostream &os, Controller &a) {
    os << "\n";
    a.print(os);
    os << "\n";

    return os;
}

std::ostream &operator<<(std::ostream &os, Controller *a) {
    os << *a;
    return os;
}