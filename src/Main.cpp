#include "Utilities.hpp"
int main() {
  Utility util = Utility();
  cout << " from Main Reference:" << &util.getMapCArithmetic() << endl;
  for (auto &[k, value] : util.getMapCArithmetic()) {
    cout << "Key: " << k << "Value: " << value << endl;
  }
}
