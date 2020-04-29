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
    Mammals(unsigned int n = 5) : number_of_spieces(n){};

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
    Giraffe(string _name, unsigned int _high, unsigned int _n) : Mammals(getNumberOfSpieces()) {
        name = _name;
        color = yellow;
        place = africa;
        high = _high;
        number_of_patches = _n;
    };

    unsigned int getNumberOfPutches() const{//расширение поведения
        return number_of_patches;
    }
    void setNumberOfPutches(unsigned int n){// за счёт get/set
        number_of_patches = n;
    }

    string getName() const{
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
public:
    LittleGiraffe(Giraffe &_parent, string _name, unsigned int _high) : Giraffe(parent->getName(), parent->getHigh(),
                                                                                             parent->getNumberOfPutches()) {
        name = _name;
        high = _high;
        parent = &_parent;
        color = yellow;
        place = africa;
    };
    string getParentName(){
        return parent->getName();
    }
    unsigned int getNumberOfPutchesOfParent(){
        return parent->getNumberOfPutches();
    }
};

class Whale: protected Mammals{
public:
    string name;
    Whale(string n, unsigned int _high): Mammals(getNumberOfSpieces()){
        color = gray;
        place = ocean;
        high = _high;
        name = n;
    }

    color_t getColor() const{//замена поведения
        return gray ;
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

int main() {

    Whale Don("Don", 410);
    Giraffe Gora("Gora", 220, 41);
//    Mammals Mam(140);
//    try{
//        Mam.setNumberOfSpieces(29000);
//    }
//    catch(exception &e){
//        cout << e.what() << endl;
//    }

    cout << Don.getColor() << endl;

    cout << Gora.getNumberOfPutches() << endl;
    LittleGiraffe Lil(Gora, "Lil", 150);
    cout << Lil.getNumberOfPutchesOfParent()<< endl;
    return 0;
}
