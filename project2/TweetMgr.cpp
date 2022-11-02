// File name: TweetMgr.cpp
// Author: Kyung Ho (Scott) Kang
// VUnetid: kangk
// Email: kyung.ho.kang@vanderbilt.edu
// Class: CS2201
// Date: 2019 9/23
// Honor statement: I have not given or received unauthorized aid on this assignment
// Assignment Number: #2
// Description: This is the declaration of the TweetMgr class, which supports a collection of Tweets. This class uses
// dynamic array to store, add tweets.


#include "TweetMgr.h"
#include <string>
#include <stdexcept>

// Default Constructor
// Create an empty collection (one with zero Tweets)
TweetMgr::TweetMgr() : maxTweets(DEFAULT_SIZE), numTweets(0), tweetArr(new Tweet[maxTweets]) {

}

// Alternate constructor
// Create an empty collection (one with zero Tweets) but with an array of initSize
// elements
// Precondition: initSize > 0; throws std::invalid_argument exception if not the case
TweetMgr::TweetMgr(size_t initSize) : maxTweets(initSize), numTweets(0), tweetArr(new Tweet[maxTweets]) {

    if (initSize <= 0) {
        throw std::invalid_argument("exception");
    }

}

// Copy ctor
TweetMgr::TweetMgr(const TweetMgr &rhs) : maxTweets(rhs.maxTweets), numTweets(rhs.numTweets),
                                          tweetArr(new Tweet[maxTweets]) {


    for (size_t i = 0; i < maxTweets; i++) {
        tweetArr[i] = rhs.tweetArr[i];

    }

}

// Assignment operator
const TweetMgr &TweetMgr::operator=(const TweetMgr &rhs) {
    if (this == &rhs) {
        return *this;
    }
    TweetMgr tmp(rhs); // copy rhs into a local temp object
    std::swap(maxTweets, tmp.maxTweets);
    std::swap(numTweets, tmp.numTweets);

    delete[] tweetArr;
    tweetArr = new Tweet[maxTweets];

    for (size_t i = 0; i < numTweets; i++) {
        tweetArr[i] = rhs.tweetArr[i];
    }

    return *this;
}

// Destructor
TweetMgr::~TweetMgr() {
    delete[] tweetArr;
    tweetArr = nullptr;
}


// getnumTweets
// Return the total number of Tweets in the collection
size_t TweetMgr::getNumTweets() const {
    return numTweets;
}


// maxSize
// Return: size_t - the size of the Tweet array
size_t TweetMgr::maxSize() const {

    return maxTweets;

}


//addTweet(const Tweet &t)
//
//Purpose: add/insert a Tweet to the collection of Tweet objects
//Parameters: Tweet t - the Tweet to be added
//Returns: size_t - the index position of the inserted Tweet
//
//Behavior:
//1. In case of the array being empty: insert as the first element
//2. In case the array is full: double the size of the array and then add
//   the Tweet
//3. In case of a non-empty array with space available: insert the Tweet in sorted
//   order by timestamp, shifting other items up to make space
//4. In case of already existing Tweet with same timestamp: insert new tweet
//   after (behind) the existing one
//5. Return the index of the inserted tweet, using zero-based indexing
//Note: Normally this method would be a void method and not return any value. We have it
//return the index of where the tweet was inserted so that we can verify that the tweet
//was inserted in the correct position in the array.
size_t TweetMgr::addTweet(const Tweet &t) {

    if (numTweets == maxTweets) {
        this -> grow(maxTweets * 2);
    }

    size_t index = numTweets;
    int i = numTweets - 1;
    while (tweetArr[i] > t && i >= 0) {
        tweetArr[index] = tweetArr[index - 1];
        i--;
        index--;
    }
    tweetArr[index] = t;
    numTweets++;

    return index;  // replace this!
}


// getTweet(size_t index)
//
// Purpose:    returns the Tweet at the specified index in the collection,
//             throw exception if index is bad
// Parameters: size_t index - the index of the desired Tweet; using zero-based indexing
// Returns:    Tweet  - the Tweet at the specified index
//
// Behavior:
// 1. If the index is invalid, throw an std::invalid_argument exception
// 2. Otherwise, return the Tweet at the specified index
// NOTE: Normally a TweetMgr class would not support indexing to access tweets, as the user
// does not think of storing tweets by index. We have only added this method so that we
// can verify that your addTweet method works correctly. You should not call this method
// in any code, as it only exists for testing and should later be deleted.
Tweet TweetMgr::getTweet(size_t index) const {
    Tweet desired;
    // check if the index is larger than number of tweets and check if it is a negative number
    if (index >= numTweets) {
        throw std::invalid_argument("index is invalid");
    } else {
        desired = tweetArr[index];
    }
    return tweetArr[index];
}


