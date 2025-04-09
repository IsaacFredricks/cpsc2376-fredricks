Program specifications: A program to manage lending out board games. Prints out a list of every game, shows how many of each are available. If someone is using one of the games, show who is using the game, when they took it, and when they need to bring it back.

nouns: list of games, list of renters, number of games, number of copies, name of game, name of renter, due date, rent date, number of games returned

verbs: game tracker, list games, list renters, print renter info, add renter, remove renter

//GameTracker.h
class GameTracker{
private:
    std::vector<Game> games; 
public:
    void listGames();
};

//Game.h
class Game{
private:
    std::string name;
    int numCopies;
    std::vector<Renter> renters;
public:
    Game(std::string& name, int numCopies, std::vector<Renter>& renters);
    void printRenters();
    void addRenter(const Renter& renter);
    void removeRenter(const Renter& renter);
};

//Renter.h
class Renter{
private:
    std::string name;
    std::string rentDate;
    std::string dueDate;
    std::string whenReturned;
public: 
    Renter(std::string& name, std::string& rentDate, std::string& dueDate, std::string& whenReturned);
    void printInfo();
};

code outline:

```mermaid
classDiagram
    class GameTracker {
        -games : vector~Game~

        +listGames()
    }

    class Game {
        +string name
        +int numCopies
        -renters : vector~Renter~

        +Game(string name, int numCopies, renters : vector~Renter~)
        +printRenters()
        +addRenter(renter : Renter)
        +removeRenter(renter : Renter)
    }

    class Renter{
        +string name
        +string rentDate
        +string dueDate
        +string whenReturned


        +Renter(string name, string rentDate, string dueDate, string whenReturned)
        +printInfo()
    }

GameTracker --> Game : uses
Game --> Renter : uses
