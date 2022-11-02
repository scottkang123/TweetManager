// CS2201 Vanderbilt University
// Prof. Roth


#ifndef TWEET_H
#define TWEET_H

#include <string>

class Tweet {

private:
    size_t timestamp;    // Every Tweet has a time stamp that indicates the time of its origin.
                         // To keep things simple for us, we will use a non-negative integer for the time stamp
                         // rather than a full time stamp structure/object. Smaller integers indicate an earlier
                         // time, while larger integers indicate a later time

    std::string user;    // Handle/username of the sender of the Tweet

    std::string text;    // The text of the Tweet

public:
    Tweet();     // default ctor. Sets the timestamp to zero amd the sender & message to ""

    Tweet(size_t ts, const std::string &sender, const std::string &msg);  // alt ctor

    // accessors
    size_t getTimestamp() const;

    const std::string & getUser() const;

    const std::string & getText() const;

    virtual std::string toString() const;

    virtual bool equals(const Tweet &rhs) const;  // compares timestamp, user, and text

    // mutators
    void setTimestamp(size_t newTime);

    void setUser(const std::string &newUser);

    void setText(const std::string &newText);


    // logical operators that compare two Tweets only compare the timeStamps of the
    // Tweets and are useful for sorting
    bool operator==(const Tweet &rhs) const;  // compares only timestamp

    bool operator!=(const Tweet &rhs) const;

    bool operator<(const Tweet &rhs) const;

    bool operator<=(const Tweet &rhs) const;

    bool operator>(const Tweet &rhs) const;

    bool operator>=(const Tweet &rhs) const;


    // we also overload the logical operators to allow us to compare a Tweet directly
    // against a timestamp
    bool operator==(size_t ts) const;

    bool operator!=(size_t ts) const;

    bool operator<(size_t ts) const;

    bool operator<=(size_t ts) const;

    bool operator>(size_t ts) const;

    bool operator>=(size_t ts) const;


    // stream insertion
    friend std::ostream &operator<<(std::ostream &os, const Tweet &tweet);


};


#endif //TWEET_H
