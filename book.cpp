#include <iomanip>
#include <sstream>
#include "book.h"
#include "util.h"

using namespace std;

Book::Book(const std::string& category, const std::string& name, double price, int qty, 
          const std::string& isbn, const std::string& author) 
          : Product(category, name, price, qty), isbn_(isbn), author_(author) {}

std::set<std::string> Book::keywords() const 
{
  std::set<std::string> key = parseStringToWords(name_);
  std::set<std::string> authorW = parseStringToWords(author_);
  key.insert(authorW.begin(), authorW.end());
  key.insert(isbn_);
  return key;
}

std::string Book::displayString() const 
{
  std::ostringstream oss;
  oss << name_ << "\n";
	oss << "Author: " << author_ << " ISBN: " << isbn_ << "\n";
	oss << std::fixed << std::setprecision(2) << price_ << " " << qty_ << " left.";
  return oss.str();
}

void Book::dump(std::ostream& os) const
{
		os << category_ << std::endl;
		os << name_ << std::endl;
		os << price_ << std::endl;
		os << qty_ << std::endl;
		os << isbn_ << std::endl;
		os << author_ << std::endl;
}