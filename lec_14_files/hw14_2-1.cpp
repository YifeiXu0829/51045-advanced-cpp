#include "flex_factory.h"
#include <iostream>

using namespace std;
using namespace cspp51045;

struct locomotive_base
{
    // implicitly delete default constructor
    explicit locomotive_base(double horsepower){}
    virtual void print() = 0;
    virtual ~locomotive_base(){}
};

struct freightcar_base
{
    virtual void print() = 0;
    virtual ~freightcar_base(){}
};

struct caboose_base
{
    virtual void print() = 0;
    virtual ~caboose_base(){}
};

using BaseTrain = abstract_factory<locomotive_base, freightcar_base, caboose_base>;

struct locomotive_model : public locomotive_base
{
    locomotive_model(double h):locomotive_base(h){}
    virtual void print() override{cout<<"locomotive_model\n";}
    virtual ~locomotive_model(){}
};

struct freightcar_model : public freightcar_base
{
    virtual void print() override{cout<<"freightcar_model\n";}
    virtual ~freightcar_model(){}
};

struct caboose_model : public caboose_base
{
    virtual void print() override{cout<<"caboose_model\n";}
    virtual ~caboose_model(){}
};

using model_train_factory = concrete_factory<BaseTrain, locomotive_model, freightcar_model, caboose_model>;

struct locomotive_real : public locomotive_base
{
    locomotive_real(double h):locomotive_base(h){}
    virtual void print() override{cout<<"locomotive_real\n";}
    virtual ~locomotive_real(){}
};

struct freightcar_real : public freightcar_base
{
    virtual void print() override{cout<<"freightcar_real\n";}
    virtual ~freightcar_real(){}
};

struct caboose_real : public caboose_base
{
    virtual void print() override{cout<<"caboose_real\n";}
    virtual ~caboose_real(){}
};

using real_train_factory = concrete_factory<BaseTrain, locomotive_real, freightcar_real, caboose_real>;

int main()
{

    string real_or_model{};
    cin >> real_or_model;
    unique_ptr<BaseTrain> train{};
    if (real_or_model == "real")
    {
        cout << "building real train ...\n";
        train = make_unique<real_train_factory>();
    }
    else if (real_or_model == "model")
    {
        cout << "building model train ...\n";
        train = make_unique<model_train_factory>();
    }
    else
    {
        cout << "invalid input\n";
    }

    if (train != nullptr)
    {
        double hp = 666;
        auto locomotive = train->create<locomotive_base>(hp);
        locomotive->print();
        //auto freightcar = train->create<freightcar_base>();
        //freightcar->print();
        //auto caboose = train->create<caboose_base>();
        //caboose->print();
    }

}
