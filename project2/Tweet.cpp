// CS2201 Vanderbilt University
// Prof. Roth


#include "Tweet.h"
#include <iostream>

// default ctor. Sets the timestamp to zero amd the sender & message to ""
Tweet::Tweet() : timestamp(0), user(""), text("")
{
    // nothing left to do
}

Tweet::Tweet(size_t ts, const std::string &sender, const std::string &msg) :
    timestamp(ts), user(sender), text(msg)
{
    // nothing left to do
}


// accessors

size_t Tweet::getTimestamp() const
{
    return timestamp;
}

const std::string & Tweet::getUser() const
{
    return user;
}

const std::string &Tweet::getText() const
{
    return text;
}

std::string Tweet::toString() const
{
    return user + ": " + text + " (sent at " + std::to_string(timestamp) + ")";
}


bool Tweet::equals(const Tweet &rhs) const   // compares timestamp, user, and text
{
    return timestamp==rhs.timestamp && user==rhs.user && text==rhs.text;
}



// mutators

void Tweet::setTimestamp(size_t newTime)
{
    timestamp = newTime;
}

void Tweet::setUser(const std::string &newUser)
{
    user = newUser;
}

void Tweet::setText(const std::string &newText)
{
    text = newText;
}

// logical operators that compare two Tweets only compare the timeStamps of the
// Tweets and are useful for sorting

bool Tweet::operator==(const Tweet &rhs) const   // compares only timestamp
{
    return timestamp == rhs.timestamp;
}

bool Tweet::operator!=(const Tweet &rhs) const
{
    return !(*this==rhs);
}

bool Tweet::operator<(const Tweet &rhs) const
{
    return timestamp < rhs.timestamp;
}

bool Tweet::operator<=(const Tweet &rhs) const
{
    return *this<rhs || *this==rhs;
}

bool Tweet::operator>(const Tweet &rhs) const
{
    return !(*this<=rhs);
}

bool Tweet::operator>=(const Tweet &rhs) const
{
    return !(*this<rhs);
}


// we also overload the logical operators to allow us to compare a Tweet directly
// against a timestamp
bool Tweet::operator==(size_t ts) const
{
    return timestamp == ts;
}

bool Tweet::operator!=(size_t ts) const
{
    return !(*this==ts);
}

bool Tweet::operator<(size_t ts) const
{
    return timestamp < ts;
}

bool Tweet::operator<=(size_t ts) const
{
    return *this<ts || *this==ts;
}

bool Tweet::operator>(size_t ts) const
{
    return !(*this<=ts);
}

bool Tweet::operator>=(size_t ts) const
{
    return !(*this<ts);
}




////// FRIEND FUNCTIONS DEFINED HERE

// insertion operator
std::ostream &operator<<(std::ostream &os, const Tweet &tweet) {
    os << tweet.toString();
    return os;
}
