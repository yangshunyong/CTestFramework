# CTestFramework
## Run the Test
> mkdir build </br>
> cmake .. </br>
> make </br>
> ctest -V </br>

The "-V" option is to enable console log output in the cases.
## Integrate to Other Projects
1. Copy CTestFramework.h, ctest.cmake, CMakeLists.txt to the new project. </br>
2. Take TestExample.cpp as a refrence to write your own test cases.</br>
3. Add your test case in CMakeLists.txt by create_test_app(), please NOTE the app name should be the first part of cpp source file name. </br> 
   For example, suppose the source file name is mytest.cpp, the command should be,</br>
> create_test_app(mytest)</br>

