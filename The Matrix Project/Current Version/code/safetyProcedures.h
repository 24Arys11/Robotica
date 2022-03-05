#ifndef SAFETYPROCEDURES_H_INCLUDED
#define SAFETYPROCEDURES_H_INCLUDED


template <class T>
bool isEqual(T a, T b){
  return a == b;
}

template <class T>
bool isNotEqual(T a, T b){
  return a != b;
}

template <class T>
bool isNull(T a){
  return a == NULL;
}

template <class T>
bool isNotNull(T a){
  return a != NULL;
}

template <class T>
bool isLesser(T a, T b){
  return a < b;
}

template <class T>
bool isGreater(T a, T b){
  return a > b;
}

template <class T>
bool isLesserOrEqual(T a, T b){
  return a <= b;
}

template <class T>
bool isGreaterOrEqual(T a, T b){
  return a >= b;
}

template <class T>
void Set(T &a, T b){
  a = b;
}


#endif /// SAFETYPROCEDURES_H_INCLUDED
