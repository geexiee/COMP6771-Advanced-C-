/*

  == Explanation and rational of testing ==

  The scope of my tests are quite limited due to the fact that we are meant to test this as a black
  box, so the only real variation in tests I could make was in the length of the words and the
  length/depth of the ladders created. (depth = number of hops) I wanted to test small, medium, and
  large cases for both length of word and depth of ladders/words. I want to test this range of cases
  because my program could potentially run into unexpected bugs as the ladders get longer and the
  bfs gets bigger.

  I first wanted to ensure that edge cases were covered. However, the only real edge case is when
  there is no ladder. This is because the specs specified that all input was going to be valid and
  taken from the lexicon, so no point testing for things such as no input, diff length start/end
  word etc. I also decided to test the edge case of the start and end word being the same, as there
  was no mention of that being invalid input.

  My tests should be quite thorough as they cover all types of words and cases (long/short length
  words, long/short length ladders) If they pass these tests, the should work for all cases, though
  some harder cases may take a lot more time due to inefficiencies in my code.

*/

#include "assignments/wl/word_ladder.h"
#include "catch.h"

// Testing for when there is no ladder
SCENARIO("No Ladder Exists") {
  GIVEN("Two words that don't have a ladder connecting them") {
    std::string start = "airplane", end = "tricycle";
    REQUIRE(start == "airplane");
    REQUIRE(end == "tricycle");

    std::vector<std::vector<std::string>> expected_ladder = {};
    WHEN("You try to find the ladders from airplane to tricycle") {
      std::vector<std::vector<std::string>> master_ladder = GetLadders(start, end);
      THEN("No ladder should get generated") { REQUIRE(master_ladder == expected_ladder); }
    }
  }
}

// Testing for when start and end word are the same
SCENARIO("Testing when start and end words are the same") {
  GIVEN("'work' as a starting word and 'work' as an ending word") {
    std::string start = "work", end = "work";
    REQUIRE(start == "work");
    REQUIRE(end == "work");

    std::vector<std::vector<std::string>> expected_ladder = {{"work", "work"}};
    WHEN("You try to find the ladders from work to work") {
      std::vector<std::vector<std::string>> master_ladder = GetLadders(start, end);
      THEN("The correct ladders get generated") { REQUIRE(master_ladder == expected_ladder); }
    }
  }
}

// Testing for short words
SCENARIO("Testing short length/depth words") {
  GIVEN("'at' as a starting word and 'it' as an ending word") {
    std::string start = "at", end = "it";
    REQUIRE(start == "at");
    REQUIRE(end == "it");

    std::vector<std::vector<std::string>> expected_ladder = {{"at", "it"}};
    WHEN("You try to find the ladders from at to it") {
      std::vector<std::vector<std::string>> master_ladder = GetLadders(start, end);
      THEN("The correct ladders get generated") { REQUIRE(master_ladder == expected_ladder); }
    }
  }
}

// Testing for medium length words
SCENARIO("Testing medium length words") {
  GIVEN("work as a starting word and play as an ending word") {
    std::string start = "work", end = "play";
    REQUIRE(start == "work");
    REQUIRE(end == "play");

    std::vector<std::vector<std::string>> expected_ladder = {
        {"work", "fork", "form", "foam", "flam", "flay", "play"},
        {"work", "pork", "perk", "peak", "pean", "plan", "play"},
        {"work", "pork", "perk", "peak", "peat", "plat", "play"},
        {"work", "pork", "perk", "pert", "peat", "plat", "play"},
        {"work", "pork", "porn", "pirn", "pian", "plan", "play"},
        {"work", "pork", "port", "pert", "peat", "plat", "play"},
        {"work", "word", "wood", "pood", "plod", "ploy", "play"},
        {"work", "worm", "form", "foam", "flam", "flay", "play"},
        {"work", "worn", "porn", "pirn", "pian", "plan", "play"},
        {"work", "wort", "bort", "boat", "blat", "plat", "play"},
        {"work", "wort", "port", "pert", "peat", "plat", "play"},
        {"work", "wort", "wert", "pert", "peat", "plat", "play"}};
    WHEN("You try to find the ladders from work to play") {
      std::vector<std::vector<std::string>> master_ladder = GetLadders(start, end);
      THEN("The correct ladders get generated") { REQUIRE(master_ladder == expected_ladder); }
    }
  }
}

