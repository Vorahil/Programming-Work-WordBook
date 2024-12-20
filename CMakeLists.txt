cmake_minimum_required(VERSION 3.28)
project(Programming)

set(CMAKE_CXX_STANDARD 17)
add_executable(Programming src/main.cpp
        src/homePage/Login.cpp
        src/homePage/Login.h
        src/entity/Customer.cpp
        src/entity/Customer.h
        src/homePage/Register.cpp
        src/homePage/Register.h
        src/entity/Word.cpp
        src/entity/Word.h
        src/WordOperator/AddWord.h
        src/WordOperator/AddWord.cpp
        src/WordOperator/DeleteWord.h
        src/WordOperator/DeleteWord.cpp
        src/WordOperator/ModifyWord.h
        src/WordOperator/ModifyWord.cpp
        src/WordOperator/AddMeaning.h
        src/WordOperator/AddMeaning.cpp
        src/WordOperator/ViewWords.h
        src/WordOperator/ViewWords.cpp
        src/memorizeWord/ChoiceQ.cpp
        src/memorizeWord/ChoiceQ.h
        src/memorizeWord/BlankQ.h
        src/memorizeWord/BlankQ.cpp
        src/memorizeWord/QModel.cpp
        src/memorizeWord/QModel.h
        src/homePage/UserData.h
        src/homePage/UserData.cpp
)
