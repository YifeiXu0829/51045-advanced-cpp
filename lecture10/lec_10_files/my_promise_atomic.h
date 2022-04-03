#ifndef MY_PROMISE_H
#  define MY_PROMISE_H
#include<memory>
#include <atomic>
#include<thread>
#include<mutex>
#include<condition_variable>
#include<exception>
#include<stdexcept>
#include<iostream>
using std::shared_ptr;
using std::unique_ptr;
using std::make_shared;
using std::make_unique;
using std::move;
using std::mutex;
using std::condition_variable;
using std::lock_guard;
using std::unique_lock;
using std::exception_ptr;
using std::rethrow_exception;
using std::runtime_error;
using std::atomic;

namespace mpcs {
template<class T> class MyPromise;

enum class State : uint8_t
{ empty, val, exc };

template<class T>
struct SharedState {
  atomic<State> state{State::empty};
  unique_ptr<T> value{};
  exception_ptr exception{};
};

template<typename T>
class MyFuture {
public:
  MyFuture(MyFuture const &) = delete; // Injected class name
  MyFuture(MyFuture &&other) : sharedState{move(other.sharedState)} {}
  T get() {
    std::cout<<"is_lock_free ? "<<sharedState->state.is_lock_free()<<std::endl;
    sharedState->state.wait(State::empty); // wait until no longer empty
    switch (sharedState->state.load()) {
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
    sharedState->state.store(State::val);
    sharedState->state.notify_all();
  }

  void set_exception(exception_ptr exc) {
    sharedState->exception = exc;
    sharedState->state.store(State::exc);
    sharedState->state.notify_all();
  }

  MyFuture<T> get_future() {
    return sharedState;
  }
private:
  shared_ptr<SharedState<T>> sharedState; 
};
}
#endif
