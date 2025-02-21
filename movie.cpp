#include <iomanip>
#include <sstream>
#include "movie.h"
#include "util.h"

using namespace std;

Movie::Movie(const std::string& category, const std::string& name, double price, int qty, 
                    const std::string& genre, const std::string& rating)
          : Product(category, name, price, qty), genre_(genre), rating_(rating) {}

std::set<std::string> Movie::keywords() const 
{
  std::set<std::string> key = parseStringToWords(name_);
  std::set<std::string> genreW = parseStringToWords(genre_);
  key.insert(convToLower(genre_));
	key.insert(genreW.begin(), genreW.end());
	key.insert(convToLower(rating_));
  return key;
}

std::string Movie::displayString() const 
{
  std::ostringstream oss;
  oss << name_ << "\n";
	oss << "Genre: " << genre_ << " Rating: " << rating_ << "\n";
	oss << std::fixed << std::setprecision(2) << price_ << " " << qty_ << " left.";
  return oss.str();
}

void Movie::dump(std::ostream& os) const
{
    //os << "<products>" << std::endl;
		os << category_ << std::endl;
		os << name_ << std::endl;
		os << price_ << std::endl;
		os << qty_ << std::endl;
		os << genre_ << std::endl;
		os << rating_ << std::endl;
}