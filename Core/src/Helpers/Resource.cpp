#include "Helpers\Resource.h"

template<typename T>
Resource<T>::Resource() {

}
template<typename T>
Resource<T>::~Resource() {}

template<typename T>
T Resource<T>::operator*() { return resource; }