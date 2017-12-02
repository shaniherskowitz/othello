cmake_minimum_required(VERSION 3.8)
project(othello)

set(CMAKE_CXX_STANDARD 98)

set(SOURCE_FILES main.cpp Board.cpp Board.h Tile.cpp Tile.h Point.cpp Point.h Game.cpp
        Game.h Player.cpp Player.h Move.cpp Move.h GameLogic.cpp GameLogic.h RegularGameLogic.cpp
        RegularGameLogic.h GameStatus.cpp GameStatus.h Score.cpp Score.h GameUI.cpp GameUI.h ConsolUI.cpp
        ConsolUI.h HumanPlayer.cpp HumanPlayer.h Menu.cpp Menu.h AIPlayer.cpp AIPlayer.h)

add_executable(othello ${SOURCE_FILES})


#Add the google test subdirectory
add_subdirectory(googletest-release-1.8.0 )

#include googletest/include dir
include_directories(googletest-release-1.8.0/googletest/include)

#include the googlemock/include dir
include_directories(googletest-release-1.8.0/googlemock/include)

include_directories(/test)


set(SOURCE_FILES2 Board.cpp Board.h Tile.cpp Tile.h Point.cpp Point.h Game.cpp Game.h Player.cpp
        Player.h Move.cpp Move.h GameLogic.cpp GameLogic.h RegularGameLogic.cpp RegularGameLogic.h GameStatus.cpp
        GameStatus.h Score.cpp Score.h GameUI.cpp GameUI.h ConsolUI.cpp ConsolUI.h HumanPlayer.cpp HumanPlayer.h
        Menu.cpp Menu.h AIPlayer.cpp AIPlayer.h test/test_main.cpp test/test_RegularGameLogic.cpp
        test/test_Board.cpp test/AIPlayerTest.cpp test/AIPlayerTest.h test/test_RegularGameLogic.h)


add_executable(test_main.cpp ${SOURCE_FILES2})

#Link with GoogleTest
target_link_libraries(test_main.cpp gtest gtest_main)

#Link with GoogleMock
target_link_libraries(test_main.cpp gmock gmock_main)