// getTweets()
//
// Purpose:    Return a string of all Tweets
// Parameters: None
// Returns:    string - containing all the Tweets in sorted order with each & every
//             Tweet followed immediately by a newline character.
//             Returns an empty string if the collection is empty
std::string TweetMgr::getTweets() const {
    // print all the tweets in the tweet manager
    std::string answer;
    for (size_t i = 0; i < numTweets; i++) {
        answer += tweetArr[i].toString() + "\n";
    }
    return answer;
}


// getTweets(const string &sender)
//
// Purpose:    Return a string of all Tweets sent by the specified sender
// Parameters: string sender - the author of the Tweets we are supposed to return
// Returns:    string     - containing all the Tweets from the specified author, in sorted order,
//                          with each Tweet followed immediately by a newline character.
//
// Behavior:
// 1. Finds all Tweets from the specified sender (matching sender is case sensitive)
// 2. If no such Tweets are found, returns an empty string
// 3. If Tweets are found, append them on the return string in sorted order each
//    followed by a newline character.
std::string TweetMgr::getTweets(const std::string &sender) const {
    std::string answer = "";
    //if the sender name match, then add the tweet to the answer
    for (size_t i = 0; i < numTweets; i++) {
        if (tweetArr[i].getUser() == (sender)) {
            answer += tweetArr[i].toString() + "\n";
        }
    }
    return answer;  // replace this!
}


// getTweets(size_t ts)
//
// Purpose:    Return a string of all Tweets for a given timestamp
// Parameters: size_t ts - the timestamp we are supposed to check for match
// Return:     string - containing all the matching Tweets, in sorted order,
//             each tweet followed immediately by a newline character.
//
// Behavior:
// 1. Finds all Tweeets with the given timestamp
// 2. If no match is found, returns an empty string
// 3. If matches are found, append them on the return string in sorted order each
//    followed by a newline character.
//
// Note: see addTweet() for the definition of sorted order of Tweets with the same timestamp.
std::string TweetMgr::getTweets(size_t ts) const {

    return getTweets(ts, ts);

}


// getTweets(size_t ts1, size_t ts2)
//
// Purpose:    Return a string of all Tweets in a range of two given timestamps
// Parameters: ts1 and ts2 (the range of timestamps)
// Return:     string containing all the matching Tweets, in sorted order,
//             each Tweet followed immediately by a newline character.
//
// Behavior:
// 1. If the collection contains no timestamps in the given range, return an empty string
// 2. Create a string containing all the Tweets, in sorted order, which are later
//    than or equal to the smaller of the two timestamps and are earlier than or equal to
//    the larger of the two timestamps, with each tweet followed immediately by a
//    newline character.
// Note: the relative order of ts1 and ts2 is unknown
std::string TweetMgr::getTweets(size_t ts1, size_t ts2) const {

    std::string answer;
    // find the smaller timespan between the two, ts1 and ts2
    if (ts1 > ts2) {
        size_t temp = ts1;
        ts1 = ts2;
        ts2 = temp;
    }

    size_t i = 0;
    while (tweetArr[i].getTimestamp() <= ts2 && i < numTweets) {
        if (tweetArr[i].getTimestamp() >= ts1 && tweetArr[i].getTimestamp() <= ts2) {
            answer += tweetArr[i].toString() + "\n";
        }
        i++;
    }

    return answer;  // replace this!
}


// deleteTweets()
//
// Purpose:    Deletes all Tweets from the collection
// Parameters: None
// Return:     size_t - the number of Tweets deleted (a size_t value)
size_t TweetMgr::deleteTweets() {

    size_t deletedTweets = numTweets;
    numTweets = 0;
    return deletedTweets;

}

// deleteTweets(const string &sender)
//
// Purpose:    Delete all Tweets from the specified sender
// Parameters: string sender - author of tweets to be deleted, comparison is case sensitive
// Return:     size_t - number of Tweets deleted (size_t value)
size_t TweetMgr::deleteTweets(const std::string &sender) {
    size_t numDeleted = 0;
    for (size_t i = 0; i < numTweets; i++) {
        std::string user = tweetArr[i].getUser();

        //whenever find the match, shift all the element left by one
        if (user == sender) {
            for (size_t j = i + 1; j < numTweets; j++) {
                tweetArr[j - 1] = tweetArr[j];
            }
            numDeleted++;
            i--;
            numTweets--;
        }
    }
    return numDeleted;
}


// deleteTweets(size_t ts)
//
// Purpose:    Deletes all Tweets whose timestamps are earlier than the parameter ts
// Parameters: size_t ts - the specified timestamp
// Return:     size_t - the number of Tweets deleted (a size_t value)
//
// Notes:
// 1. If there are no timestamps earlier than ts, no deletions will be performed and
//    zero is returned
size_t TweetMgr::deleteTweets(size_t ts) {

    if(ts == 0){
        return 0;
    }

    return deleteTweets(0, ts-1);
}


