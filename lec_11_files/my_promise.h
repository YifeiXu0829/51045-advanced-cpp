// Note: The condition_variable version is a good choice for problem 10-3
// But if you choose to do an atomic version, here is how (h/t Harry Gray)

#ifndef MY_PROMISE_H
#  define MY_PROMISE_H
#include<memory>
#include<thread>
#include<exception>
#include<stdexcept>
#include<atomic>
using std::shared_ptr;
using std::unique_ptr;
using std::make_shared;
using std::make_unique;
using std::move;
using std::lock_guard;
using std::unique_lock;
using std::exception_ptr;
using std::rethrow_exception;
using std::runtime_error;

namespace mpcs {
template<class T> class MyPromise;

enum class State { empty, val, exc };

template<class T>
struct SharedState {
  std::atomic<State> state{State::empty};
  unique_ptr<T> value;
  exception_ptr exception;
};

template<typename T>
class MyFuture {
public:
  MyFuture(MyFuture const &) = delete; // Injected class name
  MyFuture(MyFuture &&other) : sharedState{move(other.sharedState)} {}
  T get() {
    sharedState->state.wait(State::empty);
    switch (sharedState->state) {
    case State::val:
      return move(*sharedState->value);
    case State::exc:
      rethrow_exception(sharedState->exception);
    default:
      throw runtime_error{"Invalid state for future"};
    }
  }
private:
  friend class MyPromise<T>;
  MyFuture(shared_ptr<SharedState<T>> &sharedState) 
	  : sharedState(sharedState) {}
  shared_ptr<SharedState<T>> sharedState;
};

template<typename T>
class MyPromise
{
public:
  MyPromise() : sharedState{make_shared<SharedState<T>>()} {}

  void set_value(const T &value) {
    sharedState->value = make_unique<T>(value);
    sharedState->state = State::val;
    // As discussed in class, this works because memory model defaults
    // to sequential consistency. We will learn more formally about this later
    sharedState->state.notify_one();
  }

  void set_exception(exception_ptr exc) {
    sharedState->exception = exc;
    sharedState->state = State::exc;
    sharedState->state.notify_one();
  }

  MyFuture<T> get_future() {
    return sharedState;
  }
private:
  shared_ptr<SharedState<T>> sharedState; 
};
}
#endif
