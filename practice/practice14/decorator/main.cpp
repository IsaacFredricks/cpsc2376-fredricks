#include <iostream>
#include <memory>
#include <limits>
/*Create a base Purchase interface with a method getCost().
Implement a SimplePurchase with a base cost.
Create decorators for:
TaxDecorator – adds 10% tax
ShippingFeeDecorator – adds a flat shipping fee
DiscountDecorator – reduces cost by a percentage
Let the user choose which decorators to apply and print the final cost.*/

//interface class
class Purchase{
public:
    virtual float getCost() const = 0;
    virtual ~Purchase() = default;
};

//concrete class
class SimplePurchase : public Purchase{
    float baseCost;

public:
    SimplePurchase(float baseCost) : baseCost(baseCost) {}
    float getCost() const override{return baseCost;}
};

//decorators
class TaxDecorator : public SimplePurchase{
    std::shared_ptr<Purchase> base;
public://based off of tutorial 14
    TaxDecorator(std::shared_ptr<Purchase> b) : SimplePurchase(b->getCost()), base(std::move(b)) {}

    float getCost() const override{return (base->getCost() + (base->getCost() * 0.1));}
};

class ShippingFeeDecorator : public SimplePurchase{
    std::shared_ptr<Purchase> base;
public://based off of tutorial 14
    ShippingFeeDecorator(std::shared_ptr<Purchase> b) : SimplePurchase(b->getCost()), base(std::move(b)) {}

    float getCost() const override{return (base->getCost() + 10);}
};

class DiscountDecorator : public SimplePurchase{
    std::shared_ptr<Purchase> base;
public://based off of tutorial 14
    DiscountDecorator(std::shared_ptr<Purchase> b) : SimplePurchase(b->getCost()), base(std::move(b)) {}

    float getCost() const override{return (base->getCost() - (0.05 * base->getCost()));}
};

//forward declarations:
float getFloat(const std::string& prompt);
int getInt(const std::string& prompt);
char getChar(const std::string& prompt);

int main(){
    //test code: 
    /*float baseCost = 50;
    std::shared_ptr<Purchase> w;
    w = std::make_shared<TaxDecorator>(
    std::make_shared<SimplePurchase>(baseCost));
    std::cout << w->getCost() << '\n';
    w = std::make_shared<ShippingFeeDecorator>(
        std::make_shared<SimplePurchase>(baseCost));
    std::cout << w->getCost() << '\n';
    */
    
    std::cout << "Purchase Decorator pattern.\n";
    float cost{getFloat("Enter the base cost: $")};
    std::shared_ptr<Purchase> purchase = std::make_shared<SimplePurchase>(cost);
    
    char yOrN{getChar("Do you want to apply 10% tax? y or n: ")};
    if(yOrN == 'y' || yOrN == 'Y'){
        purchase = std::make_shared<TaxDecorator>(std::make_shared<SimplePurchase>(cost));
        cost = purchase->getCost();
    }
    
    yOrN = getChar("Do you want to apply a flat $10 shipping fee? y or n: ");
    if(yOrN == 'y' || yOrN == 'Y'){
        purchase = std::make_shared<ShippingFeeDecorator>(std::make_shared<SimplePurchase>(cost));
        cost = purchase->getCost();
    }

    yOrN = getChar("Do you want to apply a 5% discount? y or n: ");
    if(yOrN == 'y' || yOrN == 'Y'){
        purchase = std::make_shared<DiscountDecorator>(std::make_shared<SimplePurchase>(cost));
        cost = purchase->getCost();
    }

    std::cout << "The final cost is $" << cost << '\n'; 
    

    return 0;
}

//for menu
int getInt(const std::string& prompt) {

    int input{};
    
    while (true) {
        std::cout << prompt;
        std::cin >> input;

        if (std::cin.fail() || std::cin.peek() != '\n' || input < 1 || input > 6) {
            //peek looks at next character in queue
            std::cin.clear(); //clears the error

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            //discards invalid input

            std::cout << "Inproper input. please try again.\n";
        }

        else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            //discards any extra input
            break;//exits loop
        }
    }
    return input;
}

float getFloat(const std::string& prompt) {

    float input{};
    
    while (true) {
        std::cout << prompt;
        std::cin >> input;

        if (std::cin.fail() || std::cin.peek() != '\n' || input <= 0) {
            //peek looks at next character in queue
            std::cin.clear(); //clears the error

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            //discards invalid input

            std::cout << "Inproper input. please try again.\n";
        }

        else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            //discards any extra input
            break;//exits loop
        }
    }
    return input;
}

char getChar(const std::string& prompt) {

    char input{};
    
    while (true) {
        std::cout << prompt;
        std::cin >> input;

        if (std::cin.fail() || std::cin.peek() != '\n' || (input != 'y' && input != 'n' &&
        input != 'Y' && input != 'N')) {
            //peek looks at next character in queue
            std::cin.clear(); //clears the error

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            //discards invalid input

            std::cout << "Inproper input. please try again.\n";
        }

        else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            //discards any extra input
            break;//exits loop
        }
    }
    return input;
}