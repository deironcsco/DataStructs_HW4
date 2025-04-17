#pragma once

template <typename T> class BST {
public:
  BST<T> *left = nullptr;
  BST<T> *right = nullptr;
  T *data;
  BST(T *);
  BST();
  ~BST();
  int Insert(T *);
  BST<T> *Find(T *);
  BST<T> *FindChecked(T *, int *);
  int Size();
  T **GetAllAscending();
  T **GetAllDescending();
  void EmptyTree();
  BST<T> *Remove(T *);
  BST<T> *RemoveChecked(T *, int *);
  int Height();
  int BalanceFactor();
  void LeftRotation();
  void RightRotation();
  void Print();
  void Balance();
};
