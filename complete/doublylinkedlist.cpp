#include "../header/doublylinkedlist.h"
#include "../test/test.h"
#include <optional>
#include <string>
/*
    Doubly Linked List
    Description: A doubly linked list is a data structure consisting of nodes that contain data and pointers to both the next and previous node in the sequence.
    Implementation Hint: Each node should have two pointers (next and prev) and handle both insertions and deletions by updating these pointers accordingly.
*/
TEST_CASE("testing DoublyLinkedList - 1")
{
    DoublyLinkedList<int> dLL;
    dLL.insertAtEnd(1);
    dLL.insertAtEnd(45);
    dLL.insertAtEnd(3);
    dLL.insertAtEnd(198);
    dLL.insertAtEnd(9482);
    dLL.insertAtEnd(10293);
    dLL.insertAtEnd(43);

    CHECK(dLL.search(1) == true);
    CHECK(dLL.search(43) == true);
    CHECK(dLL.search(45) == true);
    CHECK(dLL.search(10293) == true);
    CHECK(dLL.search(3) == true);
    CHECK(dLL.search(9482) == true);
    CHECK(dLL.search(198) == true);
    CHECK(dLL.getLength() == 7);

    CHECK(dLL.search(420) == false);
    CHECK(dLL.search(69) == false);
    CHECK(dLL.search(37) == false);

    CHECK(dLL.remove(45) == 45);
    CHECK(dLL.remove(3) == 3);
    CHECK(dLL.getLength() == 5);

    CHECK(dLL.remove(10293) == 10293);
    CHECK(dLL.remove(1) == 1);
    CHECK(dLL.remove(43) == 43);
    CHECK(dLL.getLength() == 2);
    CHECK(dLL.remove(9482) == 9482);
    CHECK(dLL.remove(198) == 198);
    CHECK(dLL.getLength() == 0);

    CHECK(dLL.remove(123) == std::nullopt);
    CHECK(dLL.remove(456) == std::nullopt);
    CHECK(dLL.getLength() == 0);
}

TEST_CASE("testing DoublyLinkedList - 2")
{
    DoublyLinkedList<int> dLL;
    dLL.insertAtEnd(20);
    dLL.insertAtStart(10);
    dLL.insertAtEnd(40);
    dLL.insertAtStart(104);
    dLL.insertAtEnd(123);
    dLL.insertAtEnd(987);
    dLL.insertAtStart(943);
    dLL.insertAtStart(1023);
    dLL.insertAtEnd(69);
    CHECK(dLL.getLength() == 9);
    dLL.printElements();

    CHECK(dLL.removeFromEnd() == 69);
    CHECK(dLL.removeFromStart() == 1023);
    CHECK(dLL.getLength() == 7);

    CHECK(dLL.removeFromEnd() == 987);
    CHECK(dLL.removeFromStart() == 943);
    CHECK(dLL.getLength() == 5);

    CHECK(dLL.removeFromEnd() == 123);
    CHECK(dLL.removeFromStart() == 104);
    CHECK(dLL.getLength() == 3);

    CHECK(dLL.removeFromEnd() == 40);
    CHECK(dLL.removeFromStart() == 10);
    CHECK(dLL.removeFromStart() == 20);
    CHECK(dLL.getLength() == 0);

    dLL.insertAtEnd(432);
    dLL.insertAtStart(9872);
    dLL.insertAtEnd(123);

    CHECK(dLL.getLength() == 3);
    CHECK(dLL.removeFromEnd() == 123);
    CHECK(dLL.removeFromEnd() == 432);
    CHECK(dLL.removeFromEnd() == 9872);
    CHECK(dLL.getLength() == 0);
}

TEST_CASE("testing DoublyLinkedList copy constructor")
{
    DoublyLinkedList<int> dLL1;
    dLL1.insertAtStart(134);
    dLL1.insertAtEnd(69);
    dLL1.insertAtStart(34);
    dLL1.insertAtStart(71);
    dLL1.insertAtEnd(1092);
    // 71, 34, 134, 69, 1092

    DoublyLinkedList dLL2(dLL1);
    dLL2.printElements();
    dLL2.removeFromEnd();   // 1092
    dLL2.removeFromStart(); // 71
    dLL2.insertAtEnd(1234);
    dLL2.insertAtStart(8794);
    // 8794, 34, 134, 69, 1234

    CHECK(dLL1.search(71) == true);
    CHECK(dLL2.search(71) == false);

    CHECK(dLL1.search(1092) == true);
    CHECK(dLL2.search(1092) == false);

    CHECK(dLL1.search(1234) == false);
    CHECK(dLL2.search(1234) == true);

    CHECK(dLL1.search(8794) == false);
    CHECK(dLL2.search(8794) == true);
}