// Testing for long length words
SCENARIO("Testing long length words") {
  GIVEN("blistering as a starting word and blithering as an ending word") {
    std::string start = "blistering", end = "blithering";
    REQUIRE(start == "blistering");
    REQUIRE(end == "blithering");

    std::vector<std::vector<std::string>> expected_ladder = {
        {"blistering", "blustering", "clustering", "cluttering", "clattering", "blattering",
         "blathering", "blithering"},
        {"blistering", "blustering", "flustering", "fluttering", "flattering", "blattering",
         "blathering", "blithering"},
        {"blistering", "glistering", "glittering", "flittering", "flattering", "blattering",
         "blathering", "blithering"}};
    WHEN("You try to find the ladders from blistering to blithering") {
      std::vector<std::vector<std::string>> master_ladder = GetLadders(start, end);
      THEN("The correct ladders get generated") { REQUIRE(master_ladder == expected_ladder); }
    }
  }
}

// Testing medium depth words (at->it already covered short depth)
SCENARIO("Testing medium depth words") {
  GIVEN("awake as a starting word and sleep as an ending word") {
    std::string start = "awake", end = "sleep";
    REQUIRE(start == "awake");
    REQUIRE(end == "sleep");

    std::vector<std::vector<std::string>> expected_ladder = {
        {"awake", "aware", "sware", "share", "sharn", "shawn", "shewn", "sheen", "sheep", "sleep"},
        {"awake", "aware", "sware", "share", "shire", "shirr", "shier", "sheer", "sheep", "sleep"}};
    WHEN("You try to find the ladders from awake to sleep") {
      std::vector<std::vector<std::string>> master_ladder = GetLadders(start, end);
      THEN("The correct ladders get generated") { REQUIRE(master_ladder == expected_ladder); }
    }
  }
}

// Testing long depth words
SCENARIO("Testing long depth words") {
  GIVEN("decanting as a starting and derailing as an ending word") {
    std::string start = "decanting", end = "derailing";
    REQUIRE(start == "decanting");
    REQUIRE(end == "derailing");

    std::vector<std::vector<std::string>> expected_ladder = {
        {"decanting", "recanting", "recasting", "retasting", "retesting", "revesting", "revetting",
         "reletting", "relenting", "relending", "remending", "remanding", "remanning", "remaining",
         "remailing", "retailing", "detailing", "derailing"},
        {"decanting", "recanting", "recasting", "retasting", "retesting", "revesting", "revetting",
         "reletting", "relenting", "relending", "remending", "remanding", "remanning", "remaining",
         "retaining", "detaining", "detailing", "derailing"},
        {"decanting", "recanting", "recasting", "retasting", "retesting", "revesting", "revetting",
         "reletting", "relenting", "relending", "remending", "remanding", "remanning", "remaining",
         "retaining", "retailing", "detailing", "derailing"},
        {"decanting", "recanting", "recasting", "retasting", "retesting", "revesting", "revetting",
         "resetting", "resenting", "resending", "remending", "remanding", "remanning", "remaining",
         "remailing", "retailing", "detailing", "derailing"},
        {"decanting", "recanting", "recasting", "retasting", "retesting", "revesting", "revetting",
         "resetting", "resenting", "resending", "remending", "remanding", "remanning", "remaining",
         "retaining", "detaining", "detailing", "derailing"},
        {"decanting", "recanting", "recasting", "retasting", "retesting", "revesting", "revetting",
         "resetting", "resenting", "resending", "remending", "remanding", "remanning", "remaining",
         "retaining", "retailing", "detailing", "derailing"},
    };
    WHEN("You try to find the ladders from decanting to derailing") {
      std::vector<std::vector<std::string>> master_ladder = GetLadders(start, end);
      THEN("The correct ladders get generated") { REQUIRE(master_ladder == expected_ladder); }
    }
  }
}
