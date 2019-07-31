# Advanced features

## Read-only property

### Using a typename tag

```cpp
struct readwrite_t {};
struct readonly_t {};

template<class T, class = readwrite_t>
class property; // Read-write

template<class T>
class property<T, readonly_t>; // Read-only
```

### Using C++17 template argument deduction & deduction guide

```cpp
template<class T, typename Get, typename Set = void>
class property; // Read-write

template<class T, typename Get>
class property<T, Get, void>; // Read-only

template<class T, typename Get>
property(Get x)->property<T, Get, void>; // Deduction guide for read-only
```
## Auto-implemented property

### Using a backing field inside the property class

```cpp
template<class T>
class property
{
    ...
private:
    T backing_field_;
};

```

## Expression-bodied property

### ???
