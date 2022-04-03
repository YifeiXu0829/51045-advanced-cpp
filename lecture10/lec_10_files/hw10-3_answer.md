As SharedState is a structure of multiple objects, using atomic<SharedState> may not work due to SharedState, as this reference https://en.cppreference.com/w/cpp/atomic/atomic pointed out, 
```
The primary std::atomic template may be instantiated with any TriviallyCopyable type T satisfying both CopyConstructible and CopyAssignable. The program is ill-formed if any of following values is false:

std::is_trivially_copyable<T>::value
std::is_copy_constructible<T>::value
std::is_move_constructible<T>::value
std::is_copy_assignable<T>::value
std::is_move_assignable<T>::value
```
which may break atomicity.
Thus It will be a bad idea to apply atomic on SharedState since it doesn't guarantee atomicity on ShareState, which would fall back to using locks, I would not going for it.
