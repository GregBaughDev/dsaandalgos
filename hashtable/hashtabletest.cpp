#include "./hashtable.h"
#include "../test/test.h"

void setupTestTable(HashTable *table)
{
    table->put("aaaa", 10);
    table->put("feelingfishes", 40);
    table->put("aaab", 11);
    table->put("aaac", 12);
    table->put("aaad", 13);
    table->put("aaae", 14);
    table->put("aaaf", 15);
    table->put("aaag", 16);
    table->put("aaah", 17);
    table->put("aaai", 18);
    table->put("aaaj", 19);
    table->put("baag", 21);
    table->put("abag", 22);
    table->put("distraction", 10);
    table->put("kikiaaabv", 150);
    table->put("caah", 23);
    table->put("hhhaa", 30);
    table->put("bbbg", 35);
    table->put("loool", 40);
    table->put("abbbababba", 41);
    table->put("ginanna", 42);
    table->put("gaga", 43);
    table->put("sleight", 45);
    table->put("furocious", 50);
    table->put("tenderaaa", 60);
    table->put("g", 65);
    table->put("a", 70);
    table->put("zulu", 100);
    table->put("zendslaya", 101);
    table->put("titantic", 150);
    table->put("hurtinggggaa", 200);
    table->put("aaak", 20);
    table->put("previousprevious", 1001);
    table->put("fortitudeattitude", 1069);
    table->put("gaaa", 25);
    table->put("tenderlay", 1);
    table->put("hbosgirls", 10000);
    table->put("marnie", 99938);
    table->put("elektra", 90);
    table->put("hopefullytheresenoughvariance", 25);
    table->put("aaaai", 10101);
}

TEST_CASE("HashTable test")
{
    HashTable ht{20};
    setupTestTable(&ht);
    
    CHECK(ht.containsKey("titantic") == true);
    CHECK(ht.containsKey("kikiaaabv") == true);
    CHECK(ht.containsKey("aaah") == true);
    CHECK(ht.containsKey("distraction") == true);
    CHECK(ht.containsKey("fortitudeattitude") == true);
    CHECK(ht.containsKey("loool") == true);
    CHECK(ht.containsKey("marnie") == true);

    CHECK(ht.containsKey("shouldn'tbethere") == false);
    CHECK(ht.containsKey("fabs") == false);
    CHECK(ht.containsKey("treacle") == false);

    CHECK(ht.containsValue(10) == true);
    CHECK(ht.containsValue(23) == true);
    CHECK(ht.containsValue(70) == true);
    CHECK(ht.containsValue(1069) == true);
    CHECK(ht.containsValue(99938) == true);

    CHECK(ht.containsValue(4) == false);
    CHECK(ht.containsValue(99999) == false);
    CHECK(ht.containsValue(1029384) == false);

    CHECK(ht.size() == 41);
}

TEST_CASE("HashTable test 2")
{
    HashTable ht{10};
    setupTestTable(&ht);

    // get
    CHECK(ht.get("aaaj") == 19);
    CHECK(ht.get("distraction") == 10);
    CHECK(ht.get("ginanna") == 42);
    CHECK(ht.get("bbbg") == 35);
    CHECK(ht.get("gaga") == 43);
    CHECK(ht.get("a") == 70);

    CHECK_THROWS_WITH_AS(
        ht.get("yassmother"), 
        "Key yassmother not found in the table",
        std::runtime_error
    );

    // replace
    ht.replace("sleight", 1001);
    CHECK(ht.get("sleight") == 1001);

    ht.replace("furocious", 1234);
    CHECK(ht.get("furocious") == 1234);

    ht.replace("elektra", 1989);
    CHECK(ht.get("elektra") == 1989);

    CHECK_THROWS_WITH_AS(
        ht.replace("painsofbeing", 1234),
        "Unable to replace painsofbeing as it doesn't exist",
        std::runtime_error
    );

    CHECK(ht.size() == 41);

    // remove
    CHECK(ht.remove("hbosgirls") == 10000);
    CHECK(ht.remove("previousprevious") == 1001);
    CHECK(ht.remove("sleight") == 1001);

    CHECK(ht.size() == 38);

    CHECK_THROWS_WITH_AS(
        ht.remove("carlos"),
        "Unable to remove carlos as it doesn't exist",
        std::runtime_error
    );

    // re-add
    ht.put("hbosgirls", 120);
    CHECK(ht.get("hbosgirls") == 120);
    ht.replace("hbosgirls", 40404);
    CHECK(ht.get("hbosgirls") == 40404);

    // clear
    ht.clear();

    CHECK(ht.size() == 0);

    ht.put("charleess", 768594);
    ht.put("pegasus", 123);
    ht.put("allowwssmee", 345);
    
    CHECK(ht.get("charleess") == 768594);
    CHECK(ht.get("pegasus") == 123);
    CHECK(ht.get("allowwssmee") == 345);

    CHECK(ht.size() == 3);
}