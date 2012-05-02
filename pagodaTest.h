/*
 * =====================================================================================
 *
 *       Filename:  pagodaTest.h
 *
 *    Description:  A lightweight c++ program's unit testing framework
 *
 *        Version:  1.0
 *        Created:  05/02/2012 06:45:51 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Darius-Kylin (DK), dongyuchi@gmail.com
 *        Company:  UESTC
 *
 * =====================================================================================
 */
#ifndef _PAGODATEST_HEAD_H
#define _PAGODATEST_HEAD_H

#include<stdexcept>
#include<vector>
#include<cstdio>
/*
 *@brief: expect a condition to be  true
 * */
#define PAGODA_EXPECT_TRUE(cond)                \
    if(!(cond))                                 \
    {                                           \
        throw std::runtime_error("[Check failed]"#cond);    \
    }                                           
/* 
 *@brief: expect a condition to be false
 * */
#define PAGODA_EXPECT_FALSE(cond)       PAGODA_EXPECT_TRUE(!(cond))
/* 
 *@brief:expect a arithmetic expression(val1 op val2) to be true
 * */
#define PAGODA_EXPECT_OP(op,val1,val2)              \
    if(!((val1) op (val2)))                         \
    {                                               \
        throw std::runtime_error("[Check failed]"#val1" "#op" "#val2);  \
    }
/* 
 *@brief:expect some logic expression to be true: ==,!=,>=,<=,>,<
 * */
#define PAGODA_EXPECT_EQ(val1,val2)     PAGODA_EXPECT_OP(== ,val1,val2)
#define PAGODA_EXPECT_NE(val1,val2)     PAGODA_EXPECT_OP(!= ,val1,val2)
#define PAGODA_EXPECT_GE(val1,val2)     PAGODA_EXPECT_OP(>= ,val1,val2)
#define PAGODA_EXPECT_LE(val1,val2)     PAGODA_EXPECT_OP(<= ,val1,val2)
#define PAGODA_EXPECT_GT(val1,val2)     PAGODA_EXPECT_OP(> ,val1,val2)
#define PAGODA_EXPECT_LT(val1,val2)     PAGODA_EXPECT_OP(< ,val1,val2)

/* 
 *@brief:expect tow double's equality
 * */
#define PAGODA_EXPECT_DOUBLE_EQ(val1,val2)                      \
    if((val1)-(val2)>0.0001||(val2)-(val1)>0.0001)              \
    {                                                           \
        throw std::runtime_error("[Check failed]"#val1" == "#val2);     \
    }
/* 
 *@brief: expect two c-string equality
 * */
#define PAGODA_EXPECT_CSTR_EQ(val1,val2)                        \
    if(strcmp((val1),(val2)) != 0)                              \
    {                                                           \
        throw std::runtime_error("[Check failed] cstr eq:"#val1","#val2);  \
    }
/* 
 *@brief: begin declare the test class
 * */
#define PAGODA_DACLARE_TEST_CLASS_BEGIN(name)               \
    class PAGODA_TEST_##name                                      \
    {                                                       \
        public:                                             \
               typedef void (PAGODA_TEST_##name::*TestCase)();       \
               void RegisterTestCase(TestCase testcase)     \
                {                                           \
                    m_testcases.push_back(testcase);        \
                }                                           \
        private:                                            \
               std::vector<TestCase> m_testcases;           \
        public:                                             \
               void RunAllTest()                            \
                {                                           \
                    fprintf(stderr,"\n--------------------------------"); \
                    fprintf(stderr,"--------------------------------\n"); \
                    fprintf(stderr,"Begin running test cases of %s:\n",#name);  \
                    unsigned int size = m_testcases.size();                 \
                    int count = size;                                       \
                    for( unsigned int i = 0;i<size ;i++)                    \
                    {                                                       \
                        try                                                 \
                        {                                                   \
                            fprintf(stderr,"[%d] ",i);                      \
                            (this->*m_testcases[i])();                              \
                        }                                                   \
                        catch(std::runtime_error &error)                    \
                        {                                                   \
                            fprintf(stderr," %s \n",error.what());          \
                            count--;                                        \
                        }                                                   \
                    }                                                       \
                    fprintf(stderr,"Total %u cases , passed %d\n",size,count);  \
                }                   
/*
 *@brief:declare the test case
 */
#define PAGODA_DACLARE_TEST_CASE(a)                                         \
        public:                                                             \
                void TestCase##a()                                          \
                {                                                           \
                    fprintf(stderr,"Running test case :%s \t",#a);          \
                    Run##a();                                               \
                    fprintf(stderr," [Passed]\n");                          \
                }                                                           \
        private:                                                            \
                void Run##a();
/*
 *@brief: declare the class end
 */
#define PAGODA_DACLARE_TEST_CLASS_END()                                     \
    };
/* 
 *@brief:define a instance of the test class used to  do the testing
 * */
#define PAGODA_DEFINE_TEST_OBJECT(name,obj) PAGODA_TEST_##name obj;
/*
 *@brief:define a test case
 */
#define PAGODA_DEFINE_TEST_CASE(name ,obj,a)                            \
    class PAGODA_TEST_CASE_##a                                          \
    {                                                                   \
        public:                                                         \
            PAGODA_TEST_CASE_##a(PAGODA_TEST_##name &tester)            \
            {                                                           \
                tester.RegisterTestCase(&PAGODA_TEST_##name::TestCase##a);  \
            }                                                           \
    };                                                                  \
    static PAGODA_TEST_CASE_##a g_test_##name##_case_##a(obj);          \
    void PAGODA_TEST_##name::Run##a()
/* 
 *@brief:run all the defined test cases
 * */
#define PAGODA_RUN_ALL_TESTCASES(obj) obj.RunAllTest();
/*
 *if the test class need to be access a class's protected or private members,
 *you should define PAGODA_NEED_ACCESS_PRIVATE_MEMBER before you include pagodaTest.h
 *and the use PAGODA_DECLARE_FRIEND to declare the test class to be a friend of 
 *the class to be tested
 */
#ifdef PAGODA_NEED_ACCESS_PRIVATE_MEMBER
#define PAGODA_DECLARE_FRIEND(name) friend class PAGODA_TEST_##name;
#else
#define PAGODA_DECLARE_FRIEND(name)
#endif //PAGODA_NEED_ACCESS_PRIVATE_MEMBER
#endif //_PAGODATEST_HEAD_H
