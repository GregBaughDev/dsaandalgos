#include "./trie.h"
#include "../test/test.h"

TEST_CASE("Trie test - 1")
{
    Trie trie;
    
    trie.insertWord("hello");
    trie.insertWord("hey");
    trie.insertWord("heaven");
    trie.insertWord("apple");
    trie.insertWord("zoo");
    trie.insertWord("application");
    trie.insertWord("bark");
    trie.insertWord("biting");
    trie.insertWord("feeling");
    trie.insertWord("extraneous");
    trie.insertWord("app");
    trie.insertWord("extra");
    trie.insertWord("allowing");
    trie.insertWord("gravity");
    trie.insertWord("gravitas");
    trie.insertWord("piling");
    trie.insertWord("piles");
    trie.insertWord("selecting");
    trie.insertWord("salsa");

    CHECK(trie.startsWith("gra") == true);
    CHECK(trie.search("piles") == true);
    CHECK(trie.search("extra") == true);
    CHECK(trie.search("ex") == false);
    CHECK(trie.startsWith("ex") == true);
    CHECK(trie.search("app") == true);
    CHECK(trie.startsWith("app") == true);
    CHECK(trie.search("extraneous") == true);
    CHECK(trie.startsWith("f") == true);
    CHECK(trie.startsWith("g") == true);
    CHECK(trie.startsWith("gravit") == true);

    CHECK(trie.search("zulu") == false);
    CHECK(trie.search("fantasy") == false);
    CHECK(trie.startsWith("amy") == false);
}