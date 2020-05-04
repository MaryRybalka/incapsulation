/*1. Продемонстрировать различные уровни инкапсуляции данных (указать комментарием):
a. Отсутствие инкапсуляции (public свойства)
b. Инкапсуляция с помощью set/get
c. Инкапсуляция с помощью специализированных протоколов/методов
d. Инкапсуляция за счёт абстракций

p.s. использовать механизмы исключений, если нарушается инвариант или не соблюдаются пост/пред-условия

2. Продемонстрировать различные варианты инкапсуляции поведения
a. За счёт позднего связывания
b. Замена поведения (тут тоже используется позднее связывание)
c. Расширения поведения (тут тоже используется позднее связывание)*/

#include <iostream>
#include <exception>
using namespace std;

const int N = 5;

enum color_t{black, white, gray, yellow};
enum place_t{africa, canada, china, ocean, everywhere};

class Mammals{
private:
    unsigned int number_of_spieces;
protected:
    color_t color;
    unsigned int high;
    place_t place;
public:
    Mammals() : number_of_spieces(N){};

    void setNumberOfSpieces(unsigned int n){
        ((n<=0)||(n>25000))? throw logic_error("destroy the invariant") : number_of_spieces = n;
    }
    unsigned int getNumberOfSpieces() const{
        return number_of_spieces ;
    }

    virtual color_t getColor() {return color;};
    virtual void setHigh( unsigned int h) {};//за счёт позднего связывания
    virtual unsigned int getHigh() {return 0;};
    virtual void setPlace(place_t p) {};
    virtual place_t getPlace() {return place;};
    virtual void sound(){};
};

class Giraffe: public Mammals{
private:
    unsigned int number_of_patches;
    string name;
public: //отсутствие инкапсуляции
    Giraffe(string _name, unsigned int _high, unsigned int _n) {
        name = _name;
        color = yellow;
        place = africa;
        high = _high;
        number_of_patches = _n;
    };

    virtual unsigned int getNumberOfPutches() const{
        return number_of_patches;
    }
    virtual void setNumberOfPutches(unsigned int n){// за счёт get/set
        number_of_patches = n;
    }

    virtual string getName() const{
        return name;
    }
    void setName(string &n){
           name = n;
    }

    color_t getColor() const{
        return yellow ;
    }

    void setHigh( unsigned int h){
        high = h;
    }
    unsigned int getHigh() const{
        return high ;
    }

    void setPlace(place_t p){
        place = p ;
    }
    place_t getPlace() const{
        return place ;
    }
};

class LittleGiraffe: public Giraffe{//инкапсуляция за счёт абстракций
private:
    Giraffe *parent;
    string name;
    unsigned int number_of_patches;
public:
    LittleGiraffe(Giraffe &_parent, string _name, unsigned int _high) : Giraffe(_name, _high, _parent.getNumberOfPutches()) {
        name = _name;
        high = _high;
        parent = &_parent;
        color = yellow;
        place = africa;
    };
    string getParentName() const{
        return parent->getName();
    }
    unsigned int getNumberOfPutchesOfParent(){
        return parent->getNumberOfPutches();
    }

    string getName() const override{ //расширение поведения
        return  getParentName() + "'s child little " + name;
    }

    void setNumberOfPutches(unsigned int n){
        number_of_patches = n % 100;
    }
    unsigned int getNumberOfPutches() const{
        return number_of_patches;
    }
};

class Fish {
private:
    unsigned int numberOfFishes;
public:
    void setNumberOfFishes(unsigned int n) {
        numberOfFishes = n;
    }

    unsigned int getNumberOfFishes() const {
        return numberOfFishes;
    }

    virtual bool fastSwim() = 0;
};

class Tuna: public Fish{
private:
    bool yummy;
public:
    Tuna(){
        setNumberOfFishes(getNumberOfFishes()+1);
    }
    bool fastSwim(){
        return true;
    }
};

class Forel: public Fish{
private:
    bool yummy;
public:
    Forel(){
        setNumberOfFishes(getNumberOfFishes()+2);
    }
    bool fastSwim(){
        return false;
    }
};

class Whale: protected Mammals{
private:
    int satiety = 0;
    bool alive = true;
public:
    string name;
    Whale(string n, unsigned int _high){
        color = gray;
        place = ocean;
        high = _high;
        name = n;
    }

    color_t getColor() const{//замена поведения
            return gray;
    }
    void setHigh( unsigned int h){
        if (alive) {
            high = h;
        }
    }
    unsigned int getHigh() const{
        if (alive) {
            return high;
        }
    }
    void setPlace(place_t p){
        if (alive) {
            place = p;
        }
    }
    place_t getPlace() const{
        if (alive) {
            return place;
        }
    }

    void decPopulationOfFish(Fish &fish, unsigned  int n){
        fish.setNumberOfFishes(fish.getNumberOfFishes()-n);
    }

    bool haveLunch(Fish &fish){
        if (!alive) return false;
        if (fish.fastSwim()) {
                cout << "Whale missed the fish" << endl;
                satiety--;
            if (satiety < -7){
                alive = false;
                cout << "Whale died!"<< endl;
                return false;
            }
            if (satiety < -5) cout << "Get hurry Whale going to die!" << endl;
            return false;
        }
        decPopulationOfFish(fish,1);
        cout << "Whale ate the fish" << endl;
        satiety++;
        return true;
    }
};

int main() {
    Giraffe Gora("Gora", 220, 41);
    cout << "Number of " << Gora.getName() << "'s patches: " << Gora.getNumberOfPutches() << endl;
    cout << Gora.getName() << "'s high: " << Gora.getHigh() << endl;
    Gora.setHigh(310);
    cout << Gora.getName() << "'s new high: " << Gora.getHigh() << endl;

    Tuna tuna;
    Forel forel;

    Whale Don("Don", 410);
    cout << Don.name << "'s color: " << Don.getColor() << endl;//2b
    cout << Gora.getName() << "'s color: " << Gora.getColor() << endl;
    Don.haveLunch(tuna);
    Don.haveLunch(tuna);
    Don.haveLunch(tuna);
    Don.haveLunch(tuna);
    Don.haveLunch(tuna);
    Don.haveLunch(tuna);
    Don.haveLunch(tuna);
    Don.haveLunch(tuna);
    Don.haveLunch(tuna);
    Don.haveLunch(forel);//1c

    LittleGiraffe Ponyo(Gora, "Ponyo", 150);
    cout << Ponyo.getName()<<endl;//2c
    cout << "Number of Parent Patches: " << Ponyo.getNumberOfPutchesOfParent()<< endl;//1d
    Ponyo.setNumberOfPutches(20);//2a
    cout << "Number of " << Ponyo.getName() << "'s patches: " << Ponyo.getNumberOfPutches() << endl;
    cout << Ponyo.getName() <<" has parent "<< Ponyo.getParentName() << endl;
    return 0;
}