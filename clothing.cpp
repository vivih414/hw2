#include <iomanip>
#include <sstream>
#include "clothing.h"
#include "util.h"

using namespace std;

Clothing::Clothing(const std::string& category, const std::string& name, double price, int qty, 
          const std::string& size, const std::string& brand)
          : Product(category, name, price, qty), size_(size), brand_(brand) {}

std::set<std::string> Clothing::keywords() const 
{
  std::set<std::string> key = parseStringToWords(name_);
  std::set<std::string> brandW = parseStringToWords(brand_);
  key.insert(brandW.begin(), brandW.end());
  return key;
}

std::string Clothing::displayString() const 
{
  std::ostringstream oss;
  oss << name_ << "\n";
	oss << "Size: " << size_ << " Brand: " << brand_ << "\n";
	oss << std::fixed << std::setprecision(2) << price_ << " " << qty_ << " left.";
  return oss.str();
}

void Clothing::dump(std::ostream& os) const
{
    //os << "<products>" << std::endl;
		os << category_ << std::endl;
		os << name_ << std::endl;
		os << price_ << std::endl;
		os << qty_ << std::endl;
		os << size_ << std::endl;
		os << brand_ << std::endl;
}