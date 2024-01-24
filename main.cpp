#include <iostream>
#include <cmath>
#include <sstream>
#include <algorithm>
#include <vector>
#include <functional>

enum class SignalType {Peak, Valley, None};

struct Signal
{
    std::size_t index;
    double value;
    double prominence;
    SignalType type;
    Signal* leftRef;
    Signal* rightRef;

    Signal(std::size_t i, double v, double p, SignalType t, Signal* lRef = nullptr, Signal* rRef = nullptr) : index(i)
        ,value(v)
        ,prominence(p)
        ,type(t)
        ,leftRef(lRef)
        ,rightRef(rRef)
    {}
};

[[nodiscard]] std::string GetSignalTypeString(Signal s) noexcept
{
    if(s.type == SignalType::Peak) return "Peak";
    else if(s.type == SignalType::Valley) return "Valley";

    return "None";
}

[[nodiscard]] constexpr SignalType GetSignalType(double left, double right) noexcept
{
    if((left > 0 && right > 0) || (left == 0 && right > 0) || (left > 0 && right == 0)) return SignalType::Peak;
    else if((left < 0 && right < 0) || (left == 0 && right < 0) || (left < 0 && right == 0)) return SignalType::Valley;

    return SignalType::None;
} 

[[nodiscard]] constexpr auto MaxSignalByValue(const Signal& p1, const Signal& p2) noexcept -> bool {
    return p1.value < p2.value;
};

auto MinSignalByValue = [](const Signal& p1, const Signal& p2) { return p1.value > p2.value; };
auto GetSignalByAValue = [](const Signal& p1, double value) { return p1.value > value; };
auto GetSignalByPeak = [](const Signal& p) { return p.type == SignalType::Peak; };
auto GetSignalByValley = [](const Signal& p) { return p.type == SignalType::Valley; };
auto DrawLine = [](std::string title = "") { std::cout << "=========================================================\n" << title + "\n"; };
auto DrawThinLine = []() { std::cout << "---------------------------------------------------------\n"; };

void DrawSignalInfo(const Signal& p) 
{
    std::cout << "Signal (i: "<< p.index << ", v: " << p.value << ", p: " << p.prominence << ", t: " << GetSignalTypeString(p) << ")\n";
    if(p.leftRef != nullptr) std::cout << "    Signal leftRef (i: "<< p.leftRef->index << ", v: " << p.leftRef->value << ", p: " << p.leftRef->prominence << ", t: " << GetSignalTypeString(*p.leftRef) << ")\n";
    if(p.rightRef != nullptr) std::cout << "    Signal rightRef (i: "<< p.rightRef->index << ", v: " << p.rightRef->value << ", p: " << p.rightRef->prominence << ", t: " << GetSignalTypeString(*p.rightRef) << ")\n";
};

void DrawListSignalInfo(std::vector<Signal> signals, std::string title = "") 
{
    DrawLine(title);
    for_each(signals.begin(), signals.end(), DrawSignalInfo);
    DrawLine();
};

[[nodiscard]] std::vector<Signal> GetSignalInfoFunc(const std::vector<int>& input) noexcept
{
    DrawLine("GetSignalInfoFunc");
    const std::size_t size = input.size();
    std::vector<Signal> lstPeaks;

    if(size > 2)
    {
        for(std::size_t i = 0; i < size; i++)
        {
            double left = 0;
            double right = 0;
            if(i == 0)
            {
                right = input[i] - input[i + 1];
            }
            else if (i == size - 1)
            {
                left = input[i] - input[i - 1];
            }
            else
            {
                right = input[i] - input[i + 1];
                left = input[i] - input[i - 1];
            }
            
            double prominece = left + right;
            SignalType type = GetSignalType(left, right);
            lstPeaks.emplace_back(i, input[i], prominece, type);
        }
    }
    DrawListSignalInfo(lstPeaks);
    return lstPeaks;
}

[[nodiscard]] std::vector<Signal> FindSignalsInRange(const std::vector<Signal>& input, std::function<bool(const Signal&)> criteria) noexcept
{
    std::vector<Signal> filteredSignals;
    std::copy_if(input.begin(), input.end(), std::back_inserter(filteredSignals), criteria);
    return filteredSignals;
}

[[nodiscard]] double GetProminenceValue(const Signal& p, double left, double right) noexcept
{
    double result = 0.0;
    
    if(left == 0)
    {
        result = right;
    }
    else if(right == 0)
    {
        result = left;
    }
    else
    {
        if(p.type == SignalType::Peak)
        {
            result = std::min(left, right);
        }
        else if (p.type == SignalType::Valley)
        {
            result = std::max(left, right);
        }
    }
    
    return result;
}

[[nodiscard]] std::vector<Signal> CaculateProminenceOfSignal(std::vector<Signal>& input) noexcept
{
    //DrawLine("CaculateProminenceOfSignal");
    std::size_t size = input.size();
    std::vector<Signal> ouput = input;
    for(auto& p: ouput)
    {
        //if(p.index == 0 || p.index == size - 1) continue;
        if(p.type == SignalType::None) continue;

        auto funcCompare = (p.type == SignalType::Peak) ? MinSignalByValue : MaxSignalByValue;
        auto refRight = std::find_if(input.begin() + p.index, input.end(), [&](const Signal& s){
            return funcCompare(s, p);
        });

        if(refRight == input.end())
        {
            refRight = std::prev(input.end());
        }
        p.rightRef = &ouput[refRight->index];

        auto refLeft = std::find_if(input.rbegin() + (input.size() - p.index), input.rend(), [&](const Signal& s) {
            return funcCompare(s, p);
        });

        if (refLeft == input.rend()) {
            refLeft = std::prev(input.rend());
        }
        p.leftRef = &ouput[refLeft->index];

        auto minLeft = std::max_element(input.begin() + p.leftRef->index, input.begin() + p.index, funcCompare);
        auto minRight = std::max_element(input.begin() + p.index + 1, input.begin() + p.rightRef->index + 1, funcCompare);
        p.prominence = GetProminenceValue(p, p.value - minLeft->value, p.value - minRight->value);
    };
    
    DrawListSignalInfo(ouput, "ouput");
    return ouput;
}

int main() {
    //const std::vector<int> v = {2, 1, 1, 2, 3, 4, 5, 6, 0, 2, 3, 1, 4, 5, 1};
    const std::vector<int> v = {9,4,5,6,4,7,10,4,4,7};
    auto peaks = GetSignalInfoFunc(v);
    auto updatePeaks = CaculateProminenceOfSignal(peaks);
    auto listPeaks = FindSignalsInRange(updatePeaks, GetSignalByPeak);
    DrawListSignalInfo(listPeaks, "listPeaks");
    auto listValleys = FindSignalsInRange(updatePeaks, GetSignalByValley);
    DrawListSignalInfo(listValleys, "listValleys");
    return 0;
}
