#pragma once

#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

class Strategy
{
public:
    virtual ~Strategy() = default;
    virtual void AddListItem(std::ostringstream& oss, const std::string& item) = 0;
    virtual void Start(std::ostringstream& oss) = 0;
    virtual void End(std::ostringstream& oss) = 0;
};

class MarkdownStrategy : public Strategy
{
public:    
    virtual ~MarkdownStrategy() override = default;
    virtual void AddListItem(std::ostringstream& oss, const std::string& item) override 
    {
        oss << "* " << item << "\n";
    }
    virtual void Start(std::ostringstream& oss) override {}
    virtual void End(std::ostringstream& oss) override {}
};

class HtmlStrategy : public Strategy
{
public:
    virtual ~HtmlStrategy() override = default;
    virtual void AddListItem(std::ostringstream& oss, const std::string& item) override 
    {
        oss << "<li>" << item << "</li>\n";
    }
    virtual void Start(std::ostringstream& oss) override 
    {
        oss << "<ul>\n";
    }
    virtual void End(std::ostringstream& oss) override 
    {
        oss << "</ul>\n";
    }
};

template<typename T>
class TextProcessor
{
public:
    enum class OutputFormat
    {
        Markdown,
        HTML,
    };

    void AppendList(const std::vector<std::string>& items)
    {
        strategy_.Start(oss_);
        for(auto& item : items){
            strategy_.AddListItem(oss_, item);
        }
        strategy_.End(oss_);
    }

    std::string Str() const { return oss_.str(); }

    void Clear()
    {
        oss_.str("");
        oss_.clear();
    }
private:
    std::ostringstream oss_;
    T strategy_;

};