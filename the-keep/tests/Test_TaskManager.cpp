/**
 * @filename: Test_TaskManager.cpp
 * @description: To test the TaskManager of the Keep.
 * @author: KeepId
 * @date: March 27, 2022
 */

#include <gtest/gtest.h>

#include "../core/task-manager/TaskManager.hpp"

using namespace std;

/**
 * ConstructorDestructor - Test that the constructr and destructor of
 *                         the TaskManager clas works correctly.
 */
TEST(TestTaskManager, ConstructorDestructor){
    TaskManager* manager = new TaskManager();
    EXPECT_FALSE(manager->isRunning());
    delete manager;
}

// TODO, create mock classes and test the actually algorithm.
