#include "bst.h"
#include <algorithm>
#include <iostream>

template <typename T> BST<T>::BST() {}
template <typename T> BST<T>::BST(T *item) { data = item; }

template <typename T> BST<T>::~BST() {
  EmptyTree();
  delete data;
}

template <typename T> int BST<T>::Insert(T *value) {
  int checks = 0;
  if (data == nullptr) {
    data = value;
    return checks;
  }
  checks++;
  if (*value < *data) {
    if (left == nullptr)
      left = new BST(value);
    else
      checks += left->Insert(value);
  } else if (*value > *data) {
    if (right == nullptr)
      right = new BST(value);
    else
      checks += right->Insert(value);
  }
  Balance();
  return checks;
}

template <typename T> BST<T> *BST<T>::Find(T *input) {
  BST<T> *value = nullptr;
  if (*data == *input) {
    value = data;
  } else if (left != nullptr && *input < *data) {
    value = left->Find(input);
  } else if (right != nullptr && *input > *data) {
    value = right->Find(input);
  }
  return value;
}

template <typename T> BST<T> *BST<T>::FindChecked(T *input, int *checks) {
  BST<T> *value = nullptr;
  if (*data == *input) {
    value = this;
  } else if (left != nullptr && *input < *data) {
    (*checks)++;
    value = left->FindChecked(input, checks);
  } else if (right != nullptr && *input > *data) {
    (*checks)++;
    value = right->FindChecked(input, checks);
  }
  return value;
}

template <typename T> int BST<T>::Size() {
  int size = 1;
  if (left != nullptr) {
    size += left->Size();
  }
  if (right != nullptr) {
    size += right->Size();
  }
  return size;
}

template <typename T> T **BST<T>::GetAllAscending() {
  int size = Size();
  int index = 0;
  T *arr[size] = new T *[size];
  T *sub[] = nullptr;
  if (left != nullptr) {
    size = left->Size();
    sub = left->GetAllAscending();
    for (int i{0}; i < size; i++) {
      sub = arr[index++] = sub[i];
    }
    delete sub;
  }
  arr[index++] = data;
  if (right != nullptr) {
    size = right->Size();
    sub = right->GetAllAscending();
    for (int i{0}; i < size; i++) {
      sub = arr[index++] = sub[i];
    }
    delete sub;
  }
  return arr;
}

template <typename T> T **BST<T>::GetAllDescending() {
  int size = Size();
  int index = 0;
  T *arr[size] = new T *[size];
  T *sub[] = nullptr;
  if (right != nullptr) {
    size = right->Size();
    sub = right->GetAllDescending();
    for (int i{0}; i < size; i++) {
      sub = arr[index++] = sub[i];
    }
    delete sub;
  }
  arr[index++] = data;
  if (left != nullptr) {
    size = left->Size();
    sub = left->GetAllDescending();
    for (int i{0}; i < size; i++) {
      sub = arr[index++] = sub[i];
    }
    delete sub;
  }
  return arr;
}

template <typename T> void BST<T>::EmptyTree() {
  if (left != nullptr) {
    left->EmptyTree();
    delete left;
  }
  if (right != nullptr) {
    right->EmptyTree();
    delete right;
  }
  left = right = nullptr;
}

template <typename T> BST<T> *BST<T>::Remove(T *value) {
  BST<T> *removed = nullptr;
  BST<T> *parent = nullptr;
  if (*value == *data) {
    removed = this;
  } else if (*value < *data && left != nullptr) {
    if (*left->data == *value) {
      removed = left;
      if (left->left == nullptr && left->right == nullptr) {
        left = nullptr;
      } else if (left->left == nullptr) {
        left = left->right;
      } else if (left->right == nullptr) {
        left = left->left;
      } else {
        BST<T> *min = left->right;
        parent = left;
        while (min->left != nullptr) {
          parent = min;
          min = min->left;
        }
        if (min->right != nullptr) {
        }
        T *temp = left->data;
        left->data = min->data;
        min->data = temp;
        removed = min;
      }
    } else {
      removed = left->Remove(value);
    }
  } else if (*value > *data && right != nullptr) {
    if (*right->data == *value) {
      removed = right;
      if (right->left == nullptr && right->right == nullptr) {
        right = nullptr;
      } else if (right->left == nullptr) {
        right = right->right;
      } else if (right->right == nullptr) {
        right = right->left;
      } else {
        BST<T> *min = right->right;
        parent = right;
        while (min->left != nullptr) {
          parent = min;
          min = min->left;
        }
        if (min->right != nullptr) {
        }
        T *temp = right->data;
        right->data = min->data;
        min->data = temp;
        removed = min;
      }
    } else {
      removed = right->Remove(value);
    }
  }
  if (parent != nullptr) {
    if (parent->left == removed)
      parent->left = nullptr;
    if (parent->right == removed) {
      parent->right = removed->right;
      removed->right = nullptr;
    }
  }
  left->Balance();
  right->Balance();
  return removed;
}

