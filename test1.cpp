/*
 * =====================================================================================
 *
 *       Filename:  test1.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  05/02/2012 09:05:56 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Darius-Kylin (DK), dongyuchi@gmail.com
 *        Company:  UESTC
 *
 * =====================================================================================
 */
#define PAGODA_NEED_ACCESS_PRIVATE_MEMBER
#include"pagodaTest.h"
PAGODA_DACLARE_TEST_CLASS_BEGIN(Calculator)
PAGODA_DACLARE_TEST_CASE(Add)
PAGODA_DACLARE_TEST_CASE(Sub)
PAGODA_DACLARE_TEST_CLASS_END()

PAGODA_DEFINE_TEST_OBJECT(Calculator, tester)

class Calculator {
  public:
    int Add(int a, int b) {
      return a + b;
    }
  private:
    int Sub(int a, int b) {
      return a - b;
    }
    PAGODA_DECLARE_FRIEND(Calculator);
};
PAGODA_DEFINE_TEST_CASE(Calculator, tester, Add) {
  Calculator cal;
  PAGODA_EXPECT_TRUE(cal.Add(3, -4) == -1);
}
PAGODA_DEFINE_TEST_CASE(Calculator, tester, Sub) {
  Calculator cal;
  PAGODA_EXPECT_TRUE(cal.Sub(10, 20) == 10);
}
int main() {

  PAGODA_RUN_ALL_TESTCASES(tester);
  return 0;
}
