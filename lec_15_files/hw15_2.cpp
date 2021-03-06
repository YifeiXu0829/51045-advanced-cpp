#include "hw15_2.h"
#include <variant>

template <typename Locomotive, typename FreightCar, typename Caboose>
struct train_factory
{
    Locomotive locomotive;
    FreightCar freight_car;
    Caboose caboose;
};
using namespace cspp51045;
using model_train_factory = train_factory<model_locomotive, model_freight_car, model_caboose>;
using real_train_factory = train_factory<real_locomotive, real_freight_car, real_caboose>;
int main()
{
    using std::cout;
    using std::endl;
    std::variant<model_train_factory, real_train_factory> v;

    while(true){

        int option=0;
        cout << "Choose Part: (1) real train (2) model train (else) Exit program"<<endl;
        std::cin >> option;

        if (option==2)
        {
            v = model_train_factory{};
        }
        else if (option == 1)
        {
            v = real_train_factory{};
        }
        else {
            return 0;
        }

        std::visit([](auto &x) { x.locomotive.blow_horn(); }, v);
        std::visit([](auto &x) { x.freight_car.load_coal(); }, v);
        std::visit([](auto &x) { x.caboose.wave(); }, v);
    }
}