// deleteTweets(size_t ts1, size_t ts2)
//
// Purpose:    Deletes all Tweets between a range of two given timestamps
// Parameters: ts1 and ts2 - the range of timestamps
// Return:     size_t - number of Tweets deleted (size_t value)
//
// Behavior:
// 1. If the collection contains no timestamps in the given range, perform no deletions
//    and return zero
// 2. Delete all Tweets which are later than or equal to the smaller of the two
//    timestamps and are earlier than or equal to the larger of the two timestamps.
//    Return the number deleted.
// Note: the relative order of ts1 and ts2 is unknown
size_t TweetMgr::deleteTweets(size_t ts1, size_t ts2) {
    size_t numDeleted = 0;
    size_t index1 = 0;     //start of deletion
    size_t index2 = 0;     //end of deletion


    //find the smaller time between the two
    if (ts1 > ts2) {
        size_t temp = ts1;
        ts1 = ts2;
        ts2 = temp;
    }

    for (size_t i = 0; i < numTweets; i++) {
        // if timespan is smaller than ts1, then index1++
        if (tweetArr[i].getTimestamp() < ts1) {
            index1 = i + 1;
        } else if (tweetArr[i].getTimestamp() <= ts2) {
            numDeleted++;
        }
        // if timespan is smaller than ts2, then index2++
        if (tweetArr[i].getTimestamp() <= ts2) {
            index2++;
        }

    }

    // shift all the tweets
    for (size_t j = index2; j < numTweets; j++) {
        tweetArr[index1] = tweetArr[j];
        index1++;
    }


    numTweets -= numDeleted;
    return numDeleted;
}


// merge(const TweetMgr& tm)
//
// Purpose:    Merge a received tweet collection into this collection
// Parameters: TweetMgr tm (the TweetMgr collection to be merged)
// Return:     None
//
// Behavior:
// 1. Add each tweet of the parameter TweetMgr to the object TweetMgr;
//    may result in duplicate entries if both TweetMgrs had the same tweets.
// 2. All tweets that are added remain in the same order as they appeared in the
//    parameter TweetMgr.
// 3. Any added tweet with the same timestamp of an existing tweet is added
//    after (behind) the existing tweet.
// 4. If the total number of tweets is too big to be stored, we grow the array
//    to a total size of the total number of tweets from the two collections plus
//    DEFAULT_SIZE.
// 5. You are guaranteed that the parameter TweetMgr object tm is a different
//    TweetMgr object than the ‘this’ TweetMgr object.
//
// Additional constraint: full credit will only be given for this function if it is
// efficient; that is only if each tweet is moved/assigned only once in the target
// array
void TweetMgr::merge(const TweetMgr &tm) {

    // save the last index of available tweet for both tweetManager

    int initialNum1 = this->numTweets - 1;
    int initialNum2 = tm.numTweets - 1 ;

    // grow the original tweetArr if the maxTweets is less than number of tweets combined

    if (this->maxTweets < tm.numTweets + this->numTweets) {
        this -> grow(this->numTweets + tm.numTweets + DEFAULT_SIZE);
    }

    // change number of tweets

    numTweets += tm.numTweets;

    // start from the behind and put tweet in order

    for(int i = numTweets-1; i >= 0; i--){

        // if the end index of the second tweetmanager is greater or equal to the end index of the first tweetmanager
        // then the tweet of the second manager goes inside the end of the resulting array. Reverse, otherwise

        if(tweetArr[initialNum1] <= tm.tweetArr[initialNum2] && initialNum2 >= 0 && initialNum1 >= 0){
            tweetArr[i] = tm.tweetArr[initialNum2];
            initialNum2--;         // end index of the second tweetmanager decreases by one
        }else if(tweetArr[initialNum1] > tm.tweetArr[initialNum2] && initialNum1 >= 0 && initialNum2 >= 0){
            tweetArr[i] = tweetArr[initialNum1];
            initialNum1--;            // end index of the first tweetmanager decreases by one
        }else if(initialNum1 < 0){    // if all of the first tweetmanager is used up, then the second manager is placed
            tweetArr[i] = tm.tweetArr[initialNum2];
            initialNum2--;  // end index of the second tweetmanager decreases by one
        }
    }
}


// grow(size_t newSize)
//
// Purpose:    grow the tweetArr array
// Parameters: newSize - the new desired size of the array
// Return:     None
//
// If the current size of the array is equal to or larger than newSize, we do nothing.
// Else we allocate a new array for the TweetMgr of the desired size and copy the
// old data into it.
//
// NOTE: normally this method would be a private method, but it is public here to
//       ease testing
void TweetMgr::grow(size_t newSize) {

    // nothing happens if maxTweets is already greater or equal to newSize

    if (maxTweets >= newSize) {
        return;
    } else {

        // create a temporary pointer array with newSize

        TweetPtr temp = new Tweet[newSize];

        // copy the tweets
        for (size_t i = 0; i < this->numTweets; i++) {
            temp[i] = tweetArr[i];
        }

        // change the maxTweets to newSize
        maxTweets = newSize;

        // delete the original tweetArr
        delete[] tweetArr;
g
        // make tweetArr point to the temp array
        this -> tweetArr = temp;

        // temp array becomes a null pointer
        temp = nullptr;


    }
}



