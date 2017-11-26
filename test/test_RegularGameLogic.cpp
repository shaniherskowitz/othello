//
// Created by shani herskowitz on 11/23/17.
//
#include "RegularGameLogicTest.h"

TEST(GetMovesListTest, PlayerHasMoves) {
    RegularGameLogic regularGameLogic = RegularGameLogic();
    char path[] = "../boardFiles/board1";
    Board *board1 = new Board(path);
    vector<Move> boardMovesList = regularGameLogic.getMovesList(Tile('O'), *board1);
    const Move arr[] = {Move(Point(5, 3), 1), Move(Point(3, 5), 1), Move(Point(3, 3), 1)};;
    vector<Move> movesList (arr, arr + sizeof(arr) / sizeof(arr[0]) );
    EXPECT_EQ(regularGameLogic.getMovesList(Tile('O'), *board1), movesList);

}
TEST_F(RegularGameLogicTest, testLogic) {


}