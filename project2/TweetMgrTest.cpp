// File name: TweetMgrTest.cpp
// Author: Scott Kang
// VUnetid: kangk
// Email: kyung.ho.kang@vanderbilt.edu
// Class: CS2201
// Date: 2019 9/23
// Honor statement: I have not given or received unauthorized aid on this assignment
// Assignment Number: #2
// Description: This program will test the TweetMgr class

#include <iostream>
#include <string>
#include <stdexcept>
#include "TweetMgr.h"

int main() {

    TweetMgr empty;
    if (empty.getTweets() != "") {
        std::cout << "failed" << std::endl;
    }

    TweetMgr test1;
    Tweet first(4, "scott", "first");
    test1.addTweet(first);

    Tweet second(0, "jane", "second");
    test1.addTweet(second);

    if (test1.getTweets() != "jane: second (sent at 0)\n"
                             "scott: first (sent at 4)\n") {
        std::cout << "not added correctly to the first position when non empty tweet Manager" << std::endl;
        std::cout << test1.getTweets() << std::endl;
    }

    // Here is some sample code that does some simple testing of the TweetMgr class.
    // It creates an empty TweetMgr and performs some test on it.
    // It then adds a tweet to the TweetMgr and performs some other tests on it.
    // This is only a simple sample, and is not considered to be very thorough.

    std::cout << "Testing TweetMgr..." << std::endl;


    TweetMgr tm1;   // create an empty TweetMgr object via default ctor

    if (tm1.getNumTweets() != (size_t) 0) {  // test getnumTweets()
        std::cout << "Default ctor failed to create an empty TweetMgr" << std::endl;
        std::cout << "Reported that " << tm1.getNumTweets() << " tweets exist" << std::endl;
    }

    //Test if String getTweets returns an empty line if the TweetMgr is empty

    if (tm1.getTweets() != "") {  // test getTweets()
        std::cout << "Default ctor should produce an empty TweetMgr" << std::endl;
        std::cout << "getTweets returned the following non-empty tweets: " << tm1.getTweets()
                  << std::endl;
    }

    Tweet twt1(0, "@jack", "just setting up my twttr");  //first tweet ever

    size_t index = tm1.addTweet(twt1);   // test addTweet(); TweetMgr now has one tweet


    if (index != (size_t) 0) {
        std::cout << "addTweet failed to return index 0 for first insertion" << std::endl;
        std::cout << "Returned index == " << index << std::endl;
    }

    if (tm1.getNumTweets() != (size_t) 1) {
        std::cout << "addTweet/getNumTweets failed after inserting one tweet" << std::endl;
        std::cout << "Reported that " << tm1.getNumTweets() << " tweets exist" << std::endl;
    }

    if (tm1.getTweets() != "@jack: just setting up my twttr (sent at 0)\n") {
        std::cout << "Unexpected tweet in collection" << std::endl;
        std::cout << "getTweets() returned the following tweets: " << tm1.getTweets() << std::endl;
    }

    if (tm1.getTweets(0) != "@jack: just setting up my twttr (sent at 0)\n") {
        std::cout << "Unexpected tweet in collection" << std::endl;
        std::cout << "getTweets(0) returned the following tweets: "
                  << tm1.getTweets(0) << std::endl;
    }

    //Test if addTweet correctly adds tweets according to their timespan
    Tweet twt2(3, "@tom", "I am tom");
    Tweet twt5(5, "@jane", "I am jane");
    size_t index2 = tm1.addTweet(twt2);
    size_t index5 = tm1.addTweet(twt5);


    if (index2 >= index5) {
        std::cout << "Tweet not adding in chronological order" << std::endl;
    }

    //Test if addTweet correctly adds tweets when they have the same timespan

    Tweet twt3(3, "@Tom", "I am Tom");
    size_t index3 = tm1.addTweet(twt3);
    if (index3 != index2 + (size_t) 1) {
        std::cout << "Tweets with same timespan not adding correctly" << std::endl;
    }
    Tweet twt4(4, "@jack", "I am jack2");
    size_t index4 = tm1.addTweet(twt4);
    if (index4 != index3 + (size_t) 1) {
        std::cout << "Tweets not inserted correctly according to the timespan" << std::endl;
    }

    //Test if getNumTweets work fine - returning the number of tweets in the collection

    size_t numberOfTweets = tm1.getNumTweets();
    if (numberOfTweets != 5) {
        std::cout << "Number of tweets in the collection is wrong" << std::endl;
    }

    TweetMgr fullTweets;

    try {
        for (int i = 0; i < 50; i++) {
            fullTweets.addTweet(twt1);
        }
    }
    catch (std::overflow_error &excpt) {
        std::cout << "50 tweets were not added" << excpt.what() << std::endl;
    }

    //testing if copy constructor works correctly.

    //copy constructor - second tweet manager has some tweets

    TweetMgr ttt = tm1;
    if (ttt.getTweets() != "@jack: just setting up my twttr (sent at 0)\n"
                           "@tom: I am tom (sent at 3)\n"
                           "@Tom: I am Tom (sent at 3)\n"
                           "@jack: I am jack2 (sent at 4)\n"
                           "@jane: I am jane (sent at 5)\n") {
        std::cout << "copy ctr failed" << std::endl;
    }

    // copy constructor - second tweet manager is empty
    TweetMgr aaa;
    TweetMgr bbb = aaa;

    if (bbb.getTweets() != "") {
        std::cout << "copy ctr failed\n" << ttt.getTweets() << std::endl;
    }

    // copy constructor - second tweet manager has tweets over 50

    TweetMgr ccc;
    for(int i = 0; i < 100; i++){
        Tweet lol(i, "add", "add");
        ccc.addTweet(lol);
    }

    TweetMgr ddd = ccc;

    if(ddd.maxSize() != 100){
        std::cout << "copy ctr failed. for tweetmgr over 50 " << ddd.maxSize() << std::endl;
    }

    if(ddd.getNumTweets() != 100){
        std::cout << "copy ctr failed. for tweetmgr over 50 " << ddd.getNumTweets() << std::endl;
    }

    // testing if assignment operator works correctly

    // = operator with the second tweetManger having some tweets
    bbb = tm1;

    if (bbb.getTweets() != "@jack: just setting up my twttr (sent at 0)\n"
                           "@tom: I am tom (sent at 3)\n"
                           "@Tom: I am Tom (sent at 3)\n"
                           "@jack: I am jack2 (sent at 4)\n"
                           "@jane: I am jane (sent at 5)\n") {
        std::cout << "= operator failed\n" << bbb.getTweets() << std::endl;
    }

    // = operator with the second tweetManager being the same as the first one
    bbb = tm1;

    if (bbb.getTweets() != "@jack: just setting up my twttr (sent at 0)\n"
                           "@tom: I am tom (sent at 3)\n"
                           "@Tom: I am Tom (sent at 3)\n"
                           "@jack: I am jack2 (sent at 4)\n"
                           "@jane: I am jane (sent at 5)\n") {
        std::cout << "= operator failed\n" << bbb.getTweets() << std::endl;
    }

    // = operator with the second tweetManager being empty
    TweetMgr empty1;

    bbb = empty1;
    if (bbb.getTweets() != "") {
        std::cout << "= operator failed\n" << bbb.getTweets() << std::endl;
    }

    // = operator with the first tweetManager being empty
    TweetMgr empty2;

    empty2 = tm1;
    if (empty2.getTweets() != "@jack: just setting up my twttr (sent at 0)\n"
                              "@tom: I am tom (sent at 3)\n"
                              "@Tom: I am Tom (sent at 3)\n"
                              "@jack: I am jack2 (sent at 4)\n"
                              "@jane: I am jane (sent at 5)\n") {
        std::cout << "= operator failed\n" << empty2.getTweets() << std::endl;
    }

    // = operator with both the first and second tweetManager being empty
    TweetMgr empty3;

    empty3 = empty1;
    if (empty3.getTweets() != "") {
        std::cout << "= operator failed\n" << empty3.getTweets() << std::endl;
    }

    // testing alternate constructor

    TweetMgr newtest(10);
    if(newtest.maxSize() != 10){
        std::cout << "alternate constructor failed\n" << newtest.maxSize() << std::endl;
    }
    if(newtest.getNumTweets() != 0){
        std::cout << "alternate constructor - number of tweets - failed\n" << newtest.getNumTweets() << std::endl;
    }

    // alternate constructor - initsize is zero

    try {
        TweetMgr newtest2(0);
    }
    catch (std::invalid_argument &excpt) {
        std::cout << "initsize as 0 - Exception successfully thrown & caught:: " << excpt.what() << std::endl;
    }

    //testing merge

    // second tweetmgr all greater time span than the first tweetmgr
    TweetMgr ttest1;
    Tweet t1(10, "@a", "just setting up my twttr");  //first tweet ever
    Tweet t2(11, "@b", "just setting up my twttr");  //first tweet ever
    Tweet t3(12, "@c", "just setting up my twttr");  //first tweet ever
    Tweet t4(13, "@d", "just setting up my twttr");  //first tweet ever
    Tweet t5(14, "@e", "just setting up my twttr");  //first tweet ever
    ttest1.addTweet(t1);
    ttest1.addTweet(t2);
    ttest1.addTweet(t3);
    ttest1.addTweet(t4);
    ttest1.addTweet(t5);

    TweetMgr ttest3 = ttest1;

    ttt.merge(ttest1);
    if (ttt.getTweets() != "@jack: just setting up my twttr (sent at 0)\n"
                           "@tom: I am tom (sent at 3)\n"
                           "@Tom: I am Tom (sent at 3)\n"
                           "@jack: I am jack2 (sent at 4)\n"
                           "@jane: I am jane (sent at 5)\n"
                           "@a: just setting up my twttr (sent at 10)\n"
                           "@b: just setting up my twttr (sent at 11)\n"
                           "@c: just setting up my twttr (sent at 12)\n"
                           "@d: just setting up my twttr (sent at 13)\n"
                           "@e: just setting up my twttr (sent at 14)\n") {

        std::cout << "merge didn't work correctly\n" << ttt.getTweets() << std::endl;
    }
    if(ttt.getNumTweets() != 10){
        std::cout << "merge didn't add correctly\n" << ttt.getNumTweets() << std::endl;
    }
    if(ttt.maxSize() != 50){
        std::cout << "merge didn't have correct maxsize\n" << ttt.getNumTweets() << std::endl;
    }


    // second tweetmgr all smaller time span than the first tweetmgr
    TweetMgr ttest2;
    Tweet tt1(1, "@aa", "just setting up my twttr");  //first tweet ever
    Tweet tt2(2, "@bb", "just setting up my twttr");  //first tweet ever
    Tweet tt3(3, "@cc", "just setting up my twttr");  //first tweet ever
    Tweet tt4(4, "@dd", "just setting up my twttr");  //first tweet ever
    Tweet tt5(5, "@ee", "just setting up my twttr");  //first tweet ever
    ttest2.addTweet(tt1);
    ttest2.addTweet(tt2);
    ttest2.addTweet(tt3);
    ttest2.addTweet(tt4);
    ttest2.addTweet(tt5);

    ttest3.merge(ttest2);

    if (ttest3.getTweets() != "@aa: just setting up my twttr (sent at 1)\n"
                              "@bb: just setting up my twttr (sent at 2)\n"
                              "@cc: just setting up my twttr (sent at 3)\n"
                              "@dd: just setting up my twttr (sent at 4)\n"
                              "@ee: just setting up my twttr (sent at 5)\n"
                              "@a: just setting up my twttr (sent at 10)\n"
                              "@b: just setting up my twttr (sent at 11)\n"
                              "@c: just setting up my twttr (sent at 12)\n"
                              "@d: just setting up my twttr (sent at 13)\n"
                              "@e: just setting up my twttr (sent at 14)\n") {

        std::cout << "merge didn't work correctly\n" << ttest3.getTweets() << std::endl;
    }
    if(ttest3.getNumTweets() != 10){
        std::cout << "merge didn't add correctly\n" << ttest3.getNumTweets() << std::endl;
    }
    if(ttest3.maxSize() != 50){
        std::cout << "merge didn't have correct maxsize\n" << ttest3.getNumTweets() << std::endl;
    }

    // testing merge - first and second tweetmanager mixed timespan

    TweetMgr ttest4;

    Tweet ttt1(2, "@aaa", "just setting up my twttr");
    Tweet ttt2(4, "@bbb", "just setting up my twttr");
    Tweet ttt3(6, "@ccc", "just setting up my twttr");
    Tweet ttt4(8, "@ddd", "just setting up my twttr");
    Tweet ttt5(10, "@eee", "just setting up my twttr");

    ttest4.addTweet(ttt1);
    ttest4.addTweet(ttt2);
    ttest4.addTweet(ttt3);
    ttest4.addTweet(ttt4);
    ttest4.addTweet(ttt5);

    TweetMgr ttest5;

    Tweet ttt6(1, "@A", "just setting up my twttr");
    Tweet ttt7(3, "@B", "just setting up my twttr");
    Tweet ttt8(5, "@C", "just setting up my twttr");
    Tweet ttt9(7, "@D", "just setting up my twttr");
    Tweet ttt10(9, "@E", "just setting up my twttr");

    ttest5.addTweet(ttt6);
    ttest5.addTweet(ttt7);
    ttest5.addTweet(ttt8);
    ttest5.addTweet(ttt9);
    ttest5.addTweet(ttt10);

    ttest4.merge(ttest5);

    if (ttest4.getTweets() != "@A: just setting up my twttr (sent at 1)\n"
                              "@aaa: just setting up my twttr (sent at 2)\n"
                              "@B: just setting up my twttr (sent at 3)\n"
                              "@bbb: just setting up my twttr (sent at 4)\n"
                              "@C: just setting up my twttr (sent at 5)\n"
                              "@ccc: just setting up my twttr (sent at 6)\n"
                              "@D: just setting up my twttr (sent at 7)\n"
                              "@ddd: just setting up my twttr (sent at 8)\n"
                              "@E: just setting up my twttr (sent at 9)\n"
                              "@eee: just setting up my twttr (sent at 10)\n") {

        std::cout << "merge didn't work correctly\n" << ttest4.getTweets() << std::endl;
    }

    // testing merge where number of the tweets combined is bigger than the current size
    // check if the size changes correctly

    TweetMgr leftSide;

    for (int i = 0; i < 50; i++) {
        Tweet mtest1(i, "a", "lol");
        leftSide.addTweet(mtest1);
    }

    TweetMgr rightSide;
    for (int i = 0; i < 50; i++) {
        Tweet mtest2(i, "b", "lol");
        rightSide.addTweet(mtest2);
    }

    leftSide.merge(rightSide);

    if (leftSide.maxSize() != 150) {
        std::cout << "merged tweetManager did not grow correctly" << std::endl;
        std::cout << leftSide.maxSize() << std::endl;
    }
    if (leftSide.getNumTweets() != 100) {
        std::cout << "merged tweetManager did not grow correctly" << std::endl;
        std::cout << leftSide.getNumTweets() << std::endl;
    }

    //test if merge puts the tweet from the second tweetmgr behind the first tweetmanager if the tweets have the same
    // timespan

    if (leftSide.getTweets(0, 1) != "a: lol (sent at 0)\n"
                                    "b: lol (sent at 0)\n"
                                    "a: lol (sent at 1)\n"
                                    "b: lol (sent at 1)\n") {
        std::cout << "merged tweetManager did not add correctly when same timespan" << std::endl;
        std::cout << leftSide.getTweets(0, 1) << std::endl;
    }


    // merge one with no element.
    TweetMgr rightSide2;

    leftSide.merge(rightSide2);
    if (leftSide.maxSize() != 150) {
        std::cout << "merged tweetManager did not grow correctly" << std::endl;
        std::cout << leftSide.maxSize() << std::endl;
    }

    if (leftSide.getNumTweets() != 100) {
        std::cout << "merged tweetManager did not grow correctly" << std::endl;
        std::cout << leftSide.getNumTweets() << std::endl;
    }

    //merge both with no elements

    TweetMgr leftSide2;

    leftSide2.merge(rightSide2);
    if (leftSide2.maxSize() != DEFAULT_SIZE) {
        std::cout << "merged tweetManager do not have Default max size" << std::endl;
        std::cout << leftSide2.maxSize() << std::endl;
    }
    if (leftSide2.getNumTweets() != 0) {
        std::cout << "merged tweetManager did not grow correctly" << std::endl;
        std::cout << leftSide2.getNumTweets() << std::endl;
    }

    //merge with two different size tweet manager
    TweetMgr leftSide3;
    TweetMgr rightSide3;

    for(int i = 0; i < 100; i++){
        Tweet mtest3(i, "a", "a");
        leftSide3.addTweet(mtest3);  //leftSide3: maxSize=100, numTweets = 100
    }

    for(int i = 0; i < 50; i++){
        Tweet mtest4(i, "a", "a");
        rightSide3.addTweet(mtest4);  //rightSide3: maxSize=50, numTweets = 50
    }

    leftSide3.merge(rightSide3);

    if (leftSide3.maxSize() != 200) {
        std::cout << "merged tweetManager do not have correct max size" << std::endl;
        std::cout << leftSide3.maxSize() << std::endl;
    }
    if (leftSide3.getNumTweets() != 150) {
        std::cout << "merged tweetManager did not add correctly" << std::endl;
        std::cout << leftSide3.getNumTweets() << std::endl;
    }

    //  merge with one less than 50 and one with 50

    TweetMgr leftSide4;

    for(int i = 0; i < 20; i++){
        Tweet mtest3(i, "a", "a");
        leftSide4.addTweet(mtest3);  //leftSide3: maxSize=100, numTweets = 100
    }

    leftSide4.merge(rightSide3);

    if (leftSide4.maxSize() != 120) {
        std::cout << "merged tweetManager do not have correct max size" << std::endl;
        std::cout << leftSide4.maxSize() << std::endl;
    }
    if (leftSide4.getNumTweets() != 70) {
        std::cout << "merged tweetManager did not add correctly" << std::endl;
        std::cout << leftSide4.getNumTweets() << std::endl;
    }

    //test addTweet (for project 2)

    //adding one more to a full tweetManager
    TweetMgr fulllll;

    for (size_t i = 0; i < DEFAULT_SIZE; i++) {
        Tweet element(i, "filled", "filled");
        fulllll.addTweet(element);
    }

    //check if adding more to the full tweetmanager throws an error
    try{
        fulllll.addTweet(twt1);
    }catch(std::invalid_argument &excpt){
        std::cout << "couldn't add a tweet to a full tweetManager" << excpt.what() << std::endl;
    }

    //checking if maxSize changed correctly

    if (fulllll.maxSize() != 100) {
        std::cout << "didn't add to a full tweet\n" << fulllll.
                maxSize()<<std::endl;
    }
    //checking if tweet goes up by one
    if (fulllll. getNumTweets() != 51) {
        std::cout << "didn't add to a full tweet\n" << fulllll.getNumTweets()<<std::endl;
    }

    //add one more to the tweetManager above
    fulllll.addTweet(twt1);
    if (fulllll.maxSize() != 100) {
        std::cout << "didn't add to a full tweet\n" << fulllll.
                maxSize()<<std::endl;
    }

    if (fulllll. getNumTweets() != 52) {
        std::cout << "didn't add to a full tweet\n" << fulllll.getNumTweets()<<std::endl;
    }

    //adding 50 more tweets to tweetMgr with 52 tweets

    for (size_t i = 0; i < DEFAULT_SIZE; i++) {
        Tweet element(i, "filled", "filled");
        fulllll.addTweet(element);
    }

    if (fulllll.maxSize() != 200) {
        std::cout << "didn't add correctly to a full tweet\n" << fulllll.maxSize()<<std::endl;
    }
    //checking if tweet goes up by one
    if (fulllll. getNumTweets() != 102) {
        std::cout << "didn't add correctly to a full tweet\n" << fulllll.getNumTweets()<<std::endl;
    }

    //Test if getNumTweets work fine - returning the number of tweets in the collection

    size_t numTweets = fullTweets.getNumTweets();
    if (numTweets != 50) {
        std::cout << "Number of tweets in the collection is wrong" <<std::endl;
    }

    //Test if Tweet getTweet throws invalid_argument exception at an invalid index (5-99)

    try {
        for (int i = 5; i < 100; i++) { // attempt to get 100 tweets (max was 50)
            tm1.getTweet(i);
        }
        std::cout << "\nTHIS MESSAGE SHOULD NOT BE SEEN." << "Tweet was found in an invalid index" << std::endl;
    }
    catch (std::invalid_argument &excpt) {
        std::cout << "Exception successfully thrown & caught:: " << excpt.what() << std::endl;
    }

    //Test if grow method works correctly
    // initsize > maxTweets

    TweetMgr testGrow;

    for (size_t i = 0; i < DEFAULT_SIZE; i++) {
        Tweet element(i, "filled", "filled");
        testGrow.addTweet(element);
    }

    TweetMgr testGrowSame = testGrow;

    // newSize = 60 for a tweetManager with maxTweets of 50

    testGrow.grow(60);

    if (testGrow.maxSize() != 60) {
        std::cout << "grow do not have correct maxSize" <<std::endl;
    }

    if (testGrow.getNumTweets() != 50) {
        std::cout << "grow changed numTweets" <<std::endl;
    }

    // check if the tweets inside the tweet manager stayed the same

    for(int i = 0; i < (int) testGrow.getNumTweets(); i++){
        if(testGrow.getTweet(i) != testGrowSame.getTweet(i)){
            std::cout << "grow changed tweet elements" <<std::endl;
        }
    }

    // test grow where maxTweets = newSize

    testGrow.grow(60);

    if (testGrow.maxSize() != 60) {
        std::cout << "grow do not have correct maxSize" <<std::endl;
    }

    if (testGrow.getNumTweets() != 50) {
        std::cout << "grow changed numTweets" <<std::endl;
    }

    //check if 10 more tweets can fit inside the tweetManger that "grow" into maxTweets = 60

    for(int i = 0; i < 10; i++){
        Tweet element(i, "add", "added");
        testGrow.addTweet(element);
    }

    if (testGrow.maxSize() != 60) {
        std::cout << "grow do not have correct maxSize" <<std::endl;
    }

    if (testGrow.getNumTweets() != 60) {
        std::cout << "array doesn't have the size of \"newSize\"" <<std::endl;
    }

    //Test if Tweet getTweet throws invalid_argument exception at an invalid index (-99~-1)

    try {
        for (int i = -1; i > -100; i--) { // attempt to get 100 tweets (max was 50)
            tm1.getTweet(i);
        }
        std::cout << "\nTHIS MESSAGE SHOULD NOT BE SEEN." << "Tweet was found in an invalid index" << std::endl;
    }
    catch (std::invalid_argument &excpt) {
        std::cout << "Exception successfully thrown & caught:: " << excpt.what() << std::endl;
    }

    //Test if Tweet getTweet returns the tweet at the specified index

    Tweet checkIndex4 = tm1.getTweet(4);
    if (!checkIndex4.equals(twt5)) {
        std::cout << "Tweet at the specified index was not returned" << std::endl;
    }

    // Test if String getTweets returns all the tweets in a sorted way

    if (tm1.getTweets() != "@jack: just setting up my twttr (sent at 0)\n"
                           "@tom: I am tom (sent at 3)\n"
                           "@Tom: I am Tom (sent at 3)\n"
                           "@jack: I am jack2 (sent at 4)\n"
                           "@jane: I am jane (sent at 5)\n") {
        std::cout << "Unexpected tweet in collection" << std::endl;
        std::cout << "getTweets() returned the following tweets: " << tm1.getTweets() << std::endl;
    }

    //Test if string getTweets(const string& sender) returns all tweets sent by a specified sender
    //one tweet should be printed b/c there is only one tweet of that sender

    if (tm1.getTweets("@jane") != "@jane: I am jane (sent at 5)\n") {
        std::cout << "Unexpected tweet in collection" << std::endl;
        std::cout << "getTweets() returned the following tweets: " << tm1.getTweets("@jane") << std::endl;
    }

    //Test if string getTweets(const string& sender) returns all tweets sent by a specified sender
    // two tweets should be printed because there are two tweets with the same name

    if (tm1.getTweets("@jack") != "@jack: just setting up my twttr (sent at 0)\n"
                                  "@jack: I am jack2 (sent at 4)\n") {
        std::cout << "Unexpected tweet in collection" << std::endl;
        std::cout << "getTweets() returned the following tweets: " << tm1.getTweets("@jack") << std::endl;
    }

    //Test if getTweets is case sensitive
    //jack does not exist but jack exists

    if (tm1.getTweets("@Jack") != "") {
        std::cout << "Unexpected tweet in collection" << std::endl;
        std::cout << "getTweets() returned the following tweets: " << tm1.getTweets("@Jack") << std::endl;
    }

    //Test if getTweet is case sensitive
    //Tom exists - should get Tom's tweet

    if (tm1.getTweets("@Tom") != "@Tom: I am Tom (sent at 3)\n") {
        std::cout << "Unexpected tweet in collection" << std::endl;
        std::cout << "getTweets() returned the following tweets: " << tm1.getTweets("@Tom") << std::endl;
    }

    //Test if a tweet is returned when there is no match. Should return an empty string

    if (tm1.getTweets("@Beyonce") != "") {
        std::cout << "Unexpected tweet in collection" << std::endl;
        std::cout << "getTweets() returned the following tweets: " << tm1.getTweets("@Beyonce") << std::endl;
    }

    //Test if string getTweets(size_t ts1) returns all tweets for a given timestamp

    if (tm1.getTweets(3) != "@tom: I am tom (sent at 3)\n"
                            "@Tom: I am Tom (sent at 3)\n") {
        std::cout << "Unexpected tweet in collection" << std::endl;
        std::cout << "getTweets() returned the following tweets: " << tm1.getTweets(3) << std::endl;
    }

    //Test if string getTweets(size_t ts1) returns a tweet if there is no match for the timespan

    if (tm1.getTweets(6) != "") {
        std::cout << "Unexpected tweet in collection" << std::endl;
        std::cout << "getTweets() returned the following tweets: " << tm1.getTweets(6) << std::endl;
    }

    //Test if string getTweets(size_t ts1, size_t ts2) returns a string of all Tweets in a range of two given timestamps
    //Left timespan < right timespan


    if (tm1.getTweets(1, 5) != "@tom: I am tom (sent at 3)\n"
                               "@Tom: I am Tom (sent at 3)\n"
                               "@jack: I am jack2 (sent at 4)\n"
                               "@jane: I am jane (sent at 5)\n") {
        std::cout << "Unexpected tweet in collection" << std::endl;
        std::cout << "getTweets() returned the following tweets: " << tm1.getTweets(1, 5) << std::endl;

    }

    //Test if string getTweets(size_t ts1, size_t ts2) returns a string if there is no match of the timestamps

    if (tm1.getTweets(6, 10) != "") {
        std::cout << "Unexpected tweet in collection" << std::endl;
        std::cout << "getTweets() returned the following tweets: " << tm1.getTweets(6, 10) << std::endl;
    }

    //Test if string getTweets(size_t ts1, size_t ts2) returns a string of all Tweets in a range of two given timestamps
    //right timespan < left timespan

    if (tm1.getTweets(5, 1) != "@tom: I am tom (sent at 3)\n"
                               "@Tom: I am Tom (sent at 3)\n"
                               "@jack: I am jack2 (sent at 4)\n"
                               "@jane: I am jane (sent at 5)\n") {
        std::cout << "Unexpected tweet in collection" << std::endl;
        std::cout << "getTweets() returned the following tweets: " << tm1.getTweets(5, 1) << std::endl;

    }

    //Test if string getTweets(size_t ts1, size_t ts2) returns a string of all Tweets in a range of two given timestamps
    //left timespan == right timespan

    if (tm1.getTweets(3, 3) != "@tom: I am tom (sent at 3)\n"
                               "@Tom: I am Tom (sent at 3)\n") {
        std::cout << "Unexpected tweet in collection" << std::endl;
        std::cout << "getTweets() returned the following tweets: " << tm1.getTweets(3, 3) << std::endl;
    }

    if (tm1.getTweets(0, 3) != "@jack: just setting up my twttr (sent at 0)\n"
                               "@tom: I am tom (sent at 3)\n"
                               "@Tom: I am Tom (sent at 3)\n") {
        std::cout << "getTweets() returned the following tweets: " << tm1.getTweets(0, 3) << std::endl;
    }

    TweetMgr test2;
    test2.addTweet(twt2);
    test2.addTweet(twt3);
    test2.addTweet(twt4);
    test2.addTweet(twt5);
    if (test2.getTweets(0, 1) != "") {
        std::cout << "getTweets() returned the following tweets: " << test2.getTweets(0, 1) << std::endl;
    }


    //Copy TweetMgr to check if delete methods work
    TweetMgr test3;
    TweetMgr test4;
    TweetMgr test5;
    test3.deleteTweets();

    if (test3.getTweets() != "") {
        std::cout << "oh no" << std::endl;
    }

    test4.deleteTweets("@jack");
    if (test4.getTweets() != "") {
        std::cout << "oh no" << std::endl;
    }

    test5.deleteTweets(0, 5);
    if (test5.getTweets() != "") {
        std::cout << "oh no" << std::endl;
    }

    TweetMgr tm3 = tm1;
    TweetMgr tm4 = tm1;
    TweetMgr tm5 = tm1;
    TweetMgr tm6 = tm1;
    TweetMgr tm7 = tm1;
    TweetMgr tm8 = tm1;
    TweetMgr tm9 = tm1;
    TweetMgr tm10 = tm1;
    TweetMgr tm11 = tm1;
    TweetMgr tm12 = tm1;
    TweetMgr tm13 = tm1;
    TweetMgr tm14;

    Tweet lol1(11, "lol", "10");
    Tweet lol2(12, "lol", "11");
    Tweet lol3(13, "lol", "12");
    Tweet lol4(14, "lol", "13");

    tm14.addTweet(lol1);
    tm14.addTweet(lol2);
    tm14.addTweet(lol3);
    tm14.addTweet(lol4);
    tm14.deleteTweets(0, 10);
    if (tm14.getTweets() != "lol: 10 (sent at 11)\n"
                            "lol: 11 (sent at 12)\n"
                            "lol: 12 (sent at 13)\n"
                            "lol: 13 (sent at 14)\n") {
        std::cout << tm14.getTweets() << std::endl;
    }


    tm13.deleteTweets(0, 10);
    if (tm13.getTweets() != "") {
        tm13.addTweet(twt1);
        tm13.addTweet(twt2);
        tm13.addTweet(twt3);
        tm13.addTweet(twt4);
        tm13.addTweet(twt5);
        std::cout << tm13.getTweets() << std::endl;
    }

    tm12.deleteTweets(0, 5);
    if (tm12.getTweets() != "") {
        std::cout << tm12.getTweets() << std::endl;
    }

    tm11.deleteTweets(6, 10);
    if (tm11.getTweets() != "@jack: just setting up my twttr (sent at 0)\n"
                            "@tom: I am tom (sent at 3)\n"
                            "@Tom: I am Tom (sent at 3)\n"
                            "@jack: I am jack2 (sent at 4)\n"
                            "@jane: I am jane (sent at 5)\n") {
        tm11.addTweet(twt1);
        tm11.addTweet(twt2);
        tm11.addTweet(twt3);
        tm11.addTweet(twt4);
        tm11.addTweet(twt5);
        std::cout << tm11.getTweets() << std::endl;
    }

    //Test if all the tweets are deleted
    if (tm1.deleteTweets() != (size_t) 5) {
        std::cout << "Unexpected number of tweets are deleted" << std::endl;
        std::cout << "Number of tweets deleted are " << tm1.deleteTweets() << std::endl;
    }

    //Test if deleteTweets(size_t t1) deletes all the posts earlier than the timespan
    if (tm3.deleteTweets(4) != (size_t) 3) {
        std::cout << "Unexpected number of tweets are deleted!!" << std::endl;
        std::cout << "Number of tweets deleted are " << tm3.deleteTweets(4) << std::endl;
    }

    //Test if deleteTweets(size_t t1) does not perform deletions if there are no timespan earlier

    if (tm4.deleteTweets(0) != (size_t) 0) {
        std::cout << "Unexpected number of tweets are deleted!" << std::endl;
        std::cout << "Number of tweets deleted are " << tm4.deleteTweets(0) << std::endl;
    }

    //Test if deleteTweets(size_t t1, size_t t2) deletes all Tweets between a range of two given timestamps
    //left timespan < right timespan

    if (tm5.deleteTweets(1, 5) != (size_t) 4) {
        std::cout << "Unexpected number of tweets are deleted" << std::endl;
        std::cout << "Number of tweets deleted are " << tm5.deleteTweets(1, 5) << std::endl;
    }

    //Test if deleteTweets(size_t t1, size_t t2) deletes all Tweets between a range of two given timestamps
    //left timespan > right timespan

    if (tm6.deleteTweets(5, 1) != (size_t) 4) {
        std::cout << "Unexpected number of tweets are deleted" << std::endl;
        std::cout << "Number of tweets deleted are " << tm6.deleteTweets(5, 1) << std::endl;
    }

    //Test if deleteTweets(size_t t1, size_t t2) deletes all Tweets between a range of two given timestamps
    //left timespan = right timespan

    if (tm7.deleteTweets(3, 3) != (size_t) 2) {
        std::cout << "Unexpected number of tweets are deleted" << std::endl;
        std::cout << "Number of tweets deleted are " << tm7.deleteTweets(3, 3) << std::endl;
    }

    //Test if deleteTweets(string &sender) deletes all the tweets sent by the given sender

    if (tm8.deleteTweets("@jack") != (size_t) 2) {
        std::cout << "Unexpected number of tweets are deleted" << std::endl;
        std::cout << "Number of tweets deleted are " << tm8.deleteTweets("@jack") << std::endl;
    }


    //Test if deleteTweets(string &sender) deletes anything when there is no match of the sender

    if (tm8.deleteTweets("@Beyonce") != (size_t) 0) {
        std::cout << "Unexpected number of tweets are deleted" << std::endl;
        std::cout << "Number of tweets deleted are " << tm8.deleteTweets("@Beyonce") << std::endl;
    }

    //Test if deleteTweet is case sensitive

    //jack exists but Jack does not exists
    if (tm9.deleteTweets("@Jack") != (size_t) 0) {
        std::cout << "Unexpected number of tweets are deleted" << std::endl;
        std::cout << "Number of tweets deleted are " << tm9.deleteTweets("@Jack") << std::endl;
    }

    //Test if deleteTweet is case sensitive
    //Tom exists - should delete only 1

    if (tm10.deleteTweets("@Tom") != 1) {
        std::cout << "Unexpected number of tweets are deleted" << std::endl;
        std::cout << "Number of tweets deleted are " << tm10.deleteTweets("@Tom") << std::endl;
    }


// uncomment the following lines if you are running the program in a
// DOS or terminal window and you want the window to stay open when
// the testing is done.
//   std::cout << "\nEnd of tests. Press enter to exit.";
//   char tt;
//   tt = std::cin.get();

}
