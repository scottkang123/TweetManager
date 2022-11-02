// File name: TweetMgr.h
// Author: Kyung Ho (Scott) Kang
// VUnetid: kangk
// Email: kyung.ho.kang@vanderbilt.edu
// Class: CS2201
// Date: 2019 9/23
// Honor statement: I have not given or received unauthorized aid on this assignment
// Assignment Number: #2
// Description: This is the declaration of the TweetMgr class, which supports a collection of Tweets



#ifndef TWEETMGR_H
#define TWEETMGR_H

#include "Tweet.h"

typedef Tweet* TweetPtr;
const size_t DEFAULT_SIZE = 50;  // Default size of dynamic array


class TweetMgr {

private:

    size_t maxTweets;    //size of the dynamic array
    size_t numTweets;    //number of Tweets in the collection (in the partially-filled array)
    TweetPtr tweetArr;   //dynamic array of Tweet objects (partially-filled)

public:

    // Default Constructor
    // Create an empty collection (one with zero Tweets)
    TweetMgr();

    // Alternate constructor
    // Create an empty collection (one with zero Tweets) but with an array of initSize
    // elements
    // Precondition: initSize > 0; throws std::invalid_argument exception if not the case
    TweetMgr(size_t initSize);

    // Copy ctor
    TweetMgr(const TweetMgr &rhs);

    // Assignment operator
    const TweetMgr &operator=(const TweetMgr &rhs);

    // Destructor
    ~TweetMgr();


    // getNumTweets
    // Return the total number of Tweets in the collection
    size_t getNumTweets() const;


    // maxSize
    // Return: size_t - the size of the Tweet array
    size_t maxSize() const;



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
    size_t addTweet(const Tweet &t);


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
    Tweet getTweet(size_t index) const;


    // getTweets()
    //
    // Purpose:    Return a string of all Tweets
    // Parameters: None
    // Returns:    string - containing all the Tweets in sorted order with each & every
    //             Tweet followed immediately by a newline character.
    //             Returns an empty string if the collection is empty
    std::string getTweets() const;


    // getTweets(const string &sender)
    //
    // Purpose:    Return a string of all Tweets sent by the specified sender
    // Parameters: string sender - the author of the Tweets we are supposed to return
    // Returns:    string   - containing all the Tweets from the specified author, in sorted order,
    //                        with each Tweet followed immediately by a newline character.
    //
    // Behavior:
    // 1. Finds all Tweets from the specified sender (matching sender is case sensitive)
    // 2. If no such Tweets are found, returns an empty string
    // 3. If Tweets are found, append them on the return string in sorted order each
    //    followed by a newline character.
    std::string getTweets(const std::string &sender) const;


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
    std::string getTweets(size_t ts) const;


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
    std::string getTweets(size_t ts1, size_t ts2) const;


    // deleteTweets()
    //
    // Purpose:    Deletes all Tweets from the collection
    // Parameters: None
    // Return:     size_t - the number of Tweets deleted (a size_t value)
    size_t deleteTweets();


    // deleteTweets(size_t ts)
    //
    // Purpose:    Deletes all Tweets whose timestamps are earlier than the parameter ts
    // Parameters: size_t ts - the specified timestamp
    // Return:     size_t - the number of Tweets deleted (a size_t value)
    //
    // Notes:
    // 1. If there are no timestamps earlier than ts, no deletions will be performed and
    //    zero is returned
    size_t deleteTweets(size_t ts);


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
    size_t deleteTweets(size_t ts1, size_t ts2);


    // deleteTweets(const string &sender)
    //
    // Purpose:    Delete all Tweets from the specified sender
    // Parameters: string sender - author of tweets to be deleted, comparison is case sensitive
    // Return:     size_t - number of Tweets deleted (size_t value)
    size_t deleteTweets(const std::string &sender);


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
    void merge(const TweetMgr& tm);


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
    void grow(size_t newSize);


};


#endif //TWEETMGR_H
