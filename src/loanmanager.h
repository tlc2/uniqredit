#ifndef LOAN_MANAGER_H
#define LOAN_MANAGER_H 

#include <iostream>
#include <string>

#include "util.h"
#include "utilmoneystr.h"

#include <sqlite3.h>

#ifndef BOOST_SPIRIT_THREADSAFE
#define BOOST_SPIRIT_THREADSAFE
#endif
using namespace std;
class CLoanManager
{
public:
	string senddata(string data);
};

#endif