TEST_CASE("testing DoublyLinkedList copy assignment operator")
{
    DoublyLinkedList<int> dLL1, dLL2;

    dLL1.insertAtStart(12);
    dLL1.insertAtStart(34);
    dLL1.insertAtStart(56);
    dLL1.insertAtStart(78);
    dLL1.insertAtStart(90);

    dLL2.insertAtStart(20);
    dLL2.insertAtStart(2);
    dLL2.insertAtStart(493);
    dLL2.insertAtStart(2002);
    dLL2.insertAtStart(39490);
    dLL2.insertAtStart(11);
    dLL2.insertAtStart(9);

    dLL2 = dLL1;

    CHECK(dLL1.removeFromStart() == 90);
    CHECK(dLL2.removeFromStart() == 90);

    CHECK(dLL1.removeFromStart() == 78);
    CHECK(dLL2.removeFromStart() == 78);

    CHECK(dLL1.removeFromStart() == 56);
    CHECK(dLL2.removeFromStart() == 56);

    dLL2.insertAtStart(584);
    dLL2.insertAtStart(19);
    dLL2.insertAtStart(9837);

    CHECK(dLL1.removeFromStart() == 34);
    CHECK(dLL1.removeFromStart() == 12);
    CHECK(dLL1.removeFromStart() == std::nullopt);

    CHECK(dLL2.removeFromStart() == 9837);
    CHECK(dLL2.removeFromStart() == 19);
    CHECK(dLL2.removeFromStart() == 584);
    CHECK(dLL2.removeFromStart() == 34);
    CHECK(dLL2.removeFromStart() == 12);
    CHECK(dLL2.removeFromStart() == std::nullopt);
}

TEST_CASE("testing DoublyLinkedList move constructor")
{
    DoublyLinkedList<int> dLL1;
    dLL1.insertAtStart(134);
    dLL1.insertAtEnd(69);
    dLL1.insertAtStart(34);
    dLL1.insertAtStart(71);
    dLL1.insertAtEnd(1092);

    DoublyLinkedList dLL2 = std::move(dLL1);
    CHECK(dLL2.getLength() == 5);
    dLL2.printElements();
    dLL2.removeFromEnd();   // 1092
    dLL2.removeFromStart(); // 71
    dLL2.insertAtEnd(1234);
    dLL2.insertAtStart(8794);
    // 8794, 34, 134, 69, 1234

    CHECK(dLL2.search(71) == false);
    CHECK(dLL2.search(1092) == false);
    CHECK(dLL2.search(1234) == true);
    CHECK(dLL2.search(8794) == true);
}

TEST_CASE("testing DoublyLinkedList move assignment operator")
{
    DoublyLinkedList<int> dLL1, dLL2;

    dLL1.insertAtStart(12);
    dLL1.insertAtStart(34);
    dLL1.insertAtStart(56);
    dLL1.insertAtStart(78);
    dLL1.insertAtStart(90);

    dLL2.insertAtStart(20);
    dLL2.insertAtStart(2);
    dLL2.insertAtStart(493);
    dLL2.insertAtStart(2002);
    dLL2.insertAtStart(39490);
    dLL2.insertAtStart(11);
    dLL2.insertAtStart(9);

    dLL2 = std::move(dLL1);

    CHECK(dLL2.removeFromStart() == 90);
    CHECK(dLL2.removeFromStart() == 78);
    CHECK(dLL2.removeFromStart() == 56);

    dLL2.insertAtStart(584);
    dLL2.insertAtStart(19);
    dLL2.insertAtStart(9837);

    CHECK(dLL2.removeFromStart() == 9837);
    CHECK(dLL2.removeFromStart() == 19);
    CHECK(dLL2.removeFromStart() == 584);
    CHECK(dLL2.removeFromStart() == 34);
    CHECK(dLL2.removeFromStart() == 12);
    CHECK(dLL2.removeFromStart() == std::nullopt);
}

TEST_CASE("testing templatifying the class")
{
    DoublyLinkedList<std::string> dLL;
    dLL.insertAtEnd("greg");
    dLL.insertAtEnd("michael");
    dLL.insertAtEnd("matt");
    dLL.insertAtEnd("jo");
    dLL.insertAtEnd("magnus");
    dLL.printElements();

    CHECK(dLL.search("greg") == true);
    CHECK(dLL.search("michael") == true);
    CHECK(dLL.search("terry") == false);

    CHECK(dLL.removeFromStart() == "greg");
    CHECK(dLL.removeFromStart() == "michael");
    CHECK(dLL.removeFromStart() == "matt");
    CHECK(dLL.removeFromStart() == "jo");
    CHECK(dLL.removeFromStart() == "magnus");
    CHECK(dLL.removeFromStart() == std::nullopt);
}
