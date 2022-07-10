#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <sstream>
#include <vector>

class Strategy
{
public:
    virtual ~Strategy() = default;
    virtual void AddListItem(std::ostringstream& oss, const std::string& item) {}
    virtual void Start(std::ostringstream& oss) {}
    virtual void End(std::ostringstream& oss) {}
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

class TextProcessor
{
public:
    enum class OutputFormat
    {
        Markdown,
        HTML,
    };

    void SetOutputFormat(const OutputFormat& format)
    {
        switch(format)
        {
            case OutputFormat::Markdown:
            {
                strategy_ = std::make_unique<MarkdownStrategy>();
                break;
            }
            case OutputFormat::HTML:
            {
                strategy_ = std::make_unique<HtmlStrategy>();
                break;
            }
        }
    }

    void AppendList(const std::vector<std::string>& items)
    {
        strategy_->Start(oss_);
        for(auto& item : items){
            strategy_->AddListItem(oss_, item);
        }
        strategy_->End(oss_);
    }

    std::string Str() const { return oss_.str(); }

    void Clear()
    {
        oss_.str("");
        oss_.clear();
    }

private:
    std::ostringstream oss_;
    std::unique_ptr<Strategy> strategy_;
};