template <typename T> BST<T> *BST<T>::RemoveChecked(T *value, int *checks) {
  BST<T> *removed = nullptr;
  BST<T> *parent = nullptr;
  if (*value == *data) {
    removed = this;
  } else if (*value < *data && left != nullptr) {
    (*checks)++;
    if (*left->data == *value) {
      removed = left;
      if (left->left == nullptr && left->right == nullptr) {
        left = nullptr;
      } else if (left->left == nullptr) {
        left = left->right;
      } else if (left->right == nullptr) {
        left = left->left;
      } else {
        BST<T> *min = left->right;
        parent = left;
        while (min->left != nullptr) {
          parent = min;
          min = min->left;
        }
        if (min->right != nullptr) {
        }
        T *temp = left->data;
        left->data = min->data;
        min->data = temp;
        removed = min;
      }
    } else {
      removed = left->RemoveChecked(value, checks);
    }
  } else if (*value > *data && right != nullptr) {
    (*checks)++;
    if (*right->data == *value) {
      removed = right;
      if (right->left == nullptr && right->right == nullptr) {
        right = nullptr;
      } else if (right->left == nullptr) {
        right = right->right;
      } else if (right->right == nullptr) {
        right = right->left;
      } else {
        BST<T> *min = right->right;
        parent = right;
        while (min->left != nullptr) {
          parent = min;
          min = min->left;
        }
        if (min->right != nullptr) {
        }
        T *temp = right->data;
        right->data = min->data;
        min->data = temp;
        removed = min;
      }
    } else {
      removed = right->RemoveChecked(value, checks);
    }
  }
  if (parent != nullptr) {
    if (parent->left == removed)
      parent->left = nullptr;
    if (parent->right == removed) {
      parent->right = removed->right;
      removed->right = nullptr;
    }
  }
  // left->Balance();
  // right->Balance();
  Balance();
  return removed;
}

template <typename T> int BST<T>::Height() {
  int lheight = -1;
  int rheight = -1;
  if (left != nullptr) {
    lheight = left->Height();
  }
  if (right != nullptr) {
    rheight = right->Height();
  }
  return 1 + std::max(lheight, rheight);
}

template <typename T> int BST<T>::BalanceFactor() {
  int lheight = -1;
  int rheight = -1;
  if (left != nullptr) {
    lheight = left->Height();
  }
  if (right != nullptr) {
    rheight = right->Height();
  }
  return lheight - rheight;
}

template <typename T> void BST<T>::LeftRotation() {
  BST<T> *temp = new BST(data);
  temp->left = left;
  temp->right = right->left;
  left = temp;
  temp = right;
  data = right->data;
  right = right->right;
}

template <typename T> void BST<T>::RightRotation() {
  BST<T> *temp = new BST(data);
  temp->right = right;
  temp->left = left->right;
  right = temp;
  temp = left;
  data = left->data;
  left = left->left;
}

template <typename T> void BST<T>::Print() {
  if (data == nullptr) {
    std::cout << "oh no";
    return;
  }
  std::cout << "(data: " << *data << std::endl;
  std::cout << "left: ";
  if (left != nullptr) {
    left->Print();
    std::cout << std::endl;
  } else {
    std::cout << "none" << std::endl;
  }
  std::cout << "right: ";
  if (right != nullptr) {
    right->Print();
    std::cout << std::endl;
  } else {
    std::cout << "none" << std::endl;
  }
  std::cout << ")";
}

template <typename T> void BST<T>::Balance() {
  int bf = BalanceFactor();
  if (bf > 1) {
    int leftbf = left->BalanceFactor();
    if (leftbf >= 0) {
      RightRotation();
    } else if (leftbf < 0) {
      left->LeftRotation();
      RightRotation();
    }
  } else if (bf < -1) {
    int rightbf = right->BalanceFactor();
    if (rightbf <= 0) {
      LeftRotation();
    } else if (rightbf > 0) {
      right->RightRotation();
      LeftRotation();
    }
  }
}
