#include <iostream>
#include <type_traits>
#include <optional>
#include <string>

class A{

public: 

    A(const std::string& inputString) : dataString(std::move(inputString)) {}

    ~A() {
        printData();
    }

private:

    template <typename callbackType, std::enable_if_t<std::is_invocable_v<callbackType>, int> = 0>
    std::string getDataFromCallback(callbackType&& callback) const {

        static_assert(std::is_same_v<decltype(callback()),
                      std::optional<typename decltype(callback())::value_type>>);

        const auto optionalData = callback();

        std::string data{};
        if(optionalData.has_value()){
            data = optionalData.value();
        }

        return data;
    }

    std::optional<std::string> getOptionalDataString() const{
        return dataString;
    }

    void printData() const{
        
        const auto lambdaToGetString = [this](){
            return getOptionalDataString();
        };
        
        std::cout << getDataFromCallback(lambdaToGetString) << "\n";
    }


    std::string dataString;

};

int main() {

    A aObject("42");

    return 0;
}
