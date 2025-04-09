Program specifications: A program to manage lending out board games. Prints out a list of every game, shows how many of each are available. If someone is using one of the games, show who is using the game, when they took it, and when they need to bring it back.

key nouns and verbs: list, number of copies of each game, number of people using each game, name of game, name of person, rent date, due date

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
public: 
    Renter(std::string name, std::string rentDate, std::string dueDate);
    void printInfo();
}

code outline:

```mermaid
classDiagram
    class Game Tracker {
        +vector games ~Game~

        +listGames()
    }

    class Game {
        +string name
        +int numCopies
        +vector renters ~Renter~

        +printRenters()
        +addRenter(renter : Renter)
        +removeRenter(renter : Renter)
    }

    class Renter{
        +string name
        +string rentDate
        +string dueDate

        +printInfo()
    }