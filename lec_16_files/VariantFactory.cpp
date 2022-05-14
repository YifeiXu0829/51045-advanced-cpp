#include<string>
#include<iostream>
#include<variant>
#include<memory>
#include<utility>
#include"variadic_examples.h"

using namespace std;
using namespace mpcs;

/********************************************
*
*  Train types
*
*********************************************/

struct model_locomotive {
    void blow_horn()  {
        cout << "honk" << endl;
    }
};

struct model_freight_car {
    void load_coal() {
        cout << "Filling with coal dust. Pretending it's coal" << endl;
    }
};

struct model_caboose {
    virtual void wave() {
        cout << "Model conductor has hand in waving position" << endl;
    }
};

struct real_locomotive {
    void blow_horn() {
        cout << "HOOOOONNNNNNKKKKK" << endl;
    }
};

struct real_freight_car {
    void load_coal() {
        cout << "Powering our nation (and heating our planet)" << endl;
    }
};

struct real_caboose {
    virtual void wave() {
        cout << "Bye, kids" << endl;
    }
};

using locomotive = variant<model_locomotive, real_locomotive>;
using freight_car = variant<model_freight_car, real_freight_car>;
using caboose = variant<model_caboose, real_caboose>;

// Before implementing factories, test that our
// railroad car variants work
void without_factories() {
    locomotive l = model_locomotive();
    visit([](auto l) {l.blow_horn(); }, l);
}

/******************************************************
*
* Solution 1: 
*      Essentially the same code as our existing factory
*      but return values instead of unique_ptrs
* 
*/
template<typename T>
struct TT {
};

template<typename T>
struct abstract_creator {
    virtual T doCreate(TT<T>&&) = 0;
};

template<typename... Ts>
struct abstract_factory : public abstract_creator<Ts>... {

    template<class U> U create() {
        abstract_creator<U>& creator = *this;
        return creator.doCreate(TT<U>());
    }
    virtual ~abstract_factory() = default;
};

template<typename AbstractFactory, typename Abstract, typename Concrete>
struct concrete_creator : virtual public AbstractFactory {
    Abstract doCreate(TT<Abstract>&&) override {
        return Concrete();
    }
};

template<typename AbstractFactory, typename... ConcreteTypes>
struct concrete_factory;

template<typename... AbstractTypes, typename... ConcreteTypes>
struct concrete_factory
    <abstract_factory<AbstractTypes...>, ConcreteTypes...>
    : public concrete_creator<abstract_factory<AbstractTypes...>,
    AbstractTypes, ConcreteTypes>... {
};

// We can also make the methods on the car easier to call
void blow_horn(locomotive l) {
    visit([](auto l) {l.blow_horn(); }, l);
}

// Demonstrate solution 1
void use_solution_1() {
    using abstract_train_factory
        = abstract_factory<locomotive, freight_car, caboose>;
    using model_train_factory = 
        concrete_factory<abstract_train_factory, 
                         model_locomotive, model_freight_car, model_caboose>;
    unique_ptr<abstract_train_factory> factory = make_unique<model_train_factory>();
    locomotive l = factory->create<locomotive>();
    blow_horn(l);
}

/******************************************************
*
* Solution 2:
*      Why not use variants throughout by making the
*      abstract factory a variant of all the concrete factories as well?
*
*/

template<typename AbstractTypeList, typename ...ConcreteTypes>
struct concrete_factory_v;

template<typename... AbstractTypes, typename... ConcreteTypes>
struct concrete_factory_v
    <tuple<AbstractTypes...>, ConcreteTypes...> {
    
    template<typename Abstract>
    Abstract create() {
        // Unfortunately, you can't index parameter packs (yet), so we'll
        // use tuples and our variadic_examples to find the type at an index
        // std::tuple_element would be a more "official" version of TypeAt
        return TypeAt_t<tuple<ConcreteTypes...>, IndexOf_v<tuple<AbstractTypes...>, Abstract>>();
    }
};

// Since we are taking the "variant" approach, we need to specify the concrete families
// in our abstract factory

template<typename ...ConcreteFactories>
using abstract_factory_v = variant<ConcreteFactories...>;


template<typename Abstract, typename Factory>
Abstract create(Factory& factory)
{
    return visit([](auto& a) { return a.create<Abstract>(); }, factory);
}

// Demonstrate solution 2
void use_solution_2() {
    using abstract_train_cars = tuple< locomotive, freight_car, caboose>;
    using model_train_factory = concrete_factory_v<abstract_train_cars, model_locomotive, model_freight_car, model_caboose>;
    using real_train_factory = concrete_factory_v<abstract_train_cars, real_locomotive, real_freight_car, real_caboose>;
    using abstract_train_factory = abstract_factory_v<model_train_factory, real_train_factory>;

    abstract_train_factory factory = real_train_factory();
    locomotive l = create<locomotive>(factory);
    blow_horn(l);
}

int main()
{
    without_factories();
    use_solution_1();
    use_solution_2();
}