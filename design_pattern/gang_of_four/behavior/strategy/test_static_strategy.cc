#include "static_strategy.hpp"

int main()
{
    std::vector<std::string> items{"string1", "string2", "string3"};

    TextProcessor<MarkdownStrategy> markdown_processor;
    markdown_processor.AppendList(items);
    std::cout << markdown_processor.Str() << std::endl;

    TextProcessor<HtmlStrategy> html_strategy;
    html_strategy.AppendList(items);
    std::cout << html_strategy.Str() << std::endl;

    return 0;

    return 0;
}