#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

#define WHOLE 24 * 60
#define HALF 12 * 60

int minTimeDiff(std::string times[], size_t len){

    int min = WHOLE;
    int diff;
    int wrapDelta;

    std::vector<int> data;

    for (size_t i = 0; i < len; i++) {
        const std::size_t colon = times[i].find(":");

        int hr = std::stoi(times[i].substr(0, colon));
        int min = std::stoi(times[i].substr(colon + 1));

        int total = (hr * 60) + min;
        data.push_back(total);
    }

    std::sort(data.begin(), data.end());

    for (size_t i = 1; i < data.size(); i++) {

        diff = data[i] - data[i - 1];

        if (diff < min) {
            min = diff;
        }
    }

    wrapDelta = data[0] + WHOLE - data[data.size() - 1];
    if (wrapDelta < min) {
        min = wrapDelta;
    }

    return min;
}

int main(void) {

    std::string times[] = {"00:00", "02:24", "03:46", "01:22"};
    size_t len = sizeof(times) / sizeof(std::string);

    int result = minTimeDiff(times, len);
    std::cout << "Result: "<< result << std::endl;

    return 0;
}