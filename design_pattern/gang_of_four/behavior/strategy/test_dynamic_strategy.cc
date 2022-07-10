#include "dynamic_strategy.hpp"

int main()
{
    std::vector<std::string> items{"string1", "string2", "string3"};

    TextProcessor text_processor;
    text_processor.SetOutputFormat(TextProcessor::OutputFormat::Markdown);
    text_processor.AppendList(items);
    std::cout << text_processor.Str() << std::endl;

    text_processor.Clear();
    text_processor.SetOutputFormat(TextProcessor::OutputFormat::HTML);
    text_processor.AppendList(items);
    std::cout << text_processor.Str() << std::endl;

    return 0;
}